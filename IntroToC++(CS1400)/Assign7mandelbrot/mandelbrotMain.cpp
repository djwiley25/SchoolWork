#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

const int MAXITERS = 255;
const int ROWS = 4096;
const int COLS =4096;

struct Complex {
	double r;
	double i;
};
double interpolate(double x1, double y1, double x2, double y2, double xj) {
	float ydist, xdist, xjdist, yjdist, yj;

	ydist = y2 - y1;
	xdist = x2 - x1;
	xjdist = xj - x1;
	yjdist = ydist*(xjdist / xdist);
	yj = y1 + yjdist;

	return yj;
}

double magnitude(Complex c) {
	return sqrt(pow(c.r, 2) + pow(c.i, 2));
}

Complex operator+(Complex c1, Complex c2) {
	Complex c3;
	c3.r = c1.r + c2.r;
	c3.i = c1.i + c2.i;
	return c3;
}

Complex operator*(Complex c1, Complex c2) {
	Complex c3;
	c3.r = c1.r*c2.r - c1.i*c2.i;
	c3.i = c1.i*c2.r + c1.r*c2.i;
	return c3;
}

void print(Complex c) {
	cout << c.r << " + " << c.i << "i ";
}

int mandelbrot(Complex c) {
	Complex z;
	int i = 0;
	z = c;

	while (magnitude(z)<2 && i<MAXITERS) {
		z = z*z + c;
		++i;
	}

	return i;
}

int main(){
	ifstream fin;
	ofstream fout;
	Complex c1, c2, c3;

	fout.open("mandeloutput.ppm");
	fout << "P3" << endl;;
	fout << COLS << " " << ROWS << endl;
	fout << 255 <<endl;

	fin.open("mandelinput.txt");
	if(!fin.is_open()){
		cout << "Couldn't load input.txt file" << endl;
		return 0;
	}
	fin >> c1.r >> c1.i >> c2.r >> c2.i;
	fin.close();

	c3 = c1;
	for (int i = 0; i < ROWS; i++) {
		c3.i = interpolate(0, c1.i, ROWS, c2.i, i);
		for (int j = 0; j < COLS; j++) {
			c3.r = interpolate(0, c1.r, COLS, c2.r, j);
			int n = mandelbrot(c3);
			if (n == MAXITERS) {
				fout << 0 << " " << 0 << " " << 252 << " ";
			}
			else {
				int r, g, b;
				r = 0;
				g = (n % 16) * 64;
				b =n;
				fout << r << " " << g << " " << b << " ";
			}
		}
		
		fout << endl;
	}
	fout.close();
	cout << "Finished" << endl;
	return 0;
}