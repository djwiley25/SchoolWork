
#include <iostream>
#include <iomanip>
#include <cmath>
#include "lunarLander.h"
//#include <cstdlib>

const float TOLERANCE=0.01;

using namespace std;



// print out information about the lander's status
void dashboard(Lander l){

	Vect p,v;
	double a;
	double f;

	// get the lander status
	p=l.getPosition();
	v=l.getVelocity();
	a=l.getAngle();
	f=l.getFuel();

	// print out the lander status
	cout << "x:" << setw(7) << left << fixed << setprecision(1) << p.x;
	cout << "y:" << setw(7) << left << fixed << setprecision(1) << p.y;
	cout << "vx:" << setw(7) << left << fixed << setprecision(1) << v.x;
	cout << "vy:" << setw(7) << left << fixed << setprecision(1) << v.y;
	cout << "angle:" << setw(7)<<left<<fixed << setprecision(1) << a*180.0/PI;
	cout << "fuel:" << setw(5)<<left<<fixed << setprecision(0) << f << "  ";
	cout<<setprecision(4);
	cout << "status:";
	if(l.getCrashed())cout<<" CRASHED";
	else if(l.getLanded())cout<<" landed";
	else if(l.getFuel()<=0.0)cout<<" no fuel";
	else if(l.getFuel()<=20.0)cout<<" bingo fuel";
	else cout<<" in flight";
	cout << endl;
}

bool closeTo(float a, float b){
	if(abs(b-a)<TOLERANCE)return true;
	return false;
}


int test01(){
	cout << "Test 01:  Dashboard Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=0.0; v.y=0.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);
	cout << "Please verify the following two lines match.  \n";
	cout << "x:100.0  y:300.0  vx:0.0    vy:0.0    angle:90.0   fuel:200    status: in flight\n";
	dashboard(l);

	cout<<"\n\n";
	return 1;
}


int test02(){
	cout << "Test 02:  GetAngle Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=0.0; v.y=0.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	cout << "expected value: "<<0.5*PI<<endl;
	cout << "  actual value: "<<l.getAngle()<<endl;
	if(closeTo(l.getAngle(),0.5*PI)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}
	cout<<"\n\n";
	return 0;
}

int test03(){
	cout << "Test 03:  GetVelocity Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	cout << "expected velocity.x value: "<<5.0<<endl;
	cout << "  actual velocity.x value: "<<l.getVelocity().x<<endl;
	cout << "expected velocity.y value: "<<10.0<<endl;
	cout << "  actual velocity.y value: "<<l.getVelocity().y<<endl;
	if(closeTo(l.getVelocity().x,5.0) && closeTo(l.getVelocity().y,10.0)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}


int test04(){
	cout << "Test 04:  GetFuel Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	cout << "expected fuel value: "<<200.0<<endl;
	cout << "  actual fuel value: "<<l.getFuel()<<endl;
	if(closeTo(l.getFuel(),200.0)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test05(){
	cout << "Test 05:  GetPosition Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	cout << "expected position.x value: "<<100.0<<endl;
	cout << "  actual position.x value: "<<l.getPosition().x<<endl;
	cout << "expected position.y value: "<<300.0<<endl;
	cout << "  actual position.y value: "<<l.getPosition().y<<endl;
	if(closeTo(l.getPosition().x,100.0) && closeTo(l.getPosition().y,300.0)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test06(){
	cout << "Test 06:  GetMTV Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	cout << "expected MTV value: "<<5.0<<endl;
	cout << "  actual MTV value: "<<l.getMTV()<<endl;
	if(closeTo(l.getMTV(),5.0)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test07(){
	cout << "Test 07:  GetCrashed Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	cout << "expected Crashed value: "<<false<<endl;
	cout << "  actual Crashed value: "<<l.getCrashed()<<endl;
	if(l.getCrashed()==false){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}


int test08(){
	cout << "Test 08:  GetLanded Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	cout << "expected Landed value: "<<false<<endl;
	cout << "  actual Landed value: "<<l.getLanded()<<endl;
	if(l.getLanded()==false){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}


int test09(){
	cout << "Test 09:  Simple RotateLeft Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expected=l.getAngle()+(0.05*PI);
	l.rotateLeft(0.05*PI);
	l.timeUpdate();
	double actual=l.getAngle();
	cout << "expected rotated value: "<<expected<<endl;
	cout << "  actual rotated value: "<<actual<<endl;
	if(closeTo(expected,actual)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test10(){
	cout << "Test 10:  Simple RotateRight Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expected=l.getAngle()-(0.05*PI);
	l.rotateRight(0.05*PI);
	l.timeUpdate();
	double actual=l.getAngle();
	cout << "expected rotated value: "<<expected<<endl;
	cout << "  actual rotated value: "<<actual<<endl;
	if(closeTo(expected,actual)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test11(){
	cout << "Test 11:  Over-rotate Left Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expected=l.getAngle()+(PI/12.0);
	l.rotateLeft(0.1*PI);
	l.timeUpdate();
	double actual=l.getAngle();
	cout << "expected rotated value: "<<expected<<endl;
	cout << "  actual rotated value: "<<actual<<endl;
	if(closeTo(expected,actual)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test12(){
	cout << "Test 12:  Over-rotate Right Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expected=l.getAngle()-(PI/12.0);
	l.rotateRight(0.1*PI);
	l.timeUpdate();
	double actual=l.getAngle();
	cout << "expected rotated value: "<<expected<<endl;
	cout << "  actual rotated value: "<<actual<<endl;
	if(closeTo(expected,actual)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test13(){
	cout << "Test 13:  Simple Burn Check - quadrant 1\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.33*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=10.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expectedFuel=l.getFuel()-20;
	Vect expectedVel=l.getVelocity();
	expectedVel.x+=cos(0.33*PI)*20;
	expectedVel.y+=sin(0.33*PI)*20;
	expectedVel.x+=G.x;
	expectedVel.y+=G.y;
	l.burn(20);
	l.timeUpdate();
	double actualFuel=l.getFuel();
	Vect actualVel=l.getVelocity();
	cout << "expected fuel value: "<<expectedFuel<<endl;
	cout << "  actual fuel value: "<<actualFuel<<endl;
	cout << "expected xvel value: "<<expectedVel.x<<endl;
	cout << "  actual xvel value: "<<actualVel.x<<endl;
	cout << "expected yvel value: "<<expectedVel.y<<endl;
	cout << "  actual yvel value: "<<actualVel.y<<endl;
	if(  closeTo(expectedFuel,actualFuel)
	   &&closeTo(expectedVel.x,actualVel.x)
	   &&closeTo(expectedVel.y,actualVel.y)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test14(){
	cout << "Test 14:  Simple Burn Check - quadrant 2\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.33*PI+PI/2.0,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=10.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expectedFuel=l.getFuel()-20;
	Vect expectedVel=l.getVelocity();
	expectedVel.x+=cos(0.33*PI+PI/2.0)*20;
	expectedVel.y+=sin(0.33*PI+PI/2.0)*20;
	expectedVel.x+=G.x;
	expectedVel.y+=G.y;
	l.burn(20);
	l.timeUpdate();
	double actualFuel=l.getFuel();
	Vect actualVel=l.getVelocity();
	cout << "expected fuel value: "<<expectedFuel<<endl;
	cout << "  actual fuel value: "<<actualFuel<<endl;
	cout << "expected xvel value: "<<expectedVel.x<<endl;
	cout << "  actual xvel value: "<<actualVel.x<<endl;
	cout << "expected yvel value: "<<expectedVel.y<<endl;
	cout << "  actual yvel value: "<<actualVel.y<<endl;
	if(  closeTo(expectedFuel,actualFuel)
	   &&closeTo(expectedVel.x,actualVel.x)
	   &&closeTo(expectedVel.y,actualVel.y)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test15(){
	cout << "Test 15:  Simple Burn Check - quadrant 3\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.33*PI+PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=10.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expectedFuel=l.getFuel()-20;
	Vect expectedVel=l.getVelocity();
	expectedVel.x+=cos(0.33*PI+PI)*20;
	expectedVel.y+=sin(0.33*PI+PI)*20;
	expectedVel.x+=G.x;
	expectedVel.y+=G.y;
	l.burn(20);
	l.timeUpdate();
	double actualFuel=l.getFuel();
	Vect actualVel=l.getVelocity();
	cout << "expected fuel value: "<<expectedFuel<<endl;
	cout << "  actual fuel value: "<<actualFuel<<endl;
	cout << "expected xvel value: "<<expectedVel.x<<endl;
	cout << "  actual xvel value: "<<actualVel.x<<endl;
	cout << "expected yvel value: "<<expectedVel.y<<endl;
	cout << "  actual yvel value: "<<actualVel.y<<endl;
	if(  closeTo(expectedFuel,actualFuel)
	   &&closeTo(expectedVel.x,actualVel.x)
	   &&closeTo(expectedVel.y,actualVel.y)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}
int test16(){
	cout << "Test 16:  Simple Burn Check - quadrant 4\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.33*PI+3.0*PI/2.0,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=10.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expectedFuel=l.getFuel()-20;
	Vect expectedVel=l.getVelocity();
	expectedVel.x+=cos(0.33*PI+3.0*PI/2.0)*20;
	expectedVel.y+=sin(0.33*PI+3.0*PI/2.0)*20;
	expectedVel.x+=G.x;
	expectedVel.y+=G.y;
	l.burn(20);
	l.timeUpdate();
	double actualFuel=l.getFuel();
	Vect actualVel=l.getVelocity();
	cout << "expected fuel value: "<<expectedFuel<<endl;
	cout << "  actual fuel value: "<<actualFuel<<endl;
	cout << "expected xvel value: "<<expectedVel.x<<endl;
	cout << "  actual xvel value: "<<actualVel.x<<endl;
	cout << "expected yvel value: "<<expectedVel.y<<endl;
	cout << "  actual yvel value: "<<actualVel.y<<endl;
	if(  closeTo(expectedFuel,actualFuel)
	   &&closeTo(expectedVel.x,actualVel.x)
	   &&closeTo(expectedVel.y,actualVel.y)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}


int test17(){
	cout << "Test 17:  RotateRight Through Zero Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.001*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expected=l.getAngle()-(0.05*PI)+2.0*PI;
	l.rotateRight(0.05*PI);
	l.timeUpdate();
	double actual=l.getAngle();
	cout << "expected rotated value: "<<expected<<endl;
	cout << "  actual rotated value: "<<actual<<endl;
	if(closeTo(expected,actual)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test18(){
	cout << "Test 18:  RotateLeft Through Zero Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=2*PI-0.001*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=5.0; v.y=10.0;
	p.x=100.0; p.y=300.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);

	double expected=l.getAngle()+(0.05*PI)-2.0*PI;
	l.rotateLeft(0.05*PI);
	l.timeUpdate();
	double actual=l.getAngle();
	cout << "expected rotated value: "<<expected<<endl;
	cout << "  actual rotated value: "<<actual<<endl;
	if(closeTo(expected,actual)){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}

	cout<<"\n\n";
	return 0;
}

int test19(){
	cout << "Test 19:  Soft Landing Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=0.0; v.y=0.0;
	p.x=10.0; p.y=1.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);
	l.timeUpdate();

	cout << "expected landed  value: "<<1<<endl;
	cout << "  actual landed  value: "<<l.getLanded()<<endl;
	cout << "expected crashed value: "<<0<<endl;
	cout << "  actual crashed value: "<<l.getCrashed()<<endl;
	if(l.getLanded()&&!l.getCrashed()){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}
	cout<<"\n\n";
	return 0;
}

int test20(){
	cout << "Test 20:  Crashed Landing Check\n";

	//set up the parameters for a lander
	Vect G,v,p;
	double a=0.5*PI,f=200.0,MTV=5.0;
	bool crashed=false, landed=false;
	G.x=0.0; G.y=-1.622;
	v.x=0.0; v.y=-4.0;
	p.x=10.0; p.y=1.0;
	
	//create an instance of the lander using the above parameters
	Lander l(G,a,v,f,p,MTV,crashed,landed);
	l.timeUpdate();

	cout << "expected landed  value: "<<0<<endl;
	cout << "  actual landed  value: "<<l.getLanded()<<endl;
	cout << "expected crashed value: "<<1<<endl;
	cout << "  actual crashed value: "<<l.getCrashed()<<endl;
	if(!l.getLanded()&&l.getCrashed()){
		cout<<"PASSED\n";
		return 1;
	}else{
		cout<<"FAILED\n";
		return 0;
	}
	cout<<"\n\n";
	return 0;
}

int main(){
	if(!test01())exit(1);
	if(!test02())exit(1);
	if(!test03())exit(1);
	if(!test04())exit(1);
	if(!test05())exit(1);
	if(!test06())exit(1);
	if(!test07())exit(1);
	if(!test08())exit(1);
	if(!test09())exit(1);
	if(!test10())exit(1);
	if(!test11())exit(1);
	if(!test12())exit(1);
	if(!test13())exit(1);
	if(!test14())exit(1);
	if(!test15())exit(1);
	if(!test16())exit(1);
	if(!test17())exit(1);
	if(!test18())exit(1);
	if(!test19())exit(1);
	if(!test20())exit(1);
	cout<<"\n\nAll tests passed.\n\n";

	return 0;
}

