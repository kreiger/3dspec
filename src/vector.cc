#include "vector.h"

Vector::Vector(int foo)
:size(foo)
{
	v = new Scalar[size];
	for (int bar=0;bar<size;bar++)
		v[bar]=0;
}

Vector::Vector(const Vector& foo)
:size(foo.size)
{
	v = new Scalar[size];
	for (int bar=0;bar<size;bar++)
		v[bar]=foo.v[bar];
}

Vector::~Vector()
{
	delete[] v;
}

Scalar& Vector::operator[] (int foo) const
{
	return v[foo];
}

const Vector Vector::operator+ (const Vector& foo) const
{
	Vector bar(size);
	for (int baz=0;baz<size;baz++)
		bar.v[baz]=v[baz]+foo.v[baz];
	return bar;
}

const Vector Vector::operator- (const Vector& foo) const
{
	Vector bar(size);
	for (int baz=0;baz<size;baz++)
		bar.v[baz]=v[baz]-foo.v[baz];
	return bar;
}

const Vector& Vector::operator+= (const Vector& foo)
{
	for (int baz=0;baz<size;baz++)
		v[baz]+=foo.v[baz];
	return *this;
}

const Vector& Vector::operator-= (const Vector& foo)
{
	for (int baz=0;baz<size;baz++)
		v[baz]-=foo.v[baz];
	return *this;
}


const Vector& Vector::operator= (const Vector& foo)
{
	for (int baz=0;baz<size;baz++)
		v[baz]=foo.v[baz];
	return *this;
}

const Vector& Vector::operator= (const Scalar *foo)
{
	for (int bar=0;bar<size;bar++)
		v[bar]=foo[bar];
	return *this;
}

const Vector& Vector::operator*= (Scalar foo)
{
	for (int bar=0;bar<size;bar++)
		v[bar]*=foo;
	return *this;
}

const Vector& Vector::operator*= (Matrix<Scalar> foo)
{
	Vector qoox(size);
	for (int bar=0;bar<size;bar++)
	{
		for (int baz=0;baz<size;baz++)
		{
			qoox.v[bar]+=v[baz]*foo.m[baz][bar];
		}
	}
	*this=qoox;
	return *this;
}

const Vector Vector::operator* (const Matrix<Scalar> foo) const
{
	Vector qoox(size);
	for (int bar=0;bar<size;bar++)
	{
		for (int baz=0;baz<size;baz++)
		{
			qoox.v[bar]+=v[baz]*foo.m[baz][bar];
		}
	}
	return qoox;
}

const Vector Vector::operator* (Scalar foo)
{
	Vector baz(size);
	for (int bar=0;bar<size;bar++)
		baz.v[bar]=v[bar]*foo;
	return baz;
}

const Vector Vector::operator& (const Vector& foo) const	//CrossProduct
{
	Vector Result(size);
	for (int bar=0;bar<size;bar++)
	{
		int baz=(bar+1)%size;
		int qoox=(baz+1)%size;
		Result.v[bar]=v[baz]*foo.v[qoox]-v[qoox]*foo.v[baz];
	}
	return Result;
}

const Scalar Vector::operator| (const Vector& foo) const	//DotDitto
{
	Scalar result = 0;
	for (int bar=0;bar<size;bar++)
		result+=(v[bar]*foo.v[bar]);
	return result;
}

const Vector Vector::operator- () const
{
	Vector Result(size);
	for (int foo=0;foo<size;foo++)
		Result.v[foo]= -(v[foo]);
	return Result;
}

void Vector::Set (Scalar x, Scalar y)
{
	v[0]=x;	v[1]=y;
}

void Vector::Set (Scalar x, Scalar y, Scalar z)
{
	v[0]=x;	v[1]=y;	v[2]=z;
}

Scalar Vector::Length ()
{
	Scalar l = (*this)|(*this);
	return sqrt(l);
}

Vector& Vector::Normalize ()
{
	Scalar l = ((*this)|(*this));
	l = sqrt(l);
	if (l!=0 && l!=1)
	{
		l=((Scalar)1)/((Scalar)l);
		for(int bar=0;bar<size;bar++)
			v[bar]*=l;
	}
	return *this;
}

void Vector::Clear ()
{
	for (int foo=0;foo<size;foo++)
		v[foo]=0;
}

/*
ostream& operator<< (ostream& os, const Vector& foo)
{
	for (int bar=0;bar<foo.size;bar++)
		os << foo[bar] << " ";

	return os;
}
*/

const Vector operator* (const Vector& qoox, Scalar foo)
{
	Vector baz(qoox.size);
	for (int bar=0;bar<qoox.size;bar++)
		baz.v[bar]=qoox.v[bar]*foo;
	return baz;
}
