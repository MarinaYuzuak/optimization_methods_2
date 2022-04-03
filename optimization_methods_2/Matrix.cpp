#include "Matrix.h"
#include <iostream>

Matrix Matrix::transpose()
{
    Matrix other(lines, columns);
    for (size_t i = 0; i < lines; i++) 
    {
        for (size_t j = 0; j < columns; j++) 
        {
            other.M[j][i] = M[i][j];
        }
    }
    return other;
}

Matrix Matrix::reverse_2_2()
{
    Matrix result(2, 2);
    double det_res = this->M[1][1] * this->M[0][0] - this->M[1][0] * this->M[0][1];

    if (det_res != 0)
    {
        det_res = 1. / det_res;

        result.M[0][0] = det_res * this->M[1][1];
        result.M[0][1] = -det_res * this->M[0][1];
        result.M[1][0] = -det_res * this->M[1][0];
        result.M[1][1] = det_res * this->M[0][0];
    }
    else
    {
        std::cout << "Det = 0" << std::endl;
        std::exit(1);
    }
    return result;
}

void Matrix::defineIdentityMatrix()
{
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (i == j)
                M[i][j] = 1;
            else
                M[i][j] = 0;
        }
    }
}

void Matrix::printScreenMatrix()
{
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::readScreenMatrix()
{
    for (size_t i = 0; i < lines; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            std::cin >> M[i][j];
        }
    }
    std::cout << std::endl;
}