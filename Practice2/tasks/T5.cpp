//
// Created by zahar on 02.12.2025.
//
#include <iostream>
#include "RungeKutta.hpp"
#include <VectorMath.h>
#include <fstream>
#include <iomanip>

std::vector<double> f(const double t, const std::vector<double>& u)
{
    /*
     * x=u[0]
     * y=u[1]
     * u=u[2]
     * v=u[3]
     */
    constexpr double mu = 0.012277471;
    constexpr double eta = 1-mu;
    auto A = sqrt(pow(pow(u[0]+mu,2)+u[1]*u[1], 3));
    auto B = sqrt(pow(pow(u[0]-eta,2)+u[1]*u[1], 3));

    return std::vector<double>{
        u[2],
        u[3],
        u[0] + 2*u[3] - eta*(u[0]+mu)/A - mu*(u[0]-eta)/B,
        u[1] - 2*u[2] - eta*u[1]/A - mu*u[1]/B
    };
};


int main()
{
    std::vector<double> y0 = {0.994,0,0,-2.0015851063790825224053786224};
    const double T = 17.0652165601579625588917206249;
    auto solution = Methods::DormanPrince_4_5(f,y0,0,5*T,1e-4, 1e-10);
    std::cout<<std::setprecision(16)<<solution.back().y[0]<<std::endl;

    std::ofstream output(OUTPUT_DIR"T5.csv");
    output<<std::setprecision(16);
    for (int i=0; i<solution.size(); i+=1)
    {
        output<<solution[i].x << "," << solution[i].y[0] << std::endl;
    }
    output.close();

}