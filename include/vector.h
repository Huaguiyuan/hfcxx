#ifndef _HFCXX_VECTOR_H
#define _HFCXX_VECTOR_H

#include<iostream>
#include<iomanip>
#include<vector>

class Vector3{
	public:
	double x,y,z;

	public:
	Vector3(); /* default constructor */
	Vector3(const double xx, const double yy, const double zz);
	Vector3(const Vector3 &rhs);
};

/* typedefs */
typedef std::vector<double> VecDoub;
typedef std::vector<int> VecInt;

#endif // _HFCXX_VECTOR_HH