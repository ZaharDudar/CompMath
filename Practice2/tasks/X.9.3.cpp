//
// Created by zahar on 30.11.2025.
//
#include <iostream>
#include "RungeKutta.hpp"
#include <VectorMath.h>
#include <fstream>
#include <iomanip>

std::vector<double> f(const double x, const std::vector<double>& u)
{
    constexpr double mu = 1000;
    return std::vector<double>{u[1], mu*(1-u[1]*u[1])*u[1]-u[0]};
};


int main()
{
    auto solution = Methods::classicRK(f,std::vector<double>{0, 0.001},0.,1000,0.0005);
    std::cout<<std::setprecision(16)<<solution.back().y[0]<<std::endl;

    std::ofstream output(OUTPUT_DIR"X93.csv");
    output<<std::setprecision(16);
    for (int i=0; i<solution.size(); i+=10)
    {
        output<<solution[i].x << "," << solution[i].y[0] << std::endl;
    }
    output.close();

}