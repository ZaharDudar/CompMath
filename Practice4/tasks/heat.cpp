//
// Created by zahar on 05.05.2026.
//
#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <cmath>

#include "LinearSystemSolver.h"


// constexpr int N = 50; //NX = NY
constexpr double LAMBDA = 1e-4;
using Mesh = std::vector<std::vector<double>>;

double norm(const Mesh& mesh)
{
    double res = 0;
    for (int i = 0; i < mesh.size(); ++i)
    {
        for (int j = 0; j < mesh[i].size(); ++j)
        {
            res += pow(mesh[i][j], 2);
        }
    }
    return sqrt(res)/(mesh.size()*mesh.size());
}
double norm(const Mesh& meshA, const Mesh& meshB)
{
    double res = 0;
    for (int i = 0; i < meshA.size(); i++)
    {
        for (int j = 0; j < meshA[i].size(); j++)
        {
            res += pow(meshA[i][j] - meshB[i][j], 2);
        }
    }
    auto N = static_cast<double>(meshA.size());
    return sqrt(res / (N*N));
}
template<typename T>
T sub(const T& a, const T& b)
{
    T res = a;
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < a[i].size(); ++j)
        {
            res[i][j] -= b[i][j];
        }
    }
    return res;
}

Mesh step(const Mesh &m, const double dt, const double dh, const double t)
{
    const size_t N = m.size();
    Mesh result;
    result.resize(N);
    for (int i=0; i<N; i++)
    {
        result[i].resize(N);
    }
    std::vector<double> leftCol(N);
    std::vector<double> a(N);
    std::vector<double> b(N);
    std::vector<double> c(N);
    std::fill_n(a.begin(), N-1, 25 * LAMBDA / (dh*dh));
    std::fill_n(b.begin(), N, - 2 * 25 * LAMBDA/(dh*dh) - 2 * LAMBDA/(dh*dh) - 1 / dt);
    std::fill_n(c.begin(), N-1, 25 * LAMBDA/(dh*dh));
    a[N-2] = 0;
    b[0] = 1;
    b[N-1] = 1;
    c[0] = 0;

    for (int iter=0; iter < 100; iter++)
    {
        auto tmp = result;
        //Фикс i (y) (считаем строку)
        for (int i=1; i < N-1; i++)
        {
            for (int j=1; j < N-1; j++)
            {
                leftCol[j] = -LAMBDA/(dh*dh) * (result[i+1][j] + result[i-1][j]) - m[i][j]/dt;
            }
            leftCol[0] = std::sin(5 * std::numbers::pi * i * dh) * std::exp(- 50 * std::numbers::pi * std::numbers::pi * LAMBDA * t); // phi(0, y(i), time)
            leftCol[N-1] = -std::sin(5 * std::numbers::pi * i * dh) * std::exp(- 50 * std::numbers::pi * std::numbers::pi * LAMBDA * t);// + sin(t/5); // phi(0, y(i), time)
            auto newRow = SolveThomasAglorithm(a, b, c, leftCol);
            result[i] = newRow;
        }
        result[0] = std::vector<double>(N);
        result[N-1] = std::vector<double>(N);
        // std::fill_n(result[0].begin(), N, sin(t/5));
        if (norm(result, tmp) <= 1e-16) break;
        // std::cout<<norm(result, tmp)<<std::endl;
    }
    return result;
}
Mesh getAnalytic(const Mesh& mesh, const double dt, const double dh, const double T)
{
    const size_t N = mesh.size();
    Mesh result;
    result.resize(N);
    for (int i=0; i<N; i++)
    {
        result[i].resize(N);
    }
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            result[i][j] = cos(std::numbers::pi * j * dh) * sin(5*std::numbers::pi*i*dh)*exp(- 50 * std::numbers::pi * std::numbers::pi * LAMBDA * T);
        }
    }
    return result;
}
void writeTimeEvolution(const Mesh& mesh, const double dt, const double dh, const double T)
{
    Mesh localMesh = mesh;
    const size_t N = mesh.size();
    std::ofstream h;
    std::ofstream t;

    h.open(OUTPUT_DIR"heat.csv");
    t.open(OUTPUT_DIR"htime.csv");
    h << N << std::endl;


    for (int tstep=0; tstep<static_cast<int>(T/dt) + 1; tstep++)
    {
        Mesh newMesh = step(localMesh, dt, dh, tstep * dt);
        Mesh newMeshA = getAnalytic(localMesh, dt, dh, tstep * dt);
        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
            {
                h << newMesh[i][j] - newMeshA[i][j];
                if (j != N-1) h<<",";
            }
            if (i != N-1) h << ",";
        }
        h << std::endl;
        t << tstep * dt << std::endl;
    localMesh = newMesh;
    }
    h.close();
    t.close();
}


int main()
{
    int N = 100;
    double T = 200.0;
    double dh = 1.0 / (N - 1);
    double dt = 0.1;
    Mesh mesh;
    mesh.resize(N);
    for (int i=0; i<N; i++)
    {
        mesh[i].resize(N);
    }
    //Нач условия
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            mesh[i][j] = cos(std::numbers::pi * j * dh) * sin(5*std::numbers::pi*i*dh);
        }
    }

    Mesh meshAnalytic;
    meshAnalytic.resize(N);
    for (int i=0; i<N; i++)
    {
        meshAnalytic[i].resize(N);
    }

    writeTimeEvolution(mesh, dt, dh, T);


    dt = 1e-6;
    T = 0.02;

    std::ofstream errorFile(OUTPUT_DIR"herror.csv");
    const int Ns[] = {10,20,50,100,200,500,1000};
    for (int i=0; i<7; i++)
    {
        dh = 1.0/(Ns[i]-1);
        dt = dh * dh;
        Mesh newMesh;
        newMesh.resize(Ns[i]);
        for (int k=0; k<Ns[i]; k++)
        {
            newMesh[k].resize(Ns[i]);
        }

        for (int g=0; g<Ns[i]; g++)
        {
            for (int j=0; j<Ns[i]; j++)
            {
                newMesh[g][j] = cos(std::numbers::pi * j * dh) * sin(5*std::numbers::pi * g * dh);
            }
        }
        int steps = static_cast<int>(T / dt);
        std::cout << Ns[i] << " " << steps<< std::endl;

        for (int j=0; j<steps; j++)
        {
            newMesh = step(newMesh, dt, dh, (j+1)*dt);
        }

        errorFile << Ns[i] <<","<<norm(newMesh, getAnalytic(newMesh, dt, dh, T)) << std::endl;
    }
    errorFile.close();
}

