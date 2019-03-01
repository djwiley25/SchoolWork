Rocket.main = (function(input, logic, graphics, assets) {

    let socketIO = null;
    let deadSound = new Audio('/audio/Explosion_03.mp3');
    let beenDead = false;

    let keyboard = input.Keyboard(), lastTimeStamp, messageId = 1,
        myPlayer = {
            model: logic.Player(),
            sprite: logic.Sprite({
                spriteSheet: 'bunnysheet.png',
                spriteCount: 8,
                me: true,
                spriteSize: .05,			// Maintain the size on the sprite
            }, graphics)},
        background = null,
        initialized = false,
        mini = graphics.miniMap(),
        jobQueue = logic.createQueue(),
        otherUsers = [],
        missiles = {},
        hits = [],
        pregame = true,
        gameCount = 0,
        gameTime = 10 * 60, //seconds
        shield = {x:0,y:0,radius:0,particles:[]},
        pickups = [],
        worldParams = {
            height: 5,
            width: 5
        },
        OBSTACLE_COUNT = {
            treeNum: 8,
            buildingNum: 4
        },
        treeArray = [],
        buildingArray = [],
        treeIndex = [ [1, .5], [.5, 2.75], [1.5, 4.5], [2.3, 2.5], [2.5, 2.3], [3.25, 2], [4.5, 2.5], [3.5, 4]],
        buildingIndex = [ [1.75, 1], [4, 1], [2.75, 2.75], [4.3, 3]],
        myId;

        for(let a = 0; a < 2*Math.PI; a+=((2*Math.PI)/360)) {
            shield.particles.push(logic.ParticleSystem({
                position: {
                    x: shield.x + Math.cos(a)*shield.radius,
                    y: shield.y + Math.sin(a)*shield.radius
                },
                size: .005,
                speed: .05,
                lifetime: 1500,
                fill: 'rgba(0, 0, 255, 0.5)',
                direction: 0,
                theta: Math.PI
                }, graphics)
            )
        }

    function network() {
        socketIO.on(NetworkIds.CONNECT_ACK, data => {
            jobQueue.enqueue({
                type: NetworkIds.CONNECT_ACK,
                data: data
            });
        });

        socketIO.on(NetworkIds.CONNECT_OTHER, data => {
            jobQueue.enqueue({
                type: NetworkIds.CONNECT_OTHER,
                data: data
            });
        });

        socketIO.on(NetworkIds.RECONNECT_SELF, data => {
            jobQueue.enqueue({
                type: NetworkIds.RECONNECT_SELF,
                data: data
            });
        });

        socketIO.on(NetworkIds.RECONNECT_OTHER, data => {
            jobQueue.enqueue({
                type: NetworkIds.RECONNECT_OTHER,
                data: data
            });
        });

        socketIO.on(NetworkIds.UPDATE_OTHER, data => {
            jobQueue.enqueue({
                type: NetworkIds.UPDATE_OTHER,
                data: data
            });
        });

        socketIO.on(NetworkIds.UPDATE_SELF, data => {
            jobQueue.enqueue({
                type: NetworkIds.UPDATE_SELF,
                data: data
            });
        });

        socketIO.on(NetworkIds.UPDATE_OTHER_DELETE, data => {
            jobQueue.enqueue({
                type: NetworkIds.UPDATE_OTHER_DELETE,
                data: data
            });
        });

        socketIO.on(NetworkIds.MISSILE_NEW, data => {
            jobQueue.enqueue({
                type: NetworkIds.MISSILE_NEW,
                data: data
            });
        });

        socketIO.on(NetworkIds.MISSILE_HIT, data => {
            jobQueue.enqueue({
                type: NetworkIds.MISSILE_HIT,
                data: data
            });
        });
    }

    function playerHits(data) {
        let position = drawObjects(data.position);
        delete missiles[data.missileId];
        if (position){
            hits.push({
                particle: logic.ParticleSystem({
                    position: {
                        x: data.position.x,
                        y: data.position.y
                    },
                    size: .0075,
                    speed: .2,
                    lifetime: 200,
                    fill: 'rgba(255, 0, 0, 0.5)',
                    direction: data.direction - Math.PI,
                    theta: Math.PI/4
                }, graphics),
                life: 200
            });
        }
        if (data.userId === myPlayer.model.userId) {
            hits.push({
                particle: logic.ParticleSystem({
                    position: {
                        x: data.position.x,
                        y: data.position.y
                    },
                    size: .005,
                    speed: .2,
                    lifetime: 200,
                    fill: 'rgba(255, 0, 0, 0.5)',
                    direction: data.direction - Math.PI,
                    theta: Math.PI/4
                }, graphics),
                life: 200
            });
        }
    }

    function objectHits(data) {
        let position = drawObjects(data.position, true);
        delete missiles[data.missileId];
        if (position){
            hits.push({
                particle: logic.ParticleSystem({
                    position: {
                        x: data.position.x,
                        y: data.position.y
                    },
                    size: .005,
                    speed: .15,
                    lifetime: 400,
                    fill: 'rgba(0, 0, 0, 0.5)',
                    direction: data.direction - Math.PI,
                    theta: Math.PI
                }, graphics),
                life: 500
            });
        }
    }

    function missileNew(data) {
        missiles[data.id] = logic.Missile({
            id: data.id,
            radius: data.radius,
            speed: data.speed,
            acceleration: data.acceleration,
            direction: data.direction,
            position: {
                x: data.position.x,
                y: data.position.y
            },
            timeRemaining: data.timeRemaining
        });
        if (data.acceleration > 1){
            missiles[data.id].particle = logic.ParticleSystem({
                position: {
                    x: data.position.x,
                    y: data.position.y
                },
                size: .005,
                speed: data.speed/4,
                lifetime: 300,
                fill: 'rgba(0, 255, 0, 0.5)',
                direction: data.direction - Math.PI,
                theta: (Math.PI/4)
            }, graphics);
        }
    }

    function updateMsgs(){
        let processMe = jobQueue;
        jobQueue = jobQueue = logic.createQueue();
        while (!processMe.empty) {
            let message = processMe.dequeue();
            switch (message.type) {
                case NetworkIds.CONNECT_ACK:
                    connectPlayerSelf(message.data);
                    break;
                case NetworkIds.CONNECT_OTHER:
                    connectPlayerOther(message.data);
                    break;
                case NetworkIds.RECONNECT_SELF:
                    reconnectPlayerSelf(message.data);
                    break;
                case NetworkIds.RECONNECT_OTHER:
                    reconnectPlayerOther(message.data);
                    break;
                case NetworkIds.UPDATE_OTHER:
                    updateOthers(message.data);
                    break;
                case NetworkIds.UPDATE_SELF:
                    updateSelf(message.data);
                    break;
                case NetworkIds.UPDATE_OTHER_DELETE:
                    untrack(message.data);
                    break;
                case NetworkIds.MISSILE_NEW:
                    missileNew(message.data);
                    playrlaunch();
                    break;
                case NetworkIds.MISSILE_HIT:
                    if (!message.data.hitPlayer) {
                        objectHits(message.data);
                    } else {
                        playerHits(message.data);
                        playerHitAudio();
                    }
                    break;
            }
        }
    }

    function updateSelf(data) {
        if(data.hasOwnProperty('winner')) {
            if(data.winner){
                let fanfair = new Audio('/audio/round_end.mp3');
                fanfair.play();
                alert("Congratulations! You are the winner!");
            }
        }
        if(data.hasOwnProperty('done')) {
            if(data.done){
                document.getElementById('id-highscores').hidden = false;
                document.getElementById('id-game').hidden = true;

                let req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open("GET", "/highscores");
                req.onload  = function() {
                  var rows = req.response;
                  // do something with jsonResponse
                  document.getElementById('id-scores-list').innerHTML = "";
                  for(var row in rows){
                    var node = document.createElement("li");
                    var rowString = parseInt(row) + 1;
                    var textnode = document.createTextNode(rowString + ". " + rows[row].score + " - " + rows[row].user);
                    node.appendChild(textnode);
                    node.className = "list-group-item"
                    //node.className = "list-group-item justify-content-between align-items-center";
                    document.getElementById("id-scores-list").appendChild(node);
                  }
               };
                req.send();
            }

        }
        if (data.hasOwnProperty('weapon')){
            myPlayer.model.weapon = data.weapon;
        }
        if (data.hasOwnProperty('health')){
            myPlayer.model.health = data.health;
        }
        if (data.hasOwnProperty('ammo')){
            myPlayer.model.ammo = data.ammo;
        }
        if (data.dead){
            myPlayer.model.dead = data.dead;
        }
        gameTime = data.gameTime;
        data.shield.particles = shield.particles;
        shield = data.shield;
        pickups = data.pickups;
    }

    function connectPlayerOther(data) {
        let model = logic.OtherPlayer();
        otherUsers[data.userId] = {
            model: model,
            texture: 'bunny.png',
            sprite: logic.Sprite({
                spriteSheet: 'bunnysheet.png',
                spriteCount: 8,
                me: false,
                spriteSize: .05,			// Maintain the size on the sprite
            }, graphics)
        };
    }

    function reconnectPlayerOther(data) {
        let model = logic.OtherPlayer();
        model.state.orientation = data.orientation;
        model.map = data.position;
        otherUsers[data.userId] = {
            model: model,
            texture: 'bunny.png',
            sprite: logic.Sprite({
                spriteSheet: 'bunnysheet.png',
                spriteCount: 8,
                me: false,
                spriteSize: .05,			// Maintain the size on the sprite
            }, graphics)
        };
    }

    function reconnectPlayerSelf(data) {
        myPlayer.model.orientation = data.orientation;
        let x, y, vx, vy;
        //set y
        if (data.worldView.y < .5) {
            y = data.worldView.y;
            vy = 0;
        } else if (data.worldView.y > 4.5) {
            y = data.worldView.y - 4;
            vy = 4;
        } else {
            y = .5;
            vy = data.worldView.y - .5;
        }
        // set x
        if (data.worldView.x < .5) {
            x = data.worldView.x;
            vx = 0;
        } else if (data.worldView.x > 4.5) {
            x = data.worldView.x - 4;
            vx = 4;
        } else {
            x = .5;
            vx = data.worldView.x - .5;
        }
        background.setViewport(vx,vy);
        myPlayer.model.position.x = x;
        myPlayer.model.position.y = y;
    }

    function connectPlayerSelf(data) {
        myPlayer.model.userId = data.userId;
        myPlayer.model.position.x = data.position.x;
        myPlayer.model.position.y = data.position.y;
        myPlayer.model.projected.x = data.position.x;
        myPlayer.model.projected.y = data.position.y;
        background.setViewport(data.view.left, data.view.top);
    }

    function untrack(data) {
        if (otherUsers.hasOwnProperty(data.clientId)) {
            let model = otherUsers[data.clientId].model;
            delete model.state.position.x;
            delete model.state.position.y;
        }
    }

    function updateOthers(data) {
        dead = data.dead;
        if (otherUsers.hasOwnProperty(data.clientId)) {
            let model = otherUsers[data.clientId].model;
            model.goal.updateWindow = data.updateWindow;

            if (!model.state.position.hasOwnProperty('x')){
                model.state.position.x = data.worldView.x;
                model.state.position.y = data.worldView.y;
            }
            model.goal.position.x = data.worldView.x;

            model.goal.position.y = data.worldView.y;
            model.goal.orientation = data.orientation;
            model.state.dead = dead;
        }
    }

    function shiftView(position, elapsedTime) {
        let newCenter = {
                x: position.x,
                y: position.y
            }, vector = null;

        if (position.x >= (1 - (1/3)) || position.x <= (1/3)) {
            let x;
            if (position.x >= (1 - (1/3))) {
                newCenter.x = (1 - (1/3));
                x = Math.abs(newCenter.x - position.x);
            } else {
                newCenter.x = (1/3);
                x = Math.abs(newCenter.x - position.x)* (-1);
            }
            vector = { x: x, y: 0 };
            background.move(vector);
        }
        if (position.y >= (1 - (1/3)) || position.y <= (1/3)) {
            let y;
            if (position.y >= (1 - (1/3))) {
                newCenter.y = (1 - (1/3));
                y = Math.abs(newCenter.y - position.y);
            } else {
                newCenter.y = (1/3);
                y = Math.abs(newCenter.y - position.y)* (-1);
            }
            vector = { x: 0, y: y };
            background.move(vector);
        }
        position.x = newCenter.x;
        position.y = newCenter.y;
    }

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

    function obstacle(){
        let newCenter = {
            position: {
                x: myPlayer.model.projected.x,
                y: myPlayer.model.projected.y
            },
            radius: myPlayer.model.radius
        };

        for (let index in treeArray){
            let position = drawObjects(treeArray[index].model.position, true);
            if (position.hasOwnProperty('x')) {
                let treePosition = {
                    position: {
                        x: position.x,
                        y: position.y
                    },
                    radius: treeArray[index].model.radius,
                    type: 'tree'
                };

                if (collided(treePosition, newCenter)) {
                    let deltaX = myPlayer.model.position.x - treePosition.position.x;
                    let deltaY = (treePosition.position.y + treePosition.radius) - myPlayer.model.position.y;
                    let objDir = Math.atan2(deltaY, deltaX);
                    let vectorX = Math.cos(objDir) * (treePosition.radius + myPlayer.model.radius);
                    let vectorY = Math.sin(objDir) * (treePosition.radius + myPlayer.model.radius);

                    newCenter.position.x = treePosition.position.x + vectorX;
                    newCenter.position.y = (treePosition.position.y + treePosition.radius) - vectorY;
                }
            }
        }

        for (let index in buildingArray){
            let position = drawObjects(buildingArray[index].model.position, true);
            if (position.hasOwnProperty('x')) {
                let buildingPosition = {
                    position: {
                        x: position.x,
                        y: position.y
                    },
                    radius: buildingArray[index].model.radius,
                    type: 'building'
                };

                if (collided(buildingPosition , newCenter)) {
                    let deltaX = myPlayer.model.position.x - buildingPosition .position.x;
                    let deltaY = buildingPosition.position.y - myPlayer.model.position.y;
                    let objDir = Math.atan2(deltaY, deltaX);
                    let vectorX = Math.cos(objDir) * (buildingPosition.radius + myPlayer.model.radius);
                    let vectorY = Math.sin(objDir) * (buildingPosition.radius + myPlayer.model.radius);

                    newCenter.position.x = buildingPosition.position.x + vectorX;
                    newCenter.position.y = buildingPosition.position.y - vectorY;
                }
            }
        }

        return newCenter.position;
    }

    function gameClock(gameTime) {
        let gameSeconds = Math.floor(gameTime%60);
        let gameMinutes = Math.floor(gameTime/60).toString();
        if ( gameSeconds < 10){
            gameSeconds = '0'+gameSeconds.toString();
        }
        return gameMinutes + ':' + gameSeconds.toString();
    }

    function update(elapsedTime){
        updateMsgs();
        if (pregame) {
            if (isNaN(gameCount)){
                gameCount = 0;
            }
            gameCount += elapsedTime;
            if (gameCount > 10000 && !initialized){
                document.addEventListener("click", printMousePos);
            }
            if (gameCount > 20000) {
                pregame = false;
                document.removeEventListener("click", printMousePos);
                update(elapsedTime);
            }
        }
        shiftView(myPlayer.model.position, elapsedTime);
        myPlayer.model.position = obstacle();
        myPlayer.model.projected = myPlayer.model.position;
        for (let index in otherUsers){
            otherUsers[index].model.update(elapsedTime);
            otherUsers[index].sprite.update(elapsedTime);
        }
        myPlayer.sprite.update(elapsedTime);

        for (let index in hits){
            hits[index].life -= elapsedTime;
            hits[index].particle.update(elapsedTime);
            if (hits[index].life < 0) {
                hits.splice(index, 1);
            }
        }

        let removeMissiles = [];
        for (let missile in missiles) {
            if (!missiles[missile].update(elapsedTime)) {
                removeMissiles.push(missiles[missile]);
            } else if (missiles[missile].particle) {
                missiles[missile].particle.setPosition(missiles[missile].position.x, missiles[missile].position.y);
                missiles[missile].particle.update(elapsedTime);
            }
        }

        for(let a = 0; a < shield.particles.length; a++) {
            let angle = a*(2*Math.PI/360);
            shield.particles[a].setPosition(shield.x+ Math.cos(angle)*shield.radius,shield.y+ Math.sin(angle)*shield.radius);
            shield.particles[a].update(elapsedTime);
        }

        for (let missile = 0; missile < removeMissiles.length; missile++) {
            delete missiles[removeMissiles[missile].id];
        }
    }

    function processInput(elapsedTime){
        keyboard.update(elapsedTime);
    }

    function drawObjects(object, FOVIndifferent){
        if (object.x - background.viewport.left < 1 &&
            object.y - background.viewport.top < 1 &&
            object.x - background.viewport.left > 0 &&
            object.y - background.viewport.top > 0){
            let position = {
                y: object.y - background.viewport.top,
                x: object.x - background.viewport.left
            };
            if (FOVIndifferent !== undefined) {
                return position;
            }
            let deltaX = position.x - myPlayer.model.position.x;
            let deltaY = position.y - myPlayer.model.position.y;
            let objDir = Math.atan2(deltaY,deltaX);
            //find if they are in my view
            if (objDir <= 0) {
                objDir += (2*Math.PI);
            }
            let viewCheck = myPlayer.model.orientation % (2*Math.PI);
            if (viewCheck < 0) viewCheck += (2*Math.PI);
            let thetaMin = viewCheck - Math.PI*(3/8);
            if (thetaMin < 0){
                thetaMin += (2*Math.PI);
            }
            let thetaMax = viewCheck + Math.PI*(3/8);
            if (thetaMax >= (Math.PI*2)) {
                thetaMax -= (Math.PI*2);
            }
            if (objDir > thetaMin && objDir < thetaMax) {
                return position;
            } else if (thetaMax < thetaMin && objDir > thetaMin && objDir > thetaMax) {
                return position;
            } else if (thetaMax < thetaMin && objDir < thetaMin && objDir < thetaMax) {
                return position;
            }
        }
        return false;
    }

    function render(){
        graphics.clear();
        if (pregame){
            graphics.drawGame();
            let myPosition = {
                x: (myPlayer.model.position.x + background.viewport.left)/5,
                y: (myPlayer.model.position.y + background.viewport.top)/5,
            }
            graphics.drawPeople(myPosition);
            for (let index in otherUsers){
                let position = {
                    x: otherUsers[index].model.map.x/5,
                    y: otherUsers[index].model.map.y/5
                }
                graphics.drawPeople(position);
            }
            return;
        }
        background.render();

        for (let index in otherUsers){
            let object = otherUsers[index].model.state.position;
            if (!object.hasOwnProperty('x')) continue;
            let position = drawObjects(object);
            if(!otherUsers[index].model.state.dead){
                if (position.hasOwnProperty('x')){
                    otherUsers[index].sprite.render(position, otherUsers[index].model.state.orientation);
                    // graphics.draw(otherUsers[index].texture, position,
                    //     otherUsers[index].model.size, otherUsers[index].model.state.orientation, false)
                }
            }
        }
        for (let missile in missiles){
            let position = drawObjects(missiles[missile].position);
            if (position.hasOwnProperty('x')){
                graphics.drawMissile(position, missiles[missile].direction, 'orange');
                if (missiles[missile].particle){
                    missiles[missile].particle.render(background.viewport);
                }
                //rflying.play();
            }
        }
        for (let pickup in pickups){
            let position = drawObjects(pickups[pickup].position);
            if (position.hasOwnProperty('x')){
                graphics.draw(pickups[pickup].texture, position, {width: pickups[pickup].width,height: pickups[pickup].height},0,false);
            }
        }

        for (let building in buildingArray){
            let position = drawObjects(buildingArray[building].model.position, true);
            if (position.hasOwnProperty('x')){
                graphics.draw(buildingArray[building].texture, position,
                    buildingArray[building].model.size, buildingArray[building].model.orientation, false)
            }
        }

        // draw self
        if(myPlayer.model.dead){
            if(!beenDead){
                beenDead = true;
                deadSound.play();
            }

            graphics.draw('tombstone.png', myPlayer.model.position, myPlayer.model.size, myPlayer.model.orientation, false);
        }else{
            myPlayer.sprite.render(myPlayer.model.position, myPlayer.model.orientation);
            if (myPlayer.model.weapon >= 0) {
                let vectorX = Math.cos(myPlayer.model.orientation) * (myPlayer.model.radius*1.75);
                let vectorY = Math.sin(myPlayer.model.orientation) * (myPlayer.model.radius*1.75);
                let position = {
                    x: myPlayer.model.position.x + vectorX,
                    y: myPlayer.model.position.y + vectorY
                }
                if (myPlayer.model.weapon){
                    let size = {
                        width: .04,
                        height: .04
                    }
                    graphics.draw('bazooka2.png', position, size, myPlayer.model.orientation, false);
                } else {
                    let size = {
                        width: .05,
                        height: .01
                    }
                    graphics.draw('bazooka1.png', position, size, myPlayer.model.orientation, false);
                }
            }
        }

        for (let tree in treeArray){
            let position = drawObjects(treeArray[tree].model.position, true);
            if (position.hasOwnProperty('x')){
                graphics.draw(treeArray[tree].texture, position,
                    treeArray[tree].model.size, treeArray[tree].model.orientation, false)
            }
        }

        for (let index in hits){
            hits[index].particle.render(background.viewport);
        }
        graphics.drawShield(shield, background.viewport);

        for (let particle = 0; particle<shield.particles.length; particle += (5-Math.ceil(shield.radius))) {
            let position = drawObjects(shield.particles[particle].position, true);
            if (position.hasOwnProperty('x')){
                shield.particles[particle].render(background.viewport)
            }
        }

        mini.drawMini();
        mini.drawPosition(myPlayer.model.position, background.viewport, background.size);
        mini.drawShield(shield, background.viewport, background.size);

        document.getElementById('field-clock').innerHTML = gameClock(gameTime);
        document.getElementById('health-display').innerHTML = "Health: " + myPlayer.model.health;
        document.getElementById('ammo-display').innerHTML = "Ammo: " + myPlayer.model.ammo;
    }

    function gameLoop(time) {
        let elapsedTime = time - lastTimeStamp;
        lastTimeStamp = time;

        processInput(elapsedTime);
        update(elapsedTime);
        render();

        requestAnimationFrame(gameLoop);
    };

    function makeTrees() {
        for (let i = 0; i < OBSTACLE_COUNT.treeNum; i++){
            treeArray.push( {
                model: {
                    position : {
                        x: treeIndex[i][0],
                        y: treeIndex[i][1]
                    },
                    size: {
                        height: .4,
                        width: .2
                    },
                    radius: .1,
                    orientation: 0,
                    type: 'tree'
                },
                texture: 'trees.png',
                id: i+1
            });
        }
    }

    function makeBuildings() {
        for (let i = 0; i < OBSTACLE_COUNT.buildingNum; i++){
            buildingArray.push( {
                model: {
                    position : {
                        x: buildingIndex[i][0],
                        y: buildingIndex[i][1]
                    },
                    size: {
                        height: .5,
                        width: .5
                    },
                    radius: .25,
                    orientation: 0,
                    type: 'building'
                },
                texture: 'barn.png',
                id: i+1
            });
        }
    }

    function playrlaunch(){
        if(myPlayer.model.weapon<0){
            let sfx_throw = new Audio('/audio/sfx_throw.mp3');
            sfx_throw.play();
        }else if(myPlayer.model.weapon < 1){
            let iceball = new Audio('/audio/iceball.mp3');
            iceball.play();
        }else{
            let rlaunch = new Audio('/audio/rlaunch.mp3');
            rlaunch.play();
        }

    }

    function playerHitAudio(){
        let playerHits = new Audio('/audio/Explosion_02.mp3');
        playerHits.play();
    }

    function createObstacles() {
        makeTrees();
        makeBuildings();
    }

    function printMousePos(event) {
        let message = {
            id: messageId++,
            type: NetworkIds.CLICK,
            userId: myId,
            x: event.clientX,
            y: event.clientY,
            width: document.getElementById('canvas-pregame').width,
            height: document.getElementById('canvas-pregame').height
        };
        socketIO.emit(NetworkIds.INPUT, message);
    }

    function init(socket, userId) {
        myId = userId;
        socketIO = socket;
        background = graphics.TiledImage({
            pixel: { width: assets['background'].width, height: assets['background'].height },
            size: { width: worldParams.width, height: worldParams.height },
            tileSize: assets['background'].tileSize,
            assetKey: 'background'
        });

        background.setViewport(0.00, 0.00);
        graphics.createImage('bunny.png');
        graphics.createImage('bunnysheet.png');
        graphics.createImage('2000x2000map.png');
        graphics.createImage('carrot.png');
        graphics.createImage('bazooka1.png');
        graphics.createImage('bazooka2.png');
        graphics.createImage('upgradeWeapon.png');
        graphics.createImage('orangeCarrot.png');
        graphics.createImage('purpleCarrot.png');
        graphics.createImage('explode.png');
        graphics.createImage('trees.png');
        graphics.createImage('barn.png');
        graphics.createImage('tombstone.png');
        graphics.initGraphics();
        createObstacles();

        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_MOVE_UP,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
                // messageHistory.enqueue(message);
                myPlayer.model.moveUp(elapsedTime);
            },
            localStorage.getItem("move-up"), true);

        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_MOVE_DOWN,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
                // messageHistory.enqueue(message);
                myPlayer.model.moveDown(elapsedTime);
            },
            localStorage.getItem("move-down"), true);

        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_MOVE_LEFT,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
                // messageHistory.enqueue(message);
                myPlayer.model.moveLeft(elapsedTime);
            },
            localStorage.getItem("move-left"), true);


        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_MOVE_RIGHT,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
                // messageHistory.enqueue(message);
                myPlayer.model.moveRight(elapsedTime);
            },
            localStorage.getItem("move-right"), true);

        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_ROTATE_RIGHT,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
                // messageHistory.enqueue(message);
                myPlayer.model.rotateRight(elapsedTime);
            },
            localStorage.getItem("rotate-right"), true);

        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_FLIP,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
                // messageHistory.enqueue(message);
                myPlayer.model.flipIt(elapsedTime);
            },
            localStorage.getItem("flip"), false);

        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_ROTATE_LEFT,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
                // messageHistory.enqueue(message);
                myPlayer.model.rotateLeft(elapsedTime);
            },
            localStorage.getItem("rotate-left"), true);

        keyboard.registerHandler(elapsedTime => {
                let message = {
                    id: messageId++,
                    elapsedTime: elapsedTime,
                    type: NetworkIds.INPUT_FIRE,
                    userId: userId
                };
                socket.emit(NetworkIds.INPUT, message);
            },
            localStorage.getItem("fire"), false);

        network();
        requestAnimationFrame(gameLoop);
    }

return {
    init : init
};

}(Rocket.input, Rocket.logic, Rocket.graphics, Rocket.assets));

