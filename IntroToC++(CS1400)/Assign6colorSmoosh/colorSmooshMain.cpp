#include <iostream>
#include <fstream>

using namespace std;

struct Color {
	int r;
	int g;
	int b;
};

void Smoosh(int rows, int cols, Color c1, Color c2, string filename) {
	//toDo:  write your function(s) here
	int i, j;
	ofstream fout;
	fout.open(filename+".ppm");
	fout << "P3\n";
	fout <<cols << " " << rows << endl;
	fout << "255\n";
	for (i = 0;i < rows;++i) {
		for (j = 0;j < cols;++j) {
			fout << ((c2.r*(j*255))+(c1.r*((cols-j)*255)))/(float)cols <<" ";
			fout << ((c2.g*(j * 255)) + (c1.g*((cols - j) * 255))) /(float) cols << " ";
			fout << ((c2.b*(j * 255)) + (c1.b*((cols - j) * 255))) / (float)cols << " ";

		}
		fout << endl;
	}
	fout.close();

	// end of your code
}
int main() {
	string bw = "blackToWhite";
	string ry = "redToYellow";
	string fb = "fooToBar";
	Color black; black.r = 0; black.g = 0; black.b = 0;
	Color white; white.r = 255; white.g = 255; white.b = 255;
	Color red; red.r = 255; red.g = 0; red.b = 0;
	Color yellow; yellow.r = 255; yellow.g = 255; yellow.b = 0;
	Color foo; foo.r = 21; foo.g = 156; foo.b = 221;
	Color bar; bar.r = 253; bar.g = 24; bar.b = 129;

	Smoosh(64, 256, black, white, bw);
	cout << "Black to white finished \n";
	Smoosh(400, 2000, red, yellow, ry);
	cout << "Red to yellow finished \n";
	Smoosh(234, 800, foo, bar, fb);
	cout << "foo to bar finished\n";

	return 0;

}