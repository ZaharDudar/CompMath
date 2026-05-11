//
// Created by zahar on 03.05.2026.
//
#include <iostream>
#include "LinearSystemSolver.h"
#include <vector>



constexpr double SECINDAY = 60 * 60 * 24;

constexpr int    NX = 100;
constexpr double L  = 500;
constexpr double T  = 10 * SECINDAY;
constexpr double tau= 1.0/240.0 * SECINDAY;
constexpr double h  = L/NX;

constexpr double k      = 1e-14;
constexpr double mu     = 1e-3;
constexpr double phi    = 0.2;
constexpr double cf     = 1e-4 * 1e-5;
constexpr double rho0   = 1e3;
constexpr double p0     = 100 * 1e5; //Па
constexpr double p_inj  = 150 * 1e5; //Па
constexpr double p_prod = 50 * 1e5; //Па

std::vector<double> pMesh(NX);
// std::vector<double> rhoMesh(NX);


auto ci = [](const double rho_n_im)
{
    return k * rho_n_im / (mu * h * h);
};
auto bi = [](const double rho_n_ip)
{
    return k * rho_n_ip / (mu * h * h);
};
auto ai = [](const double ci, const double bi)
{
    return -ci - bi - phi * cf * rho0 / tau;
};
auto di = [](const double p_n_i)
{
    return - phi * cf * rho0 / tau * p_n_i;
};
auto rho_n_ip = [](const double p_n_i, const double p_n_ip)
{
    if (p_n_i >= p_n_ip)
    {
        return rho0 * (1 + cf*(p_n_i - 120 * 1e5));
    }
    return rho0 * (1 + cf*(p_n_ip - 120 * 1e5));
};
auto rho_n_im = [](const double p_n_i, const double p_n_im)
{
    if (p_n_im >= p_n_i)
    {
        return rho0 * (1 + cf*(p_n_im - 120 * 1e5));
    }
    return rho0 * (1 + cf*(p_n_i - 120 * 1e5));
};

void fillZeroLayer()
{
    for (int i=0; i<NX; i++)
    {
        pMesh[i] = p0;
        // rhoMesh[i] = rho0 * (1 + cf*(p0 - 120 * 1e5));
    }
    // pMesh[0] = p_inj;
    // pMesh[NX-1] = p_prod;
    //
    // for (int i=0; i<NX; i++)
    // {
    //     rhoMesh[i] = rho0 * (1 + cf*(p0 - 120 * 1e5));
    // }
}

std::vector<double> step()
{
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> B;


    c.push_back(0);
    b.push_back(1);
    for (int i=1; i<NX-1; i++)
    {
        auto ci_val = ci(rho_n_im(pMesh[i], pMesh[i-1]));
        auto bi_val = bi(rho_n_ip(pMesh[i], pMesh[i+1]));

        c.push_back(bi_val);
        b.push_back(ai(ci_val, bi_val));
        a.push_back(ci_val);
    }
    b.push_back(1);
    a.push_back(0);

    B.push_back(p_inj);
    for (int i=1; i<NX-1; i++)
    {
        B.push_back(di(pMesh[i]));
    }
    B.push_back(p_prod);
    auto newP = SolveThomasAglorithm(a, b, c, B);
    return newP;
}


int main()
{
    int maxSteps = static_cast<int>(T)/tau + 1;
    fillZeroLayer();
    std::ofstream p(OUTPUT_DIR"p.csv");
    std::ofstream t(OUTPUT_DIR"time.csv");
    // std::cout<< "Courant = "<<tau / h * k / mu<<std::endl;
    for (int time_step=0; time_step<maxSteps; time_step++)
    {
        t << time_step * tau / SECINDAY << std::endl;
        for (int i=0; i<NX; i++)
        {
            p << pMesh[i];
            if (i != NX-1) p<<",";
        }
        p << std::endl;
        pMesh = step();
    }
    p.close();
    t.close();
    return 0;
}