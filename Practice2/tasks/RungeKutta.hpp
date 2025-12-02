//
// Created by zahar on 30.11.2025.
//

#ifndef PRACTICE2_RUNGEKUTTA_HPP
#define PRACTICE2_RUNGEKUTTA_HPP
#include <functional>
#include <VectorMath.h>

struct point
{
    double x;
    std::vector<double> y;
};

namespace Methods
{
    std::vector<point> classicRK(const std::function<std::vector<double>(const double, const std::vector<double>&)> &f, const std::vector<double>& y0 ,const double a, const double b, const double h)
    {
        std::vector<point> sol{static_cast<size_t>((b-a)/h + 1)};
        for(size_t i=0; i<sol.size(); i++)
        {
            sol[i].x = a + static_cast<double>(i) * h;
        }
        sol[0].y = y0;
        std::array<std::vector<double>, 4> k;
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

    std::vector<point> DormanPrince_4_5(const std::function<std::vector<double>(const double, const std::vector<double>&)> &f, const std::vector<double>& y0 ,const double a, const double b, const double h0, const double epsilon)
    {
        std::array<std::array<double, 6>, 6> A = {1. / 5, 0, 0, 0, 0, 0,
                                                  3. / 40, 9. / 40, 0, 0, 0, 0,
                                                  44. / 45, -56. / 15, 32. / 9, 0, 0, 0,
                                                  19372. / 6561, -25360. / 2187, 64448. / 6561, -212. / 729, 0, 0,
                                                  9017. / 3168, -355. / 33, 46732. / 5247, 49. / 176, -5103. / 18656, 0,
                                                  35. / 384, 0, 500. / 1113, 125. / 192, -2187. / 6784, 11. / 84};
        std::array<double, 7> c =  {0, 1. / 5, 3. / 10, 4. / 5, 8. / 9, 1, 1};
        std::array<double, 7> b1 = {35. / 384, 0, 500. / 1113, 125. / 192, -2187. / 6784, 11. / 84, 0};
        std::array<double, 7> b2 = {5179. / 57600, 0, 7571. / 16695, 393. / 640, -92097. / 339200, 187. / 2100, 1. / 40};
        std::array<std::vector<double>, 7> k;

        std::vector<point> sol;
        sol.push_back({a,y0});
        double x = a;
        double h = h0;

        while (x < b)
        {
            k[0] = f(x, sol.back().y);
            std::vector<double> y1 = sol.back().y + h * b1[0] * k[0];
            std::vector<double> z1 = sol.back().y + h * b2[0] * k[0];
            for (size_t i=1; i<7; i++)
            {
                std::vector<double> lastY = sol.back().y;
                for (size_t j=0; j<i; j++)
                {
                    lastY = lastY + h * A[i-1][j] * k[j];
                }
                k[i] = f(x + h*c[i], lastY);
                y1 = y1 + h * b1[i] * k[i];
                z1 = z1 + h * b2[i] * k[i];
            }

            double error = sqrt(pow(h*(y1-z1)[0],2) + pow(h*(y1-z1)[1],2) + pow(h*(y1-z1)[2],2) + pow(h*(y1-z1)[3],2))/2;
            double h_opt = h * pow(epsilon * h / (2 * abs(y1-z1)), 0.2);
            std::cout << "h = " << h << std::endl;
            std::cout << "h opt = " << h_opt << std::endl;
            // std::cout << "abs = " << abs(y1-z1) << std::endl;
            if (x+h>b)
            {
                h=b-x;
            }
            else
            {
                h = std::min(h_opt, h0);
                // h = h_opt;
            }
            sol.push_back({x, y1});
            x += h;
        }
        return sol;
    }
}
#endif //PRACTICE2_RUNGEKUTTA_HPP