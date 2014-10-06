#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>

template<class T>
class Matrix
{
	public:
		Matrix(int _rows, int _cols);
		Matrix(const Matrix&);
		~Matrix();
		void Clear();
		void Unit();
		const Matrix& operator+= (const Matrix& x);
		const Matrix& operator-= (const Matrix& x);
		const Matrix& operator*= (int x);
		const Matrix operator* (const Matrix& x) const;
		const Matrix operator+ (const Matrix& x) const;
		const Matrix operator- (const Matrix& x) const;
		const Matrix& operator= (const Matrix& x);
		const Matrix& operator= (const T *x);
		const Matrix Transpose ();
		T *operator[] (int x);
		T& operator() (int r, int c) const;
		void Print();
		friend class Vector;

		const int rows;
		const int cols;
	private:
		T **m;
};

template<class T>
Matrix<T>::Matrix(int _rows, int _cols):
rows(_rows), cols(_cols)
{
        m = new (T*)[rows];
        for (int foo=0;foo<rows;foo++)
        m[foo]=new T[cols];
}

template<class T>
Matrix<T>::Matrix(const Matrix& x):
rows(x.rows), cols(x.cols)
{
	m = new (T*)[rows];
	for (int foo=0;foo<rows;foo++)
	{
		m[foo]=new T[cols];
		for (int bar=0;bar<cols;bar++)
			m[foo][bar]=x.m[foo][bar];
	}
}

template<class T>
Matrix<T>::~Matrix()
{
	for (int foo=0;foo<rows;foo++)
		delete[] m[foo];
	delete[] m;
}

template<class T>
T *Matrix<T>::operator[] (int x)
{
        return m[x];
}

template<class T>
T& Matrix<T>::operator() (int r, int c) const
{
	assert ((r>=0) && (r<rows) && (c>=0) && (c<cols));
	return m[r][c];
}

template<class T>
void Matrix<T>::Clear()
{
	for (int foo=0;foo<rows;foo++)
	{
		for (int bar=0;bar<cols;bar++)
		{
			m[foo][bar]=0;
		}
	}
}

template<class T>
void Matrix<T>::Unit()
{
	assert(rows==cols);
	for (int foo=0;foo<rows;foo++)
	{
		for (int bar=0;bar<cols;bar++)
		{
			if (foo==bar)
				m[foo][bar]=1;
			else
				m[foo][bar]=0;
		}
	}
}

template<class T>
const Matrix<T>& Matrix<T>::operator*= (int x)
{
	for (int foo=0;foo<rows;foo++)
		for (int bar=0;bar<cols;bar++)
			m[foo][bar]*=x;
	return *this;
}

template<class T>
const Matrix<T> Matrix<T>::operator* (const Matrix& x) const
{
	assert(cols==x.rows);

	Matrix R(rows,x.cols);
	for (int foo=0;foo<rows;foo++)
	{
		for (int bar=0;bar<x.cols;bar++)
		{
			R.m[foo][bar]=0;
			for (int baz=0;baz<cols;baz++)
				R.m[foo][bar]+=m[foo][baz]*x.m[baz][bar];
		}
	}
	return R;
}

template<class T>
const Matrix<T>& Matrix<T>::operator+= (const Matrix& x)
{
	assert (rows==x.rows && cols==x.cols);

	for (int foo=0;foo<rows;foo++)
		for (int bar=0;bar<cols;bar++)
			m[foo][bar]+=x.m[foo][bar];
	return *this;
}

template<class T>
const Matrix<T>& Matrix<T>::operator-= (const Matrix& x)
{
	assert (rows==x.rows && cols==x.cols);

	for (int foo=0;foo<rows;foo++)
		for (int bar=0;bar<cols;bar++)
			m[foo][bar]-=x.m[foo][bar];
	return *this;
}

template<class T>
const Matrix<T> Matrix<T>::operator+ (const Matrix& x) const
{
	assert (rows==x.rows && cols==x.cols);

	Matrix temp(*this);

	for (int foo=0;foo<rows;foo++)
		for (int bar=0;bar<cols;bar++)
			temp.m[foo][bar]=m[foo][bar]+x.m[foo][bar];
	return temp;
}

template<class T>
const Matrix<T> Matrix<T>::operator- (const Matrix& x) const
{
	assert (rows==x.rows && cols==x.cols);

	Matrix<T> temp(*this);
	for (int foo=0;foo<rows;foo++)
		for (int bar=0;bar<cols;bar++)
			temp.m[foo][bar]=m[foo][bar]-x.m[foo][bar];
	return temp;
}

template<class T>
const Matrix<T>& Matrix<T>::operator= (const Matrix<T>& x)
{
	assert (rows==x.rows && cols==x.cols);

	for (int foo=0;foo<rows;foo++)
		for (int bar=0;bar<cols;bar++)
			m[foo][bar]=x.m[foo][bar];
	return *this;
}

template<class T>
const Matrix<T>& Matrix<T>::operator= (const T *x)
{
	for (int foo=0;foo<rows;foo++)
		for (int bar=0;bar<cols;bar++)
			m[foo][bar]=x[foo*cols+bar];
	return *this;
}

template<class T>
void Matrix<T>::Print()
{
	for (int foo=0;foo<rows;foo++)
	{
		cout << "[";
		for (int bar=0;bar<cols;bar++)
		{
			cout << setw(3) << m[foo][bar] << " ";
		}
		cout << "]" << endl;
	}
}

template<class T>
const Matrix<T> Matrix<T>::Transpose()
{
	Matrix foo(cols,rows);

	for (int bar=0;bar<rows;bar++)
		for (int baz=0;baz<cols;baz++)
			foo.m[baz][bar]=m[bar][baz];
	return foo;
}

#endif
