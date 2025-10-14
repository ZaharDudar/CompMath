//
// Created by zahar on 12.10.2025.
//


#include <cstddef>
#include <cstdio>
#include <math.h>
/**
 *  Вычисляет интеграл прямоугольниками
 */
double integrateRect(double(&f)(double), double x0, double x1, double step)
{
    std::size_t N = (x1 - x0) / step;
    double result = 0.0;
    for (int i = 1; i <= N; i++)
    {
        result += f(x0 + step * i) * step;
    }
    return result;
}
/**
 *  Вычисляет интеграл трапециями
 */
double integrateTrapezoid(double(&f)(double), double x0, double x1, double step)
{
    std::size_t N = (x1 - x0) / step;
    double result = 0.0;
    for (int i = 1; i < N; i++)
    {
        result += step * (f(x0+step*i) + f(x0+step*(i+1))) / 2;
    }
    return result;
}
/**
 *  Вычисляет интеграл трапециями
 */
double integrateSympson(double(*f)(double), double x0, double x1, double step)
{
    std::size_t N = (x1 - x0) / step;
    double result = 0.0;
    for (int i = 1; i < N; i++)
    {
        result += step * (f(x0+step*i) + 4 * f((x0+step*i + x0+step*(i+1)) / 2) + f(x0+step*(i+1))) / 6;
    }
    return result;
}

double f(double x)
{
    return std::sin(100*x) * std::exp(-(x*x)) * std::cos(2*x);
}

int main()
{
    double x0 = 0;
    double x1 = 3;
    double step = 1e-6;
    printf("Rectangles: \t %0.12f\n", integrateRect(f, x0, x1, step));
    printf("Sympson:    \t %0.12f\n", integrateSympson(f, x0, x1, step));
    printf("Trapezoid:  \t %0.12f\n", integrateTrapezoid(f, x0, x1, step));

}

