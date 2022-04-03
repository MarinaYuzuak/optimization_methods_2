#include "Tests.h"

void Tests::test()
{
	switch (test_number)
	{
	case 1:
		func = &Tests::testFunction;
		grad = &Tests::grad1;
		break;
	case 2:
		func = &Tests::quadraticFunction;
		grad = &Tests::grad2;
		break;
	case 3:
		func = &Tests::RosenbrocksFunction;
		grad = &Tests::grad3;
		break;
	default:
		std::cout << "There no test number.";
		std::exit(1);
		break;
	}
}

double Tests::testFunction(Vector y, Vector S, double lambda) // для функции в задании
{
	return 2. / (1 + pow((y.get(0) + lambda * S.get(0) - 1) / 2, 2) + pow((y.get(1) + lambda * S.get(1) - 2), 2))
		+ 1. / (1 + pow((y.get(0) + lambda * S.get(0) - 3) / 3, 2) + pow((y.get(1) + lambda * S.get(1) - 1) / 3, 2));
}

double Tests::quadraticFunction(Vector y, Vector S, double lambda)
{
	return 100 * pow(y.get(1) + lambda * S.get(1) - y.get(0) - lambda * S.get(0), 2)
		+ pow(1 - y.get(0) - lambda * S.get(0), 2);

}

double Tests::RosenbrocksFunction(Vector y, Vector S, double lambda)
{
	return  100 * pow(y.get(1) + lambda * S.get(1) - pow(y.get(0) + lambda * S.get(0), 2), 2)
		+ pow(1 - y.get(0) - lambda * S.get(0), 2);
}

Vector Tests::grad1(Vector point) // для функции в задании
{
	Vector res(point.getSize());
	double gradx = (-2 * (point.get(0) - 1) / 2) / pow(1 + pow((point.get(0) - 1) / 2, 2) + pow(point.get(1) - 2, 2), 2)
		+ ((-2. / 3) * (point.get(0) - 3) / 3) / (pow(1 + pow((point.get(0) - 3) / 3, 2) + pow((point.get(1) - 1) / 3, 2), 2));

	double grady = (-4 * (point.get(1) - 2)) / pow(1 + pow((point.get(0) - 1) / 2, 2) + pow(point.get(1) - 2, 2), 2)
		+ ((-2. / 3) * (point.get(1) - 1) / 3) / (pow(1 + pow((point.get(0) - 3) / 3, 2) + pow((point.get(1) - 1) / 3, 2), 2));
	res.set(0, gradx);
	res.set(1, grady);

	return res;
}

Vector Tests::grad2(Vector point)
{
	Vector res(point.getSize());
	double gradx = -200 * (point.get(1) - point.get(0)) - 2 * (1 - point.get(0));
	double grady = 200 * (point.get(1) - point.get(0));
	res.set(0, gradx);
	res.set(1, grady);

	return res;
}

Vector Tests::grad3(Vector point)
{
	Vector res(point.getSize());
	double gradx = -400 * point.get(0) * (point.get(1) - pow(point.get(0), 2) - 2 * (1 - point.get(0)));
	double grady = 200 * (point.get(1) - pow(point.get(0), 2));
	res.set(0, gradx);
	res.set(1, grady);

	return res;
}