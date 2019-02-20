// cs1400 Fall 2015
// section: 00x
// assignment: 3
// name: David Wiley
// A#: A01099945

#include <iostream>
#include <math.h>

using namespace std;

//start of your code
float GetD(float v, float h) {
	float GetD = v*sqrt(2.0*h / 9.8);
	return GetD;
}

// one function "stub" to get you started
float GetT(float v, float d){
	float GetT = d / v;
	return GetT;
}

//end of your code
//make no changes below this line

int main(){
	float d,v,h,t;

	v=30; h=100;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;

	v=40; h=100;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;

	v=50; h=100;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;

	v=50; h=200;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;

	v=50; h=300;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;

	v=50; h=400;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;

	v=50; h=500;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;

	v=200; h=10000;
	d=GetD(v,h);
	t=GetT(v,d);
	cout<<"v = "<<v<<"     ";
	cout<<"h = "<<h<<"     ";
	cout<<"d = "<<d<<"     ";
	cout<<"t = "<<t<<endl;


	return 0;
}
