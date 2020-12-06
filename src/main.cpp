#include <iostream>
#include "Matrix.hpp"
using namespace std;

int constructCount = 0;
int copyConstructCount = 0;
int destructCount = 0;
int main()
{
	Matrix M1(5, 4);
	Matrix M2(4, 3),M3;
	Matrix M4= M1*M2;
	M1[2][3] = 3;
	M2[1][2] = 4;
	M3 = M1*M2;
	M4 = 2 * M1;
	cout << "Matrix 1:" << "\n" << M1 << endl;
	cout << "Matrix 2:" << "\n" << M2 << endl;
	cout << "Matrix 3:" << "\n" << M3 << endl;
	cout << "Matrix 4:" << "\n" << M4 << endl;



	//cout <<"\nconstructCount: "<< constructCount<< endl;
	//cout << "copyConstructCount: "<<copyConstructCount<< endl;
	//cout <<"destructCount: "<< destructCount << endl;
}
