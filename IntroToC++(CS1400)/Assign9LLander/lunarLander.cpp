#include<iostream>
#include"lunarLander.h"
#include<math.h>

using namespace std;

Vect operator+(Vect a, Vect b) {
	Vect c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}
Vect operator*(Vect c1, Vect c2) {
	Vect c3;
	c3.x = c1.x*c2.x - c1.y*c2.y;
	c3.y = c1.y*c2.x + c1.x*c2.y;
	return c3;
}

Lander::Lander() {
	G.x = 0.0; G.y = -1.622;
	angle = PI/2, fuel = 100;
	maxTouchdownVelocity = 5;
	crashed = false, landed = false;
	position.x = 150; position.y = 300;
	velocity.x = 10; velocity.y = 0.0;
}
Lander::Lander(Vect iG, double iangle, Vect ivelocity, double ifuel,
	Vect iposition, double imax, bool icrashed, bool ilanded) {
	if (iangle > 0||iangle<2*PI) iangle = angle;
	else { cerr << "Initial angle values cannot be less than 0 or greater than 2 pi. \n"; exit(1); }
	if (ifuel > 0)ifuel = fuel;
	else { cerr << "Initial fuel values cannot be less than 0. \n"; exit(2); }
	if (iposition.y > 0)iposition.y = position.y;
	else { cerr << "Initial Y position values cannot be less than 0. \n"; exit(3); }
	if (imax > 0)imax = maxTouchdownVelocity;
	else { cerr << "Initial MTV values cannot be less than 0. \n"; exit(4); }
	if(icrashed==true&&ilanded==true) { cerr << "Values for crashed and landed cannot both be true. \n"; exit(5); }
	else { icrashed = crashed, ilanded = landed; }
}
double Lander:: getAngle() {
	return angle;
}
Vect Lander:: getVelocity() {
	return velocity;
}
double Lander::getFuel() {
	return fuel;
}
Vect Lander:: getPosition() {
	return position;
}
double Lander::getMTV() {
	return maxTouchdownVelocity;
}
bool Lander::getCrashed() {
	return crashed;
}
bool Lander::getLanded() {
	return landed;
}
void Lander::rotateLeft(double rotateAngle) {
	if (rotateAngle < 0)rotateAngle *= -1;
	rotatedThisTurn += rotateAngle;
	if (rotatedThisTurn > PI / 12)rotatedThisTurn = PI / 12;
}
void Lander::rotateRight(double rotateAngle) {
	if (rotateAngle < 0)rotateAngle *= -1;
	rotatedThisTurn -= rotateAngle;
	if (rotatedThisTurn > -PI / 12)rotatedThisTurn = -PI / 12;

}
void Lander::burn(double fuelAmount) {
	fuelBurnedThisTurn += fuelAmount;
	if (fuelBurnedThisTurn > 50)fuelBurnedThisTurn = 50;
}
void Lander::timeUpdate() {
	angle=angle* rotatedThisTurn;
	if (angle > 0.0*PI)angle -= 2 * PI;
	if (angle < 0.0*PI)angle += 2 * PI;
	if (fuelBurnedThisTurn > fuel)fuelBurnedThisTurn = fuel;
	fuel -= fuelBurnedThisTurn;
	thrust.x = cos(angle)*fuelBurnedThisTurn;
	thrust.y = sin(angle)*fuelBurnedThisTurn;
	velocity = velocity + thrust + G;
	position = position + velocity;
	fuelBurnedThisTurn = 0.0;
	rotatedThisTurn = 0.0;
	if (position.y < 0) {
		if (sqrt((velocity.x)*(velocity.x) + (velocity.y)*(velocity.y))>maxTouchdownVelocity) {
			crashed = true;
		}
		else {
			landed = true;
		}
		if (crashed || landed) {
			velocity.x = 0;
			velocity.y = 0;
			position.y = 0;
		}
	}
}