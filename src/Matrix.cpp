#include <iostream>
#include <utility>
#include "Matrix.hpp"
using namespace std;


Matrix::Matrix(int row, int column) :row(row), column(column)
{
	//cout << "construct: " << ++constructCount << endl;
	pcount = new int(0);   //在堆上分配计数变量
	length = row * column;
	if (length == 0)
		m_data = NULL;
	else
	{
		m_data = new float* [row];

		if (m_data == NULL)
			cerr << "内存分配失败" << endl;

		for (int i = 0; i < row; i++)
		{
			this->m_data[i] = new float[column];

			if (m_data[i] == NULL)
				cerr << "内存分配失败" << endl;
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				m_data[i][j] = 1;
			}
		}
	}
}
Matrix::Matrix(const Matrix& Mat)
{
	//cout << "copy construct: " << ++copyConstructCount << endl;
	row = Mat.row;
	column = Mat.column;
	length = Mat.length;
	pcount = Mat.pcount;
	(*pcount)++;
	if (Mat.length == 0)
		m_data = NULL;
	else
		m_data = Mat.m_data;
	
}
Matrix::Matrix (Matrix&& Mat)noexcept
{
	//cout << "move construct" << endl;
	row = Mat.row;
	column = Mat.column;
	length = Mat.length;
	pcount = Mat.pcount;
	(*pcount)++;
	if (Mat.length == 0)
		m_data = NULL;
	else
		m_data = Mat.m_data;
}
//operator overload
float* Matrix:: operator[](int r)
{
	if (length == 0)
		cerr << "矩阵为空！" << endl;
	if (r >= this->row || r < 0)
		cerr << "下标越界！" << endl;
	return m_data[r]; 
}


//左值引用
Matrix& Matrix::operator=(const Matrix& Mat)
{
	//cout << "copy construct: " << ++copyConstructCount << endl;
	if (this == &Mat)
		return *this;
	erase();
	row = Mat.row;
	column = Mat.column;
	length = Mat.length;
	m_data = Mat.m_data;
	pcount = Mat.pcount;
	(*pcount)++;
	return *this;
}
Matrix Matrix::operator*(const Matrix& Mat)
{
	Matrix M(this->row,Mat.column);
	for (int m = 0; m < this->row; m++) 
	{
		for (int s = 0; s < Mat.column; s++) 
		{
			M[m][s] = 0;//初始化
			for (int n = 0; n < this->column; n++) 
				M.m_data[m][s] += this->m_data[m][n] * Mat.m_data[n][s];
		}
	}
	return M;
}
Matrix Matrix::operator*(int a)
{
	Matrix M;
	M.clone(*this);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			M.m_data[i][j] = a * m_data[i][j];
		}
	}
	return M;
}
Matrix operator*(int a, Matrix& Mat)
{
	return Mat*a;
}
//右值引用
Matrix& Matrix::operator=(Matrix&& Mat) noexcept
{
	//cout << "copy construct: " << ++copyConstructCount << endl;
	if (this == &Mat)
		return *this;
	erase();
	row = Mat.row;
	column = Mat.column;
	length = Mat.length;
	m_data = Mat.m_data;
	pcount = Mat.pcount;
	(*pcount)++;
	return *this;
}
Matrix operator*(int a, Matrix&& Mat) noexcept
{
	return Mat * a;
}

Matrix& Matrix::operator*(Matrix&& Mat) noexcept
{
	Matrix M(this->row, Mat.column);
	for (int m = 0; m < this->row; m++)
	{
		for (int s = 0; s < Mat.column; s++)
		{
			M[m][s] = 0;//初始化
			for (int n = 0; n < this->column; n++)
				M.m_data[m][s] += this->m_data[m][n] * Mat.m_data[n][s];
		}
	}
	return M;
}

Matrix& Matrix::clone(const Matrix& Mat)
{
	if (this == &Mat)
		return *this;
	erase();
	row = Mat.row;
	column = Mat.column;
	length = Mat.length;
	m_data = new float* [row];
	pcount = new int(0);
	if (m_data == NULL)
		cerr << "内存分配失败" << endl;

	for (int i = 0; i < row; i++)
	{
		this->m_data[i] = new float[column];

		if (m_data[i] == NULL)
			cerr << "内存分配失败" << endl;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			m_data[i][j] = Mat.m_data[i][j];
		}
	}
	return *this;
}

void Matrix::erase()
{
	if (*(this->pcount) > 0)
		(*(this->pcount))--;
	else
	{
		for (int i = 0; i < row; i++)
			delete[] m_data[i];
		delete pcount;
	}
		
}
Matrix::~Matrix()
{
	//cout << "destruct: " << ++destructCount << endl;
	erase();
}

ostream& operator<<(ostream& out, const Matrix& Mat)
{
	out << "[ ";
	for (int i = 0; i < Mat.row; i++)
	{
		for (int j = 0; j < Mat.column; j++)
		{
			out <<" "<< Mat.m_data[i][j];
		}
		if (i < Mat.row - 1)
			out << ";" << endl;
	}
	out << "  ]" << endl;
	return out;
}
