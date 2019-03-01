
Breakout.Particles = (function(){

	var that = {};
	var particles = {};
	var nextID = 1;

	that.render = function(context) {
		var particle;
		var value;

		// console.log(context);

		for (value in particles) {
			if (particles.hasOwnProperty(value)) {
				particle = particles[value];
				context.fillStyle = '#DDDDDD';
				context.fillRect(particle.center.x, particle.center.y, 
					2, 2);
				// console.log('rendering particle');
				// console.log(particle.center);
			}
		}


	}

	that.create = function(spec) {
		var p = {
				size: {width: 2, height: 2},
				center: {x: spec.center.x, y: spec.center.y},
				direction: {vX: Math.random() - 0.5, vY: 1},
				speed: spec.center.y * 0.02 * Math.random(), // pixels per second
				rotation: 0,
				lifetime: 1,	// How long the particle should live, in seconds
				alive: 0	// How long the particle has been alive, in seconds
			};

		// Assign a unique name to each particle
		particles[nextID++] = p;
	};

	that.update = function(elapsedTime) {
		var removeMe = [],
			value,
			particle;
			
		//
		// We work with time in seconds, elapsedTime comes in as milliseconds
		elapsedTime = elapsedTime / 1000;
		
		for (value in particles) {
			if (particles.hasOwnProperty(value)) {
				particle = particles[value];
				//
				// Update how long it has been alive
				particle.alive += elapsedTime;
				
				//
				// Update its position
				particle.center.x += (elapsedTime * particle.speed * particle.direction.vX);
				particle.center.y += (elapsedTime * particle.speed * particle.direction.vY);
				
				//
				// Rotate proportional to its speed
				particle.rotation += particle.speed / 500;
				
				//
				// If the lifetime has expired, identify it for removal
				if (particle.alive > particle.lifetime) {
					removeMe.push(value);
				}
			}
		}

		//
		// Remove all of the expired particles
		for (particle = 0; particle < removeMe.length; particle++) {
			delete particles[removeMe[particle]];
		}
		removeMe.length = 0;
	};

	return that;
}());