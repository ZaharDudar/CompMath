//
// Created by zahar on 30.11.2025.
//

#ifndef PRACTICE2_RUNGEKUTTA_HPP
#define PRACTICE2_RUNGEKUTTA_HPP
#include <functional>
#include <VectorMath.h>

template<typename T>
struct point
{
    double x;
    T y;
};

namespace RK
{
    template<typename T>
    std::vector<point<T>> classicRK(const std::function<T(const double, const T&)> &f, const T& y0 ,const double a, const double b, const double h)
    {
        std::vector<point<T>> sol{static_cast<size_t>((b-a)/h + 1)};
        for(size_t i=0; i<sol.size(); i++)
        {
            sol[i].x = a + static_cast<double>(i) * h;
        }
        sol[0].y = y0;
        std::array<T, 4> k;
        for (size_t i=0; i<sol.size()-1; i++)
        {
            k[0] = f(sol[i].x, sol[i].y);
            k[1] = f(sol[i].x + h / 2., sol[i].y + h * k[0] * 0.5);
            k[2] = f(sol[i].x + h / 2., sol[i].y + h * k[1] * 0.5);
            k[3] = f(sol[i].x + h, sol[i].y + h * k[2]);

            sol[i + 1].y = sol[i].y + h / 6 * (k[0] + 2. * k[1] + 2. * k[2] + k[3]);
        }
        return sol;
    }
}
#endif //PRACTICE2_RUNGEKUTTA_HPP