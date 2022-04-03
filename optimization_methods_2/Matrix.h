#pragma once

#include <vector>
#include "Vector.h"

class Matrix
{
public:
	Matrix(size_t n, size_t m)
	{
		lines = n;
		columns = m;
		M.resize(lines, std::vector<double>(columns));
	}

	double get(size_t i, size_t j) { return M[i][j]; }
	size_t getLines() { return lines; }
	size_t getColumns() { return columns; }
	void set(size_t i, size_t j, double value) { M[i][j] = value; }
	

	Matrix operator + (Matrix M2)
	{
		Matrix result(this->lines, this->columns);
		for (size_t i = 0; i < this->lines; i++)
		{
			for (size_t j = 0; j < this->columns; j++)
			{
				result.M[i][j] = this->M[i][j] + M2.M[i][j];
			}
		}
		return result;
	}

	Matrix operator - (Matrix M2)
	{
		Matrix result(this->lines, this->columns);
		for (size_t i = 0; i < this->lines; i++)
		{
			for (size_t j = 0; j < this->columns; j++)
			{
				result.M[i][j] = this->M[i][j] - M2.M[i][j];
			}
		}
		return result;
	}

	Matrix operator * (double number)
	{
		Matrix result(this->lines, this->columns);
		for (size_t i = 0; i < this->lines; i++)
		{
			for (size_t j = 0; j < this->columns; j++)
			{
				result.M[i][j] = number * this->M[i][j];
			}
		}
		return result;
	}

	Matrix operator / (double number)
	{
		Matrix result(this->lines, this->columns);
		for (size_t i = 0; i < this->lines; i++)
		{
			for (size_t j = 0; j < this->columns; j++)
			{
				result.M[i][j] = this->M[i][j] / number;
			}
		}
		return result;
	}

	Matrix operator * (Matrix M2)
	{
		Matrix result(this->lines, M2.columns);
		for (size_t i = 0; i < this->lines; i++) 
		{
			for (size_t j = 0; j < M2.columns; j++)
			{
				result.M[i][j] = 0;
				for (size_t k = 0; k < this->columns; k++)
				{
					result.M[i][j] += this->M[i][k] * M2.M[k][j];
				}
			}
		}
		return result;
	}

	Matrix transpose();
	Matrix reverse_2_2(); // Для обращения мтарицы 2 на 2.
	void defineIdentityMatrix(); // сгенерировать единичную матрицу
	void printScreenMatrix();
	void readScreenMatrix();

private:
	std::vector<std::vector<double>> M;
	size_t lines;
	size_t columns;
};