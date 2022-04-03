#pragma once
#include "Tests.h"
#include <cmath>

bool isGreater(double a, double b);
bool isLess(double a, double b);
double goldenRatio(std::pair<double, double>& _interval, double eps, size_t& f_k, Vector& y, Vector& S, Tests& f, bool(*compare)(double, double));
std::pair<double, double> interval(double delta, double x0, size_t& f_k, Vector& y, Vector& S, Tests& f, bool(*compare)(double, double));
void Devidon_Fletcher_Powell_method(Vector x, size_t precision);