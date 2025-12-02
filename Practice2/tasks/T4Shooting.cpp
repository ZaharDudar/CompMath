//
// Created by zahar on 02.12.2025.
//
#include <iostream>
#include "RungeKutta.hpp"
#include <VectorMath.h>
#include <fstream>
#include <iomanip>

using std::numbers::e;

std::vector<double> f(const double x, const std::vector<double>& u)
{
    return std::vector<double>{u[1],
        sqrt(1/x*x + std::numbers::e/log(x) * u[0]*u[0] - exp(u[1])*u[0])
    };
};
//Функция получает решение ДУ в точке x>x1
double g(const point& start, const point& end)
{
    auto solution = Methods::classicRK(f,start.y,start.x,end.x,0.0001);
    return solution.back().y[0];
}

double iter(const point& start, const point& end,const double epsilon)
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
    point start{e, std::vector{e, alpha}}; //Первая краевая точка без значения производной
    point end{e*e, std::vector{2*e*e, 0.}}; //Краевая точка без значения производной
    for (int it=0; it<150; it++)
    {
        alpha = iter(start, end, 1e-5);
        start.y[1] = alpha;
    }
    std::cout<<alpha<<std::endl;

    std::ofstream output(OUTPUT_DIR"T4Shooting.csv");
    auto solution = Methods::classicRK(f,start.y,start.x,end.x,0.0001);
    output<<std::setprecision(16);
    std::cout<<std::setprecision(16);
    for (int i=0; i<solution.size(); i++)
    {
        output<<solution[i].x << "," << solution[i].y[0] << std::endl;

        for (const auto point : std::vector<double>{3,4,5,6,7})
        {
            if (std::abs(solution[i].x - point) < 5e-5)
            {
                std::cout<<solution[i].x<<" "<<solution[i].y[0]<<std::endl;
            }
        }

    }
    output.close();

}