//
// Created by zahar on 12.10.2025.
//

#ifndef PRACTICE1_NEWTON_HPP
#define PRACTICE1_NEWTON_HPP
#include <vector>


class Newton
{
    std::vector<double> coeffs;
    std::vector<double> x0;
    size_t N;
    struct node
    {
        double value;
        double leftX;
        double rightX;
    };

    void calculateCoefs(const std::vector<node>& points){
        std::vector<node> tmp1 = points;
        std::vector<node> tmp2 = points;
        // std::vector<double> coeffs;
        // coeffs.push_back(points[0].value);
        coeffs.push_back(points[0].value);
        size_t tmpN = N;
        while (tmpN>1)
        {
            for(size_t i=0; i + 1 < tmpN; i++){
                tmp2[i].value = (tmp1[i+1].value - tmp1[i].value) / (tmp1[i+1].rightX - tmp1[i].leftX);
                tmp2[i].leftX = tmp1[i].leftX;
                tmp2[i].rightX = tmp1[i+1].rightX;
            }
            tmpN--;
            coeffs.push_back(tmp2[0].value);
            tmp1 = tmp2;
        }
    }
    public:
    Newton(const std::vector<double>& x, const std::vector<double>& u): x0(x), N(x.size())
    {
        std::vector<node> points(N);
        for (int i=0; i<N; i++)
        {
            points[i]=node(u[i],x[i], x[i]);
        }
        calculateCoefs(points);
    }



    double interpolate(const double x){
        double result = coeffs[0];
        double tmpTerm = 1;
        // std::cout<<result<<" +";
        for(int i=0; i+1<coeffs.size(); i++){
            // std::cout<<" "<<coeffs[i+1]<<" * ";
            for(int j=0; j<=i; j++){
                tmpTerm *= x - x0[j];
                // std::cout<<"(x - "<<x0[j]<<")";
            }
            tmpTerm *= coeffs[i+1];
            result += tmpTerm;
            // std::cout<<" +";
            tmpTerm=1;
        }
        return result;
    }
};



#endif //PRACTICE1_NEWTON_HPP