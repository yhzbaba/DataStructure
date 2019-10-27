#pragma once
#include <iostream>
#include "myException.h"
using namespace std;

template<class T>
class matrix
{
	friend ostream& operator<<(ostream&, const matrix<T>&);
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>&);
	~matrix() { delete[] element; }
	int rows()const { return theRows; }
	int columns()const { return theColumns; }
	T& operator()(int i, int j)const;
	matrix<T>& operator=(const matrix<T>&);
	//matrix<T> operator+()const;
	matrix<T> operator+(const matrix<T>&) const;
	matrix<T> operator-()const;
	matrix<T> operator-(const matrix<T>&) const;
	matrix<T> operator*(const matrix<T>&) const;
	matrix<T>& operator+=(const T&);
private:
	int theRows, theColumns;
	T* element;
};

//构造函数
template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
	if (theRows < 0 || theColumns < 0)
	{
		throw illegalParameterValue("Rows and columns must be >0.");
	}
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
	{
		throw illegalParameterValue("Either both or neither rows and columns should be zero.");
	}

	//创建矩阵
	this->theRows = theRows;
	this->theColumns = theColumns;
	element = new T[theRows * theColumns];
}

//复制构造函数
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
	theRows = m.theRows;
	theColumns = m.theColumns;
	element = new T[theRows * theColumns];

	copy(m.element, m.element + theRows * theColumns, element);
}

//@Override =
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	if (*this != m)
	{
		delete[] element;
		theRows = m.theRows;
		theColumns = m.theColumns;
		element = new T[theRows * theColumns];
		copy(m.element, m.element + theRows * theColumns, element);
	}
	return *this;
}

//@Override ()
template<class T>
T& matrix<T>::operator()(int i, int j) const
{
	if (i<1 || i>theRows || j<1 || j>theColumns)
	{
		throw matrixIndexOutOfBounds();
	}
	return element[(i - 1) * theColumns + j - 1];
}

//@Override +
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
	{
		throw matrixSizeMismatch();
	}
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
	{
		w.element[i] = element[i] + m.element[i];
	}
	return w;
}

//@Override -
template<class T>
matrix<T> matrix<T>::operator-() const
{
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
	{
		w.element[i] = -element[i];
	}
	return w;
}

//@Override -
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
	{
		throw matrixSizeMismatch();
	}
	matrix<T> w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		w.element[i] = element - m.element[i];

	return w;
}

//@Override *
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
	if (theColumns != m.theRows)
	{
		throw matrixSizeMismatch();
	}
	matrix<T> w(theRows, m.theColumns);

	int ct = 0, cm = 0, cw = 0;

	for (int i = 1; i <= theRows; i++)
	{
		for (int j = 1; j <= m.theColumns; j++)
		{
			T sum = element[ct] * m.element[cm];

			for (int k = 2; k <= theColumns; k++)
			{
				ct++;
				cm += m.theColumns;
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;
			//从行的起点和下一列重新开始
			ct -= theColumns - 1;
			cm = j;
		}
		//从下一行和第一列重新开始
		ct += theColumns;
		cm = 0;
	}
	return w;
}

//@Override +=
template<class T>
matrix<T>& matrix<T>::operator+=(const T& x)
{
	for (int i = 0; i < theRows * theColumns; i++)
	{
		element[i] += x;
	}
	return *this;
}

//@Override <<
template<class T>
ostream& operator<<(ostream& out, const matrix<T>& m)
{
	int k = 0;
	for (int i = 0; i < m.theRows; i++)
	{
		for (int j = 0; j < m.theColumns; j++)
		{
			out << m.element[k++] << " ";
		}
		out << endl;
	}

	return out;
}