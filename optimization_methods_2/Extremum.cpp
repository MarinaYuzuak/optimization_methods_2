#include "Extremum.h"

#define _TEST_2

bool isGreater(double a, double b) {
    return a > b;
}

bool isLess(double a, double b) {
    return a < b;
}

Vector operator * (Matrix M, Vector v)
{
    Vector result(M.getLines());
    for (size_t i = 0; i < M.getLines(); i++)
    {
        result.set(i, 0);
        for (size_t j = 0; j < M.getColumns(); j++)
        {
            result.set(i, result.get(i) + M.get(i, j) * v.get(j));
        }
    }
    return result;
}

double goldenRatio(std::pair<double, double>& _interval, double eps, size_t& f_k, Vector& y, Vector& S, Tests& f, bool(*compare)(double, double)) // Ост. тоже через указатели?
{
    std::pair<double, double> interval = _interval;
    double lambda1 = interval.first + ((3 - sqrt(5)) / 2) * (interval.second - interval.first);
    double lambda2 = interval.first + ((sqrt(5) - 1) / 2) * (interval.second - interval.first);

    auto func = f.getFunc();

    double f1 = (f.*func)(y, S, lambda1);
    double f2 = (f.*func)(y, S, lambda2);
    f_k += 2;

    size_t iter = 1;

    while (fabs(interval.first - interval.second) > eps)
    {
        if (compare(f1, f2))
        {
            interval.second = lambda2;
            lambda2 = lambda1;
            lambda1 = interval.first + ((3 - sqrt(5)) / 2) * (interval.second - interval.first);
            f2 = f1;
            f1 = (f.*func)(y, S, lambda1);
            f_k++;
        }
        else if (compare(f2,f1))
        {
            interval.first = lambda1;
            lambda1 = lambda2;
            lambda2 = interval.first + ((sqrt(5) - 1) / 2) * (interval.second - interval.first);
            f1 = f2;
            f2 = (f.*func)(y, S, lambda2);
            f_k++;
        }
        else
        {
            interval.first = lambda1;
            interval.second = lambda2;
            lambda1 = interval.first + ((3 - sqrt(5)) / 2) * (interval.second - interval.first);
            lambda2 = interval.first + ((sqrt(5) - 1) / 2) * (interval.second - interval.first);
            f1 = (f.*func)(y, S, lambda1);
            f2 = (f.*func)(y, S, lambda2);
            f_k += 2;
        }
    }
    return  interval.second - ((interval.second - interval.first) / 2);

}

std::pair<double, double> interval(double delta, double x0, size_t& f_k, Vector& y, Vector& S, Tests& f, bool(*compare)(double, double))
{
    double lambda_cur, f1, f2, h;

    std::pair<double, double> interval(x0, 0);
    auto func = f.getFunc();

    if (compare((f.*func)(y, S, x0),(f.*func)(y, S, x0 + delta)))
    {
        lambda_cur = x0 + delta;
        h = delta;
    }
    else
    {
        lambda_cur = x0 - delta;
        h = -delta;
    }
    f_k += 2;

    while (true)
    {
        h *= 2;
        interval.second = lambda_cur + h;

        f1 = (f.*func)(y, S, lambda_cur);
        f2 = (f.*func)(y, S, interval.second);
        f_k += 2;

        if (compare(f1, f2))
        {
            interval.first = lambda_cur;
            lambda_cur = interval.second;
        }
        else 
        {
            if (interval.first > interval.second) {
                lambda_cur = interval.first;
                interval.first = interval.second;
                interval.second = lambda_cur;
            }
            return interval;
        }    
    }   
}

void Devidon_Fletcher_Powell_method(Vector x0, size_t precision)
{
    Vector d(2), gx(2), gy(2), p(2), v(2), s(2), x1(2);
    Matrix G(2, 2), G_reverse(2, 2);

    size_t k = 0, f_k = 1; // Количество итераций, количество вычислений функции f.
    double r = 0, f0, f1;
    double abs_x, abs_y, abs_f;
    double eps = 1. / pow(10, precision);

    std::pair<double, double> _interval; // a, b
    G.defineIdentityMatrix();

    Tests f("test.txt");
    auto grad = f.getGrad();
    auto func = f.getFunc();

    gx = (f.*grad)(x0);
    f0 = (f.*func)(x0, d, r);
    d = gx;

    std::ofstream fout1("tabel_dfp_1.txt");
    std::ofstream fout2("tabel_dfp_2.txt");
    fout1.precision(precision);
    fout1 << "prec (x0, y0) k f_k (x,y) f(x,y)" << std::endl;
    fout1 << eps << " (" << x0.get(0) << ", " << x0.get(1) << ") ";

    #ifdef _TEST_2        
    fout2.precision(precision);
    fout2 << "i,(xi;yi),f(xi;yi),(s1;s2),lambda,|xk+1-xk|,|yk+1-yk|,|fk+1-fk|,(xi;yi)^(s1;s2),H" << std::endl;
    #endif // _TEST_2

    do
    {
        k++;

        /* Для нахождения максимума в interval передавать isLess, в gR - isGreater.
        * Для нахождения минимума в interval передавать isGreater, в gR - isLess.*/

        _interval = interval(eps, x0.get(0) + d.get(0), f_k, x0, d, f, &isGreater);
        r = goldenRatio(_interval, eps, f_k, x0, d, f, &isLess);
        s = d * r;
        x1 = x0 + s;
        f1 = (f.*func)(x0, d, r); f_k++;
        gy = gx;

        gx = (f.*grad)(x1); p = gx - gy; v = G * p;
        G = G + s.vectorMult(s) / (s * p) - v.vectorMult(v) / (v * p);
        d = G * gx;

        abs_x = fabs(x1.get(0) - x0.get(0));
        abs_y = fabs(x1.get(1) - x0.get(1));
        abs_f = fabs(f1 - f0);

    #ifdef _TEST_2
        G_reverse = G.reverse_2_2();
        G_reverse.printScreenMatrix();
        std::cout << std::endl;
        fout2 << k << ",(" << x1.get(0) << ";" << x1.get(1) << ")," << f1
            << ",(" << d.get(0) << ";" << d.get(1) << ")," << r << ","
            << abs_x << "," << abs_y << "," << abs_f << ","
            << x1.angleBetweenVectors(d) << ",\n";
    #endif // _TEST_2

        x0 = x1;
        f0 = f1;
    } while ((abs_x > eps || abs_y > eps) && abs_f > eps);

    fout1 << k << " " << f_k << " (" << x1.get(0) << ", " << x1.get(1) << ") " << f1 << std::endl;
    fout1.close();
    fout2.close();
}