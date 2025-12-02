//
// Created by zahar on 30.11.2025.
//
#include <iostream>
#include "RungeKutta.hpp"
#include <VectorMath.h>
#include <fstream>
#include <iomanip>

/*
 * y''-x*sqrt(y)=0
 * y(0) = 0,
 * y(1) = 2
 * Методом пристрелки
 *
 * (2):
 * y''-x*sqrt(y)=0
 * y(0) = 0,
 * y'(1) = alpha
 *
 * g(x,alpha) - решение (2)
 * g(1,alpha) - y(1)=t(alpha)=0
 * alpha_{n+1} = alpha_{n} - t(alpha_n) / t'(alpha_n),
 * где t'(alpha_n) = (t(alpha_n+epsilon) - t(alpha_n))/epsilon
 */
using std::numbers::e;

std::vector<double> f(const double x, const std::vector<double>& u)
{
    return std::vector<double>{u[1], x*sqrt(u[0])};
};

//Функция получает решение ДУ в точке x>x1
double g(const point& start, const point& end)
{
    auto solution = Methods::classicRK(f,start.y,start.x,end.x,0.0001);
    return solution.back().y[0];
}


double iter(const point& start, const point& end, const double epsilon)
{
    double tn = g(start, end)-end.y[0]; //g(pi,alpha) - y(pi)
    auto newStart = start;
    newStart.y[1] = newStart.y[1] + epsilon;
    double tne = g(newStart, end)-end.y[0];
    return start.y[1] - tn * epsilon/(tne-tn);
}

int main()
{

    double alpha = 1;
    point start{0, std::vector{0, alpha}}; //Первая краевая точка без значения производной
    point end{1, std::vector{2, 0.}}; //Краевая точка без значения производной
    for (int it=0; it<150; it++)
    {
        alpha = iter(start, end, 1e-5);
        start.y[1] = alpha;
    }
    std::cout<<std::setprecision(16)<<alpha<<std::endl;

    std::ofstream output(OUTPUT_DIR"XI93.csv");
    auto solution = Methods::classicRK(f,start.y,start.x,end.x,0.0005);
    output<<std::setprecision(16);
    std::cout<<std::setprecision(16);
    for (int i=0; i<solution.size(); i++)
    {
        output<<solution[i].x << "," << solution[i].y[0] << std::endl;

        for (const auto point : std::vector<double>{0.5,1,1.5,2,2.5})
        {
            if (std::abs(solution[i].x - point) < 1e-10)
            {
                std::cout<<solution[i].x<<" "<<solution[i].y[0]<<std::endl;
            }
        }

    }
    output.close();

}
// double g(const double x,const double alpha)
// {
//     auto solution = RK::classicRK<std::vector<double>>(f,std::vector<double>{0, alpha},0.,x,0.005);
//     return solution.back().y[0];
// }
//
// double iter(const double alpha, const double epsilon)
// {
//     double tn = g(1, alpha)-2; //g(1,alpha) - y(1) = g(...) - 2
//     double tne = g(1, alpha+epsilon)-2;
//     double tmp = tn * epsilon/(tne-tn);
//     return alpha - tn * epsilon/(tne-tn);
// }
//
// int main()
// {
//     double alpha = 1;
//     for (int it=0; it<100; it++)
//     {
//         alpha = iter(alpha, 1e-5);
//     }
//     std::cout<<alpha<<std::endl;
//
//     std::ofstream output(OUTPUT_DIR"XI93.csv");
//     auto solution = RK::classicRK<std::vector<double>>(f,std::vector<double>{0, alpha},0.,1,0.005);
//     output<<std::setprecision(16);
//     for (int i=0; i<solution.size(); i++)
//     {
//         output<<solution[i].x << "," << solution[i].y[0] << std::endl;
//     }
//     output.close();
//
// }