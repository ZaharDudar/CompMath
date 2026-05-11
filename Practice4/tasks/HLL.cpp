//
// Created by zahar on 08.03.2026.
//
#include <Eigen/Dense>
#include <fstream>
#include <iomanip>
#include <iostream>

using Vec3 = Eigen::Vector3d;
using Mat3 = Eigen::Matrix3d;


constexpr double gm = 5.0/3.0;

constexpr int    NX  =  300;
using U = std::array<Vec3, NX>; // Тип хранения параметров в-ва в ячейки и хранения потоков
using Flux = std::array<Vec3, NX-1>; // Тип хранения параметров в-ва в ячейки и хранения потоков
constexpr double L   =  10;
constexpr double dh  =  2 * L/(NX-1);
constexpr double CFT = 1;

constexpr double maxT = 0.02;
constexpr double writeInterval = 1e-4;

double maxV = 0;


Flux updateFlux(const U& u, const double time)
{
    Flux resF;
    //Расчёт ведём для правой стенки относительно i ячейки
    for (int i=0; i<NX-1; i++)
    {
        double rhoL = u[i][0];
        double uL = u[i][1]/rhoL;
        double eL = u[i][2];
        double pL = (gm-1)*(eL - 0.5 * rhoL * uL*uL);
        double aL = sqrt(gm * pL / rhoL);

        double rhoR = u[i+1][0];
        double uR = u[i+1][1]/rhoR;
        double eR = u[i+1][2];
        double pR = (gm-1)*(eR - 0.5 * rhoR * uR*uR);
        double aR = sqrt(gm * pR / rhoR);

        maxV = std::max(maxV, std::max(aL + abs(uL), aR + abs(uR)));

        double Sl = std::min(uL - aL, uR - aR);
        double Sr = std::max(uL + aL, uR + aR);

        Vec3 Fl = (u[i] + Vec3{0, 0, pL}) * uL + Vec3{0, pL, 0};
        Vec3 Fr = (u[i] + Vec3{0, 0, pR}) * uR + Vec3{0, pR, 0};

        if (0 <= Sl)
        {
            resF[i] = Fl;
        }
        if (Sl < 0 and 0 < Sr)
        {
            resF[i] = (Sr*Fl - Sl*Fr + Sr*Sl*(u[i+1] - u[i]))/(Sr-Sl);
        }
        if (0 >= Sr)
        {
            resF[i]=Fr;
        }

    }
    return resF;
};

U updateU(const U& u, const Flux& f, const double dt)
{
    U resU;
    for (int i=1; i<NX-1; i++)
    {
        resU[i] = u[i] - dt/dh * (f[i] - f[i-1]);
    }
    resU[0] = u[1];
    resU[NX-1] = u[NX-2];
    return resU;
}

int main()
{
    U u; // В модифицированных переменных {rho, rho u, E}
    Flux fu; // Поток {u rho, u rho u + (gm-1)*rho*e, u (E + p)}
    U u1;
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
        // std::cout<<std::scientific<<t<<'\t'<<dt<<"\n";
        dt = std::min(1e-7, CFT * dh / maxV);

        fu = updateFlux(u, t);
        u = updateU(u, fu, dt);


        t+=dt;
        if (t - lastTimeWrite >= writeInterval)
        {
            for (int i=0; i<NX; i++)
            {
                // u[i] = u1[i];
                double rho = u[i][0];
                double v   = u[i][1]/rho;
                double e   = u[i][2]/rho - 0.5 * v * v;
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
            std::cout<<std::scientific<<t<<'\t'<<dt<<"\n";
        }
    }
    rho_f.close();
    u_f.close();
    e_f.close();
    p_f.close();
    t_f.close();
}