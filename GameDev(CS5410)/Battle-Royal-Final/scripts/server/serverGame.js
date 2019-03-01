
let sqlite = require('sqlite3');
let db = new sqlite.Database('users.db');

let connections = 0;
let TARGET_USERS_NUM = 2;
let game_started = false;
let reconnection = false;
let activeUsers = [];

let present = require('present');
let User = require('./userData');
let NetworkIds = require('../persistant/network-ids');
let Missile = require('./missile');

let Queue = require('../persistant/queue');
const SIMULATION_UPDATE_RATE_MS = 50;
const STATE_UPDATE_RATE_MS = 100;
let lastUpdate = 0;
let quit = false;
let newMissiles = [];
let activeMissiles = [];
let hits = [];
let inputQueue = Queue.create();
let nextMissileId = 1;
let gameTime = 10 * 60; //seconds
let shield = {};
let trees;
let buildings;
let pickups = {};
let killedPlayers = [];
let livingPlayers = 0;
let gameOver = false;
let gameInProgress = false;
let io;

function createMissile(userId, user) {
    let timeM, acceleration;
    switch (user.inventory.weapon){
        case 1:
            timeM = 1500;
            acceleration = 1.013;
            break;
        case 0:
            timeM = 1500;
            acceleration = 1;
            break;
        default:
        case -1:
            timeM = 200;
            acceleration = 1;
            break;
    }
    if(user.inventory.weapon < 0){
    }else{
        timeM = 1500;
    }
    let missile = Missile.create({
        id: nextMissileId++,
        userId: userId,
        missileType: activeUsers[userId].user.inventory.weapon,
        position: {
            x: user.worldView.x,
            y: user.worldView.y
        },
        direction: user.orientation,
        acceleration: acceleration,
        speed: user.speed,
        time: timeM
    });

    newMissiles.push(missile);
}

function processInput(elapsedTime) {
    //
    // Double buffering on the queue so we don't asynchronously receive inputs
    // while processing.
    let processMe = inputQueue;
    inputQueue = Queue.create();

    while (!processMe.empty) {
        let input = processMe.dequeue();
        let client = activeUsers[input.message.userId];
        client.lastMessageId = input.message.id;
        switch (input.message.type) {
            case NetworkIds.INPUT_MOVE_DOWN:
                client.user.moveDown(input.message.elapsedTime);
                break;
            case NetworkIds.INPUT_MOVE_UP:
                client.user.moveUp(input.message.elapsedTime);
                break;
            case NetworkIds.INPUT_MOVE_LEFT:
                client.user.moveLeft(input.message.elapsedTime);
                break;
            case NetworkIds.INPUT_MOVE_RIGHT:
                client.user.moveRight(input.message.elapsedTime);
                break;
            case NetworkIds.INPUT_ROTATE_LEFT:
                client.user.rotateLeft(input.message.elapsedTime);
                break;
            case NetworkIds.INPUT_ROTATE_RIGHT:
                client.user.rotateRight(input.message.elapsedTime);
                break;
            case NetworkIds.INPUT_FLIP:
                client.user.flipIt(input.message.elapsedTime);
                break;
            case NetworkIds.INPUT_FIRE:
                if(client.user.inventory.ammo > 0){
                    client.user.inventory.ammo -= 1;
                    createMissile(input.message.userId, client.user);
                }else{
                    client.user.inventory.ammo = 0;
                }

                break;
            case NetworkIds.CLICK:
                let world = {
                    width: input.message.width,
                    height: input.message.height
                };
                let x = ((input.message.x/world.width)*4);
                let y = ((input.message.y/world.height)*4);
                client.user.projected.x = x + .5;
                client.user.projected.y = y + .5;
                client.user.worldView.x = x + .5;
                client.user.worldView.y = y + .5;
                let view = {
                    top: y,
                    left: x,
                }
                let position = {
                    x: .5,
                    y: .5,
                }
                let worldPosition = {
                    x: position.x + view.left,
                    y: position.y + view.top
                }
                client.socket.emit(NetworkIds.CONNECT_ACK, {
                    position: position,
                    view: view,
                    userId: input.message.userId
                });
                for (let clientId in activeUsers) {
                    let clientOther = activeUsers[clientId];
                    if (input.message.userId !== clientId) {
                        // Tell existing about the newly connected player
                        clientOther.socket.emit(NetworkIds.RECONNECT_OTHER, {
                            position: worldPosition,
                            userId: input.message.userId,
                            orientation: client.user.orientation,
                        });
                    }
                }
                break;
        }
    }
}

//------------------------------------------------------------------
//
// Utility function to perform a hit test between two objects.  The
// objects must have a position: { x: , y: } property and radius property.
//
//------------------------------------------------------------------
function collided(obj1, obj2) {
    let position = obj1.position;
    if (obj1.hasOwnProperty('type') && obj1.type === 'tree') {
        position = {
            x: obj1.position.x, y: obj1.position.y + obj1.radius
        }
    }
    let distance = Math.sqrt(Math.pow(position.x - obj2.position.x, 2) + Math.pow(position.y - obj2.position.y, 2));
    let radii = obj1.radius + obj2.radius;

    return distance <= radii;
}

function obstacle(user){
    let newCenter = {
        position: {
            x: user.projected.x,
            y: user.projected.y
        },
        radius: user.radius
    };

    for (let index in trees.treeArray){
        let treePosition = {
            position: {
                x: trees.treeArray[index].model.position.x,
                y: trees.treeArray[index].model.position.y
            },
            radius: trees.treeArray[index].model.radius,
            type: 'tree'
        };

        if (collided(treePosition, newCenter)) {
            let deltaX = user.worldView.x - treePosition.position.x;
            let deltaY = (treePosition.position.y + treePosition.radius) - user.worldView.y;
            let objDir = Math.atan2(deltaY, deltaX);
            let vectorX = Math.cos(objDir) * (treePosition.radius + user.radius);
            let vectorY = Math.sin(objDir) * (treePosition.radius + user.radius);

            newCenter.position.x = treePosition.position.x + vectorX;
            newCenter.position.y = (treePosition.position.y + treePosition.radius) - vectorY;
        }
    }

    for (let index in buildings.buildingArray){
        let buildingPosition = {
            position: {
                x: buildings.buildingArray[index].model.position.x,
                y: buildings.buildingArray[index].model.position.y
            },
            radius: buildings.buildingArray[index].model.radius,
            type: 'building'
        };

        if (collided(buildingPosition, newCenter)) {
            let deltaX = user.worldView.x - buildingPosition.position.x;
            let deltaY = buildingPosition.position.y - user.worldView.y;
            let objDir = Math.atan2(deltaY, deltaX);
            let vectorX = Math.cos(objDir) * (buildingPosition.radius + user.radius);
            let vectorY = Math.sin(objDir) * (buildingPosition.radius + user.radius);

            newCenter.position.x = buildingPosition.position.x + vectorX;
            newCenter.position.y = buildingPosition.position.y - vectorY;
        }
    }

    return newCenter.position;
}

function endGame() {
    for (let clientId in activeUsers) {
        db.run('INSERT INTO highscores(score,user) VALUES (?,?)', [Math.floor(activeUsers[clientId].user.points), clientId]);

        if(!activeUsers[clientId].user.dead){
            activeUsers[clientId].user.winner = true;
            activeUsers[clientId].user.points += 1000;
        }
    }
}

//------------------------------------------------------------------
//
// This Kills the player and takes care of player data
//
//------------------------------------------------------------------

function killedPlayer(clientId){
    activeUsers[clientId].user.dead = true;
    io.emit('log message', clientId + ' has been eliminated');
    activeUsers[clientId].user.inventory.ammo = 0;
    activeUsers[clientId].user.inventory.health = 0;
    activeUsers[clientId].user.points += (10*60 - gameTime);
    livingPlayers--;
    io.emit('log message', livingPlayers + ' players remaining');


}

//------------------------------------------------------------------
//
// Update the simulation of the game.
//
//------------------------------------------------------------------
function update(elapsedTime, currentTime) {
    gameTime = (gameTime - elapsedTime/1000);
    if(gameTime < 0 || livingPlayers === 1) {
        if(!gameOver){
            endGame();
        }
        gameOver = true;

    }


    for (let clientId in activeUsers) {
        activeUsers[clientId].user.worldView = obstacle(activeUsers[clientId].user);
        activeUsers[clientId].user.projected = activeUsers[clientId].user.worldView;
    }

    shield.radius = 4*(gameTime/(10*60));
    for (let clientId in activeUsers) {
        activeUsers[clientId].user.update(currentTime);
    }

    for (let missile = 0; missile < newMissiles.length; missile++) {
        newMissiles[missile].update(elapsedTime);
    }

    let keepMissiles = [];
    for (let missile = 0; missile < activeMissiles.length; missile++) {

        if (activeMissiles[missile].update(elapsedTime)) {
            keepMissiles.push(activeMissiles[missile]);
        }
    }
    activeMissiles = keepMissiles;


    // Check to see if any missiles collide with any players (no friendly fire)
    keepMissiles = [];
    for (let missile = 0; missile < activeMissiles.length; missile++) {
        let hit = false;
        for (let clientId in activeUsers) {
            // Don't allow a missile to hit the player it was fired from.
            if (clientId !== activeMissiles[missile].userId) {
                if(!activeUsers[clientId].user.dead){
                    if (collided(activeMissiles[missile], activeUsers[clientId].user)) {
                        hit = true;
                        hits.push({
                            userId: clientId,
                            missileId: activeMissiles[missile].id,
                            position: activeUsers[clientId].user.position,
                            signature: activeMissiles[missile].userId,
                            hitPlayer: true,
                            direction: activeMissiles[missile].direction
                        });


                        if(activeMissiles[missile].missileType < 0){
                            activeUsers[clientId].user.inventory.health -= 5;
                            activeUsers[activeMissiles[missile].userId].user.points += 5;
                        }else if(activeMissiles[missile].missileType < 1){
                            activeUsers[clientId].user.inventory.health -= 10;
                            activeUsers[activeMissiles[missile].userId].user.points += 10;
                        }else{
                            activeUsers[clientId].user.inventory.health -= 20;
                            activeUsers[activeMissiles[missile].userId].user.points += 20;
                        }

                        if(activeUsers[clientId].user.inventory.health < 1){
                            killedPlayer(clientId);
                            activeUsers[activeMissiles[missile].userId].user.points += 500;
                        }

                    }
                }
            }
        }
        for (let index in trees.treeArray){
            if (collided(activeMissiles[missile], trees.treeArray[index].model)) {
                hit = true;
                hits.push({
                    userId: index,
                    missileId: activeMissiles[missile].id,
                    position: trees.treeArray[index].model.position,
                    signature: activeMissiles[missile].userId,
                    hitPlayer: false,
                    direction: activeMissiles[missile].direction
                });
            }
        }
        for (let index in buildings.buildingArray){
            if (collided(activeMissiles[missile], buildings.buildingArray[index].model)) {
                hit = true;
                hits.push({
                    userId: index,
                    missileId: activeMissiles[missile].id,
                    position: buildings.buildingArray[index].model.position,
                    signature: activeMissiles[missile].userId,
                    hitPlayer: false,
                    direction: activeMissiles[missile].direction
                });
            }
        }
        if (!hit) {
            keepMissiles.push(activeMissiles[missile]);
        }
    }
    activeMissiles = keepMissiles;

   // Check if player has picked up items

    for (let clientId in activeUsers) {
        if(!activeUsers[clientId].user.dead){
            let keepPickups = [];   //
            let localPickups = pickups.row[Math.floor(activeUsers[clientId].user.worldView.y)].col[Math.floor(activeUsers[clientId].user.worldView.x)];
                for (let pickup in localPickups) {
                    let hit = false;
                    if (collided(localPickups[pickup], activeUsers[clientId].user)) {
                        hit = true;

                        switch (localPickups[pickup].type) {
                            case "ammo":
                                activeUsers[clientId].user.inventory.ammo += 5;
                                break;
                            case "health":
                                if(activeUsers[clientId].user.inventory.health < 100){
                                    activeUsers[clientId].user.inventory.health = (activeUsers[clientId].user.inventory.health + 10) % 101;
                                }else{
                                    hit = false;
                                }
                                break;
                            case "weapon":
                                if(activeUsers[clientId].user.inventory.weapon < 0){
                                    activeUsers[clientId].user.inventory.weapon = 0;
                                }else{
                                    hit = false;
                                }
                                break;
                            case "upgrade":
                                if(activeUsers[clientId].user.inventory.weapon < 1 && activeUsers[clientId].user.inventory.weapon > -1){
                                    activeUsers[clientId].user.inventory.weapon = 1;
                                }else{
                                    hit = false;
                                }
                                break;
                        }
                    }
                    if (!hit) {
                        keepPickups.push(localPickups[pickup]);
                    }
                }
                pickups.row[Math.floor(activeUsers[clientId].user.worldView.y)].col[Math.floor(activeUsers[clientId].user.worldView.x)] = keepPickups;

                if(!collided({position:shield,radius:shield.radius},activeUsers[clientId].user)) {
                    killedPlayer(clientId);
                }
        }
    }
}

function sameArea(object1, object2){
    if (Math.abs(object1.worldView.x - object2.worldView.x) < .6 &&
        Math.abs(object1.worldView.y - object2.worldView.y) < .6){
        return 0;
    } else if (Math.abs(object1.worldView.x - object2.worldView.x) < .7 &&
        Math.abs(object1.worldView.y - object2.worldView.y) < .7){
        return 1;
    }
    return 2;
}

function getLocalWeapons(client) {
    let posx = client.user.worldView.x;
    let posy = client.user.worldView.y;
    let localWeapons = pickups
    .row[Math.floor(client.user.worldView.y)]
    .col[Math.floor(client.user.worldView.x)];

    if(posx >= 1) {
        localWeapons = localWeapons.concat(
            pickups
            .row[Math.floor(client.user.worldView.y)]
            .col[Math.floor(client.user.worldView.x-1)]
        )
        if(posy >= 1) {
            localWeapons = localWeapons.concat(
                pickups
                .row[Math.floor(client.user.worldView.y-1)]
                .col[Math.floor(client.user.worldView.x-1)]
            )
        }
        if(posy <= 4) {
            localWeapons = localWeapons.concat(
                pickups
                .row[Math.floor(client.user.worldView.y+1)]
                .col[Math.floor(client.user.worldView.x-1)]
            )
        }
    }
    if(posx <= 4) {
        localWeapons = localWeapons.concat(
            pickups
            .row[Math.floor(client.user.worldView.y)]
            .col[Math.floor(client.user.worldView.x+1)]
        )
        if(posy >= 1) {
            localWeapons = localWeapons.concat(
                pickups
                .row[Math.floor(client.user.worldView.y-1)]
                .col[Math.floor(client.user.worldView.x+1)]
            )
        }
        if(posy <= 4) {
            localWeapons = localWeapons.concat(
                pickups
                .row[Math.floor(client.user.worldView.y+1)]
                .col[Math.floor(client.user.worldView.x+1)]
            )
        }
    }
    if(posy >= 1) {
        localWeapons = localWeapons.concat(
            pickups
            .row[Math.floor(client.user.worldView.y-1)]
            .col[Math.floor(client.user.worldView.x)]
        )
    }
    if(posy <= 4) {
        localWeapons = localWeapons.concat(
            pickups
            .row[Math.floor(client.user.worldView.y+1)]
            .col[Math.floor(client.user.worldView.x)]
        )
    }
    return localWeapons;
}

function updateClients(elapsedTime) {
    //
    // For demonstration purposes, network updates run at a slower rate than
    // the game simulation.
    lastUpdate += elapsedTime;
    if (lastUpdate < STATE_UPDATE_RATE_MS) {
        return;
    }

    let missileMessages = [];
    for (let item = 0; item < newMissiles.length; item++) {
        let missile = newMissiles[item];
        missileMessages.push({
            id: missile.id,
            direction: missile.direction,
            position: {
                x: missile.position.x,
                y: missile.position.y
            },
            radius: missile.radius,
            speed: missile.speed,
            acceleration: missile.acceleration,
            timeRemaining: missile.timeRemaining
        });
    }

    // Move all the new missiles over to the active missiles array
    for (let missile = 0; missile < newMissiles.length; missile++) {
        activeMissiles.push(newMissiles[missile]);
    }
    newMissiles.length = 0;

    for (let clientId in activeUsers) {
        let client = activeUsers[clientId];
        let update = {
            clientId: clientId,
            lastMessageId: client.lastMessageId,
            orientation: client.user.orientation,
            worldView: client.user.worldView,
            updateWindow: lastUpdate,
            gameTime: gameTime,
            shield: shield,
            dead: activeUsers[clientId].user.dead,
            ammo: activeUsers[clientId].user.inventory.ammo,
            health: activeUsers[clientId].user.inventory.health,
            weapon: activeUsers[clientId].user.inventory.weapon,
            winner: activeUsers[clientId].user.winner,
            done: gameOver
        };
        if (client.user.reportUpdate) {
            update.pickups = getLocalWeapons(client);
            client.socket.emit(NetworkIds.UPDATE_SELF, update);
            client.user.reportUpdate = false;
        }

        if(gameOver) {
            quit = true;
        }

        for (let otherId in activeUsers) {
            let inBoundary = sameArea(client.user, activeUsers[otherId].user);
            if (otherId !== clientId && !inBoundary) {
                activeUsers[otherId].socket.emit(NetworkIds.UPDATE_OTHER, update);
                // Report any missile hits to this client

            } else if (otherId !== clientId && inBoundary === 1) {
                activeUsers[otherId].socket.emit(NetworkIds.UPDATE_OTHER_DELETE, update);
            }
        }
        for (let hit = 0; hit < hits.length; hit++) {
            client.socket.emit(NetworkIds.MISSILE_HIT, hits[hit]);
        }
        for (let missile = 0; missile < missileMessages.length; missile++) {
            client.socket.emit(NetworkIds.MISSILE_NEW, missileMessages[missile]);
        }
    }

    for (let clientId in activeUsers) {
        activeUsers[clientId].user.reportUpdate = true;
    }

    hits.length = 0;
    lastUpdate = 0;
}

function initializeShield() {
    shield.x = Math.random() * 3 + 1;
    shield.y = Math.random() * 3 + 1;
    shield.radius = 4;
}

function initializePickups() {
    pickups.row = [];
    for(let r = 0; r < 5; r++) {
        pickups.row.push({col:[]})
        for(let c = 0; c < 5; c++) {
            pickups.row[r].col.push([]);
        }
    }
}

function placePickups() {

    for (let i = 0; i < connections*2; i++) {
        let tempx = Math.random() * (5-2/3) + 1/3;
        let tempy = Math.random() * (5-2/3) + 1/3;
        let tempPosition = {x: tempx, y: tempy};
        pickups.row[Math.floor(tempy)].col[Math.floor(tempx)].push({position: tempPosition, texture:'purpleCarrot.png', type:'health', width: 0.025, height: 0.025, radius: 0.025});
    }


    for (let i = 0; i < connections*10; i++) {
        let tempx = Math.random() * (5-2/3) + 1/3;
        let tempy = Math.random() * (5-2/3) + 1/3;
        let tempPosition = {x: tempx, y: tempy};
        pickups.row[Math.floor(tempy)].col[Math.floor(tempx)].push({position: tempPosition, texture:'orangeCarrot.png', type:'ammo', width: 0.025, height: 0.025, radius: 0.025});
    }


    for (let i = 0; i < connections*1.5; i++) {
        let tempx = Math.random() * (5-2/3) + 1/3;
        let tempy = Math.random() * (5-2/3) + 1/3;
        let tempPosition = {x: tempx, y: tempy};
        pickups.row[Math.floor(tempy)].col[Math.floor(tempx)].push({position: tempPosition, texture:'bazooka1.png', type:'weapon', width: 0.075, height: 0.05, radius: 0.025});
    }


    for (let i = 0; i < connections/2; i++) {
        let tempx = Math.random() * (5-2/3) + 1/3;
        let tempy = Math.random() * (5-2/3) + 1/3;
        let tempPosition = {x: tempx, y: tempy};
        pickups.row[Math.floor(tempy)].col[Math.floor(tempx)].push({position: tempPosition, texture:'upgradeWeapon.png', type:'upgrade', width: 0.075, height: 0.05, radius: 0.025});
    }

}

//------------------------------------------------------------------
//
// Server side game loop
//
//------------------------------------------------------------------
function gameLoop(currentTime, elapsedTime) {
    processInput(elapsedTime);
    update(elapsedTime, currentTime);
    updateClients(elapsedTime);

    if (!quit) {
        setTimeout(() => {
            let now = present();
            gameLoop(now, now - currentTime);
        }, SIMULATION_UPDATE_RATE_MS);
    }
}



//------------------------------------------------------------------
//
// Get the socket.io server up and running so it can begin
// collecting inputs from the connected clients.
//
//------------------------------------------------------------------
function initializeSocketIO(http) {

    io = require('socket.io')(http);

    function runCountdown() {
        var target_date = new Date().getTime() + (10*1000);
        var seconds, pastSeconds = 0;
        // update the tag with id "countdown" every 1 second
        var refresh = setInterval(function () {

            // find the amount of "seconds" between now and target
            var current_date = new Date().getTime();
            var seconds_left = (target_date - current_date + 1) / 1000;
            seconds = parseInt(seconds_left % 60);

            if (pastSeconds !== seconds) {
                io.emit('start game', seconds.toString());
                pastSeconds = seconds;
            }
            if (seconds === 0){
                io.emit('start game', 'countdown finished');
                clearInterval(refresh);
                reconnection = true;
                gameTime = 10 * 60;
                placePickups();
                livingPlayers = connections;
                gameInProgress = true;
            }
        }, 1000);
    }

    function notifyConnect(socket, newUser) {
        for (let clientId in activeUsers) {
            let client = activeUsers[clientId];
            if (newUser.userId !== clientId) {
                // Tell existing about the newly connected player
                client.socket.emit(NetworkIds.CONNECT_OTHER, {
                    userId: newUser.userId,
                    orientation: newUser.orientation,
                });

                // Tell the new player about the already connected player
                socket.emit(NetworkIds.CONNECT_OTHER, {
                    userId: client.user.userId,
                    orientation: client.user.orientation,
                });
            }
        }
    }

    function notifyReconnect(socket, newUser) {
        activeUsers[newUser.userId].socket.emit(NetworkIds.RECONNECT_SELF, {
            clientId: newUser.clientId,
            lastMessageId: activeUsers[newUser.userId].lastMessageId,
            orientation: activeUsers[newUser.userId].user.orientation,
            worldView: activeUsers[newUser.userId].user.worldView,
            userId: newUser.userId
        });

        for (let clientId in activeUsers) {
            let client = activeUsers[clientId];
            if (newUser.userId !== clientId) {
                // Tell existing about the newly connected player
                client.socket.emit(NetworkIds.RECONNECT_OTHER, {
                    clientId: newUser.clientId,
                    lastMessageId: newUser.lastMessageId,
                    orientation: newUser.orientation,
                    worldView: newUser.worldView,
                    userId: newUser.userId
                });

                // Tell the new player about the already connected player
                socket.emit(NetworkIds.RECONNECT_OTHER, {
                    clientId: clientId,
                    lastMessageId: client.lastMessageId,
                    orientation: client.user.orientation,
                    worldView: client.user.worldView,
                    userId: client.user.userId
                });
            }
        }
    }

    io.on('connection', function(socket){
        socket.on('join', function(data){
            //console.log(data.name + ' with id ' + socket.id + ' connected');
            if(reconnection) {
                if(typeof activeUsers[data.name] !== 'undefined') {
                    activeUsers[data.name].dead = false;
                    activeUsers[data.name].socket = socket;
                    activeUsers[data.name].id = socket.id;
                    activeUsers[data.name].user.clientId = socket.id;
                    notifyReconnect(socket, activeUsers[data.name].user);
                    io.sockets.sockets[socket.id].emit('start game', "player reconnect");
                    io.emit('chat message',data.name + ' has rejoined the game.');
                } else {
                    io.emit('chat message', "Game already in progress.")
                }
            } else {
                io.emit('chat message',data.name + ' has joined the game.');
                let newUser = User.makeplayer();
                newUser.clientId = socket.id;
                newUser.userId = data.name;
                activeUsers[data.name] = {
                    id: socket.id,
                    socket: socket,
                    user: newUser
                };

                socket.emit(NetworkIds.CONNECT_ACK, {
                    position: newUser.myPosition,
                    view: newUser.view,
                    userId: newUser.userId
                });

                notifyConnect(socket, newUser);

                connections++;
                if (connections >= TARGET_USERS_NUM) {
                    if (!game_started) runCountdown();
                    game_started = true;
                }
            }

            socket.on('chat message', function(msg){
                io.emit('chat message', data.name + ": " + msg);
            });

            socket.on(NetworkIds.INPUT, keyInput => {
                inputQueue.enqueue({
                    clientId: socket.id,
                    message: keyInput
                });
            });

            socket.on('disconnect', function(){
                // notifyDisconnect(socket.id);
                //delete activeClients[socket.id];
                connections--;
                //console.log(data.name + ' with id ' + socket.id + ' disconnected');
                io.emit('chat message', data.name + ' has left the game');
            });

        });
    });
}

function createObstacles() {
    trees = User.makeTrees();
    buildings = User.makeBuildings();
}

function initialize(http) {
    initializeSocketIO(http);
    initializeShield();
    createObstacles();
    initializePickups();
    gameLoop(present(), 0);
}

//------------------------------------------------------------------
//
// Public function that allows the game simulation and processing to
// be terminated.
//
//------------------------------------------------------------------
function terminate() {
    this.quit = true;
}

module.exports.initialize = initialize;
