//
// Created by zahar on 02.12.2025.
//
#include <iostream>
#include "RungeKutta.hpp"
#include <VectorMath.h>
#include <fstream>
#include <iomanip>



std::vector<double> f(const double x, const std::vector<double>& u)
{
    return std::vector<double>{u[1],
        2 - 6*x +2*x*x*x + (x*x-3)*exp(x)*sin(x)*(1+cos(x))+cos(x)*(exp(x)+(x*x-1)+x*x*x*x-3*x*x) \
        - (x*x-3)*(u[1] + cos(x)*u[0])
    };
};

double g(const double x,const double alpha)
{
    auto solution = RK::classicRK<std::vector<double>>(f,std::vector<double>{0, alpha},0.,x,0.0005);
    return solution.back().y[0];
}

double iter(const double alpha, const double epsilon)
{
    double tn = g(std::numbers::pi, alpha)-std::numbers::pi*std::numbers::pi; //g(pi,alpha) - y(pi)
    double tne = g(std::numbers::pi, alpha+epsilon)-std::numbers::pi*std::numbers::pi;
    return alpha - tn * epsilon/(tne-tn);
}

int main()
{
    double alpha = 1;
    for (int it=0; it<150; it++)
    {
        alpha = iter(alpha, 1e-10);
    }
    std::cout<<alpha<<std::endl;

    std::ofstream output(OUTPUT_DIR"T3.csv");
    auto solution = RK::classicRK<std::vector<double>>(f,std::vector<double>{0, alpha},0.,std::numbers::pi,0.0005);
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