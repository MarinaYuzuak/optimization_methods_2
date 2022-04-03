#include "Matrix.h"

#include <string>
#include <fstream>
#include <iostream>

class Tests
{
public:
	Tests(std::string file_name)
	{
		std::ifstream fin(file_name);
		if (fin.is_open())
			fin >> test_number;
		else
		{
			std::cout << "File with test number was not open.";
			std::exit(1);
		}
		fin.close();
		test();
	}

	void setTestNumber(size_t _test_number) { test_number = _test_number; }
	auto getFunc() { return func; }
	auto getGrad() { return grad; }

private:
	size_t test_number;
	double(Tests::*func)(Vector a, Vector b, double c);
	Vector(Tests::*grad)(Vector p);

private:
	void test();
	double testFunction(Vector y, Vector S, double lambda);
	double quadraticFunction(Vector y, Vector S, double lambda);
	double RosenbrocksFunction(Vector y, Vector S, double lambda);
	Vector grad1(Vector point);
	Vector grad2(Vector point);
	Vector grad3(Vector point);
};