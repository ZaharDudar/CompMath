//
// Created by zahar on 12.10.2025.
//
#include <math.h>
#include "LinearSystemSolver.h"

/**
 * Система
 * x^2 + y^2 = 1
 * y = tgx
 *
 * J = ( 2x          2y )
 *     ( 1/cos^2(x)  -1 )
 * adj J = ( -1           -2y )
 *       ( -1/cos^2(x)   2x )
 *
 * J^-1 = 1/det J * adj J
 * det J = -2x + 2y/cos^2(x)
 */

double detJ(const double x, const double y)
{
    return -2*x - 2*y/(std::cos(x)*std::cos(x));
}

Matrix<double> reverseJ(const std::vector<double>& u)
{
    double x = u[0];
    double y = u[1];
    Matrix<double> adjJ(2,2);
    double rDetJ = (1 / detJ(x, y));
    adjJ(0,0,-1 * rDetJ);
    adjJ(0,1,-2*y*rDetJ);
    adjJ(1,0,-1/(std::cos(x)*std::cos(x)) * rDetJ);
    adjJ(1,1,2*x*rDetJ);
    return  adjJ;
}

int main()
{
    std::cout <<"Method Newton"<< std::endl;
    auto f = [&](const std::vector<double>& u)
    {
        double x = u[0];
        double y = u[1];
        return std::vector<double>{x*x+y*y-1, std::tan(x)-y};
    };
    std::vector<double> u0{1,1};
    for (int i=0; i< 10; i++)
    {
        u0 = u0 - reverseJ(u0) * f(u0);
    }
    std::cout << u0 << std::endl;

    std::cout <<"Method relaxation"<< std::endl;
    u0 = std::vector<double>{1,1};
    for (int i=0; i< 1000; i++)
    {
        u0 = u0 + 0.001 * f(u0);
    }
    std::cout << u0 << std::endl;

    std::cout <<"MPI"<< std::endl;
    u0 = std::vector<double>{1,1};
    for (int i=0; i< 1000; i++)
    {
        double newX = std::sqrt(1 - u0[1]*u0[1]);
        double newY = std::atan(u0[0]);
        auto newU = std::vector<double>{newX, newY};
        if (abs(newU-u0) < std::numeric_limits<double>::epsilon())
        {
            // std::cout<<i<<"\n";
            break;
        }
        u0 = newU;

    }
    auto firstRoot = u0;
    u0 = std::vector<double>{-1,-1};
    for (int i=0; i< 1000; i++)
    {
        double newX = -std::sqrt(1 - u0[1]*u0[1]);
        double newY = std::atan(u0[0]);
        auto newU = std::vector<double>{newX, newY};
        if (abs(newU-u0) < std::numeric_limits<double>::epsilon())
        {
            // std::cout<<i<<"\n";
            break;
        }
        u0 = newU;
    }
    auto secondRoot = u0;

    printf("First root: (x1, y1) = (%.6f, %.6f)\n", firstRoot[0], firstRoot[1]);
    printf("Second root: (x2, y2) = (%.6f, %.6f)\n", secondRoot[0], secondRoot[1]);

}