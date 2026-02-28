//
// Created by zahar on 27.02.2026.
//
#include <iostream>
#include <vector>
#include <fstream>

constexpr double L = 20;
constexpr double T = 50;
constexpr double h = 0.5;
constexpr int N = L / h + 1;


/*
 * Нач:
 * u(x, 0) = 1, x <= 5
 * u(x, 0) = 0, 5<x<=20
 */

std::vector<double> step(const std::vector<double>& u0, double dt)
{
    std::vector<double> u1(N);
    for (int i = 1; i < N; ++i)
    {
        u1[i] = - (u0[i] - u0[i - 1]) / h * dt + u0[i];
    }
    u1[0] = u1[N-1];
    return u1;
};

void cacl(double cft, const std::vector<double>& u0)
{
    auto u = u0;
    double dt = cft * h;
    std::ofstream f;
    f.open(OUTPUT_DIR"XIV.10.2a(" +std::to_string(cft)+ ").csv");
    for (int i = 0; i < T/dt + 1; i++)
    {
        for (int j = 0; j < N; j++)
        {
            f << u[j];
            if (j < N - 1) f<<",";
        }
        u = step(u, dt);
        f << std::endl;
    }
    f.close();
}


int main()
{
    std::vector<double> u(N);

    for(int i = 0; i < N; i++)
    {
        if (i * h <= 5)
        {
            u[i]=1;
        }
    }
    cacl(0.6, u);
    cacl(1, u);
    cacl(1.01, u);
    return 0;
}