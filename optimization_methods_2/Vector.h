#pragma once
#include <vector>

class Vector
{
	friend class Matrix;
public:
	Vector(size_t n)
	{
		size = n;
		V.resize(size);
	}

	double get(size_t i) { return V[i]; }
	void   set(size_t place, double value) { V[place] = value; }
	size_t getSize() { return size; }

	Vector operator + (Vector v)
	{
		Vector result(this->size);
		for (size_t i = 0; i < this->size; i++)
		{
			result.V[i] = this->V[i] + v.V[i];
		}
		return result;
	}

	Vector operator - (Vector v)
	{
		Vector result(this->size);
		for (size_t i = 0; i < this->size; i++)
		{
			result.V[i] = this->V[i] - v.V[i];
		}
		return result;
	}

	Vector operator * (double number)
	{
		Vector result(this->size);
		for (size_t i = 0; i < this->size; i++)
		{
			result.V[i] = number * this->V[i];
		}
		return result;
	}

	Vector operator / (double number)
	{
		Vector result(this->size);
		for (size_t i = 0; i < this->size; i++)
		{
			result.V[i] = this->V[i] / number;
		}
		return result;
	}

	double operator * (Vector v)
	{
		double result = 0;
		for (size_t i = 0; i < this->size; i++)
		{
			result += this->V[i] * v.V[i];
		}
		return result;
	}

	Matrix vectorMult(Vector v);
	double vectorNorm();
	double angleBetweenVectors(Vector v);
	void   printScreenVector(size_t precision);
	void   readScreenVector();

private:
	size_t size;
	std::vector<double> V;
};
