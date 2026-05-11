//
// Created by zahar on 08.03.2026.
//
#include "Eigen/Dense"
#include <fstream>
#include <iomanip>
#include <iostream>

using Vec3 = Eigen::Vector3d;
using Mat3 = Eigen::Matrix3d;


constexpr double gm = 5.0/3.0;


auto omegaT = [](const double u, const double e){
    double c = sqrt(gm*(gm-1)*e);
    return Mat3{{-u*c,  c,   gm - 1},
                    {-c*c,  0,   gm - 1},
                    {u*c,   -c,  gm - 1}};
};
auto omegaTinv = [](const double u, const double e){
    double c = sqrt(gm*(gm-1)*e);
    double cc = 2*c*c;
    return Mat3{{1/cc,              -2/cc,      1/cc},
                    {(u+c)/cc,          -2*u/cc,    (u-c)/cc},
                    {1/(2*(gm-1)),   0,          1/(2*(gm-1))}};
};

auto Lambda = [](const double u, const double e){
    double c = sqrt(gm*(gm-1)*e);
    return Mat3{{u+c,  0,  0},
                    {0,    u,  0},
                    {0,    0,  u-c}};
};
auto LambdaAbs = [](const double u, const double e){
    double c = sqrt(gm*(gm-1)*e);
    return Mat3{{abs(u+c),  0,  0},
                    {0,    abs(u),  0},
                    {0,    0,  abs(u-c)}};
};
auto A = [](const double u, const double e){return Mat3{{0,          1,     0},
                                                                   {-u*u,     2*u,   gm - 1},
                                                                   {-gm*u*e, gm*e, u}};};

/*
 * vl = 0, rho_l = 13  кг/м3, P_l = 10 атм
 * vr = 0, rho_r = 1.3 кг/м3, P_r = 1 атм
 */

/**
 *
 * @param wC Значение w в данном узле l
 * @param wP Значение w в предыдущем узле l-1
 * @param wN Значение w в следующем узле l+1
 * @return Значение w n+1 l
 */
Vec3 wNext(const Vec3& wC, const Vec3& wP, const Vec3& wN, const double dt, const double dh)
{
    const double rho = wC[0];
    const double u = wC[1]/rho;
    const double e = wC[2]/rho;
    return wC - dt * A(u,e) * (wN - wP) / (2*dh) + dt * (omegaTinv(u,e) * LambdaAbs(u,e) * omegaT(u,e)) * (wN - 2 * wC + wP) / (2*dh);
}

constexpr int    NX  =  300;
constexpr double L   =  10;
constexpr double dh  =  2 * L/(NX-1);
constexpr double CFT = 0.01;

constexpr double writeInterval = 1e-4;

constexpr double maxT = 0.02;
auto maxL = [](const std::array<Vec3, NX>& u)
{
    double l = 0;
    for (int i=0; i<NX; i++)
    {
        double uc = u[i][1]/u[i][0];
        double ec = u[i][2]/u[i][0];
        double c = sqrt(gm*(gm-1)*ec);
        l = std::max(l, std::max(std::max(abs(uc+c), abs(uc)), abs(uc-c)));
    }
    return l;
};

int main()
{
    std::array<Vec3, NX> u; // В модифицированных переменных {rho, rho u, rho e}
    std::array<Vec3, NX> u1;
    double t=0;
    double lastTimeWrite=0;
    double dt=1;
    for (int i=0; i<NX/2; i++)
    {
        u[i] = Vec3{13, 0, 10 * 1e5 / (gm-1)};
    }
    for (int i=NX/2; i<NX; i++)
    {
        u[i] = Vec3{1.3, 0, 1 * 1e5 / (gm-1)};
    }
    std::ofstream rho_f;
    std::ofstream u_f;
    std::ofstream e_f;
    std::ofstream p_f;
    std::ofstream t_f;
    rho_f.open(OUTPUT_DIR"RIMAN_1_rho.csv");
    u_f.open(OUTPUT_DIR"RIMAN_1_u.csv");
    e_f.open(OUTPUT_DIR"RIMAN_1_e.csv");
    p_f.open(OUTPUT_DIR"RIMAN_1_p.csv");
    t_f.open(OUTPUT_DIR"RIMAN_1_t.csv");
    while (t<maxT)
    {
        dt = std::min(1e-7, CFT * dh / maxL(u));
        for (int i=1; i<NX-1; i++)
        {
            u1[i] = wNext(u[i], u[i-1],u[i+1], dt, dh);
        }
        u1[0] = u1[1];
        u1[NX-1] = u1[NX-2];

        u = u1;
        t+=dt;
        if (t - lastTimeWrite >= writeInterval)
        {
            for (int i=0; i<NX; i++)
            {
                double rho = u[i][0];
                double v   = u[i][1]/rho;
                double e   = u[i][2]/rho;
                double p   = (gm-1)*rho*e;
                rho_f << rho;
                u_f << v ;
                e_f << e ;
                p_f << p ;
                if (i < NX-1) {
                    rho_f << ",";
                    u_f <<   ",";
                    e_f <<   ",";
                    p_f <<   ",";
                };

            }
            t_f << t <<"\n";
            rho_f << "\n";
            u_f << "\n";
            e_f << "\n";
            p_f << "\n";
            lastTimeWrite = t;
            std::cout<<std::scientific<<t<<"\t"<<dt<<"\n";
        }
    }
    rho_f.close();
    u_f.close();
    e_f.close();
    p_f.close();
    t_f.close();
}