#include "LinearSystemSolver.h"




class spline{
    std::vector<std::array<double, 4>> coeffs;
    std::vector<double> coeffs_c;
    std::vector<double> u;
    std::vector<double> x0;
    size_t N;
    void calculateCoeffs()
    {
        std::vector<double> a_line;
        std::vector<double> b_line;
        std::vector<double> c_line;
        std::vector<double> B;

        for(int i=0; i<N-2; i++){
            b_line.push_back(2);
        }
        for(int i=0; i<N-3; i++){
            c_line.push_back((x0[i+2] - x0[i+1])/(x0[i+2] - x0[i]));
            a_line.push_back((x0[i+1] - x0[i])/(x0[i+2] - x0[i]));
        }
        for(int i=0; i<N-2;i++){
            B.push_back(6 * ((u[i+2]-u[i+1])/(x0[i+2]-x0[i+1]) - (u[i+1]-u[i])/(x0[i+1]-x0[i]))/ (x0[i+2] - x0[i]));
        }
        coeffs_c = SolveThomasAglorithm(a_line, b_line, c_line, B);

        for(int i=0; i < N-1; i++){
            coeffs[i][0] = u[i+1];
        }
        for(int i=0; i < N-2; i++){
            coeffs[i][2] = coeffs_c[i];
        }
        coeffs.back()[2] = 0;
        coeffs[0][1] = coeffs[0][2] * (x0[1]-x0[0])/3 + (u[1] - u[0]) / (x0[1] - x0[0]);
        coeffs[0][3] = coeffs[0][2] / (x0[1] - x0[0]);

        for (int i = 1; i < N-1; ++i) {
            coeffs[i][1] = (coeffs[i][2] / 3 + coeffs[i - 1][2] / 6) * (x0[i + 1] - x0[i]) + (u[i + 1] - u[i]) / (x0[i + 1] - x0[i]);
            coeffs[i][3] = (coeffs[i][2] - coeffs[i - 1][2]) / (x0[i + 1] - x0[i]);
        }
    };

    public:
        spline(const std::vector<double>& x, const std::vector<double>& u) : x0(x), u(u), coeffs(x.size()-1), coeffs_c(x.size()-1) {
            N = x.size();
            calculateCoeffs();
        }

        double interpolate(const double x)
        {
            double res=0;
            for(int i=0; i<N-1; i++){
                if (x0[i]<=x && x<=x0[i+1])
                {
                    double h = x - x0[i+1];
                    return coeffs[i][0] + coeffs[i][1] * h + coeffs[i][2] * h * h / 2 + coeffs[i][3] * h * h * h / 6;
                }
            }
            if (x>x0.back())
            {
                double h = x - x0.back();
                return coeffs.back()[0] + coeffs.back()[1] * h + coeffs.back()[2] * h * h / 2 + coeffs.back()[3] * h * h * h / 6;
            }
            if (x<x0[0])
            {
                double h = x - x0[0];
                return coeffs[0][0] + coeffs[0][1] * h + coeffs[0][2] * h * h / 2 + coeffs[0][3] * h * h * h / 6;
            }
            return res;
        }
};