#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include "matrix.h"

typedef float Scalar;

class Vector {
	public:
		Vector(int foo=3);
		~Vector();
		Vector(const Vector& foo);
		Scalar& operator[] (int foo) const;
		const Vector operator+ (const Vector& foo) const;
		const Vector operator- (const Vector& foo) const;
		const Vector& operator+= (const Vector& foo);
		const Vector& operator-= (const Vector& foo);
		const Vector& operator= (const Vector& foo);
		const Vector& operator= (const Scalar *foo);
		const Vector& operator*= (Scalar foo);
		const Vector& operator*= (const Matrix<Scalar> foo);
		const Vector operator* (const Matrix<Scalar> foo) const;
		const Vector operator* (Scalar foo);
		const Vector operator& (const Vector& foo) const; //CrossProduct
		const Scalar operator| (const Vector& foo) const;	//DotDitto
		const Vector operator- () const;
		//friend ostream& operator<< (ostream& os, const Vector& foo);
		friend const Vector operator* (const Vector& qoox, Scalar foo);

		void Set(Scalar x, Scalar y);
		void Set(Scalar x, Scalar y, Scalar z);
		Scalar Length();
		Vector& Normalize();
		void Clear();
	private:
		Scalar *v;
		int size;
};

#endif
