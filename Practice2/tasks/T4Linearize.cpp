//
// Created by zahar on 02.12.2025.
//

#include <iostream>
#include "RungeKutta.hpp"
#include <VectorMath.h>
#include <fstream>
#include <iomanip>

using std::numbers::e;

/*
 * y0=x*ln(x)
 * v'' = ex^2/2 * v - 1/2 ex^3 ln(x) v'
 */


std::vector<double> f(const double x, const std::vector<double>& u)
{
    return std::vector<double>{u[1],
        e*x*x/2.*u[0] - 0.5 * e*x*x*x*log(x)*u[1]
    };
};
double y0(const double x)
{
    return x*log(x);
}

//Функция получает решение ДУ в точке x>x1
template <typename T>
double g(const point<T>& start, const point<T>& end)
{
    auto solution = Methods::classicRK(f,start.y,start.x,end.x,0.0001);
    return solution.back().y[0];
}

int main()
{
    point startV{e, std::vector{0, 0.}}; //Первая краевая точка без значения производной
    point endV{e*e, std::vector{0, 0.}}; //Краевая точка без значения производной

    std::ofstream output(OUTPUT_DIR"T4Lin.csv");
    auto solution = Methods::classicRK(f,startV.y,startV.x,endV.x,0.0001);
    output<<std::setprecision(16);
    std::cout<<std::setprecision(16);
    for (int i=0; i<solution.size(); i++)
    {
        output<<solution[i].x << "," << solution[i].y[0] + y0(solution[i].x) << std::endl;

        for (const auto point : std::vector<double>{3,4,5,6,7})
        {
            if (std::abs(solution[i].x - point) < 5e-5)
            {
                std::cout<<solution[i].x<<" "<<solution[i].y[0]+ y0(solution[i].x)<<std::endl;
            }
        }

    }
    output.close();

}