//
// Created by zahar on 27.02.2026.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

constexpr double L = 20;
constexpr double T = 50;
constexpr double h = 0.5;
constexpr int N = L / h + 1;


/*
 * Нач:
 * u(x, 0) = sin(4pi x /L), x <= 5
 */

std::vector<double> step(const std::vector<double>& u0, double dt)
{
    std::vector<double> u1(N);
    for (int i = 1; i < N-1; ++i)
    {
        u1[i] = dt*dt/2 * (u0[i+1] - 2 * u0[i] + u0[i-1]) / (h*h) - dt/2 * (u0[i+1]-u0[i-1]) / h + u0[i];
    }
    u1[0] = dt*dt/2 * (u0[1] - 2 * u0[0] + u0[N-1]) / (h*h) - dt/2 * (u0[1]-u0[N-1]) / h + u0[0];
    u1[N-1] = dt*dt/2 * (u0[0] - 2 * u0[N-1] + u0[N-2]) / (h*h) - dt/2 * (u0[0]-u0[N-2]) / h + u0[N-1];
    return u1;
};

void cacl(double cft, const std::vector<double>& u0)
{
    auto u = u0;
    double dt = cft * h;
    std::ofstream f;
    f.open(OUTPUT_DIR"XIV.10.2b(" +std::to_string(cft)+ ").csv");
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
        u[i]=std::sin(4 * std::numbers::pi * (i * h)/L);
    }
    cacl(0.6, u);
    cacl(1, u);
    cacl(1.01, u);
    return 0;
}