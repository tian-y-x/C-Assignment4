#pragma once
#include <iostream>
using namespace std;

extern int constructCount ;
extern int copyConstructCount ;
extern int destructCount ;

class Matrix
{
private:
	int* pcount;
	int row, column, length;
	float** m_data;
public:
	
	 
	Matrix(int row = 0, int column = 0);  //constructor
	Matrix(const Matrix& Mat);            //copy constructor
	Matrix(Matrix&& Mat) noexcept;		  //move constructor
	~Matrix();

	Matrix& clone(const Matrix& Mat);
	Matrix& operator=(const Matrix& Mat);
	Matrix& operator=(Matrix&& Mat) noexcept;

	void erase();

	float* operator[](int row);
	Matrix operator*(int a);
	Matrix operator*(const Matrix& Mat);
	Matrix& operator*(Matrix&& Mat) noexcept;

	friend Matrix operator*(int a, Matrix& Mat);
	friend Matrix operator*(int a, Matrix&& Mat) noexcept;
	friend ostream& operator<<(ostream& out, const Matrix& Mat);
};