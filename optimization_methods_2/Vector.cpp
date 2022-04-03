#define _USE_MATH_DEFINES

#include "Vector.h"
#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <iomanip>

Matrix Vector::vectorMult(Vector v)
{
	Matrix result(size, size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			result.set(i, j, V[i] * v.V[j]);
		}
	}
	return result;
}

double Vector::vectorNorm()
{
	double result = 0;
	for (size_t i = 0; i < size; i++)
	{
		result += V[i] * V[i];
	}
	return sqrt(result);
}

double Vector::angleBetweenVectors(Vector v) // в градусах
{	
	return acos( (*this * v) / (this->vectorNorm() * v.vectorNorm()) ) * (180 / M_PI);
}

void Vector::printScreenVector(size_t precision)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << std::setprecision(precision)  <<  V[i] << " ";
	}
	std::cout << std::endl;
}

void Vector::readScreenVector()
{
	for (size_t i = 0; i < size; i++)
	{
		std::cin >> V[i];
	}
	std::cout << std::endl;
}