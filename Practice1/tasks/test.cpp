#include <iostream>
#include <math.h>


int factorial(int n){
    if (n == 0) return 1;
    return factorial(n-1)*n;
}


double partNsin(int n, double t){
    return pow(t, n) * (pow(-1, (int)((double)n/2.0)) * ((n%2==0 ? sin(t) : cos(t))) / factorial(n));
}
double partNe(int n, double t){
    return exp(t) * pow(t, n) / factorial(n);
}



template<double(*partN)(int, double)>
int testT(double t, double dt){
    double error = 0;
    int minN = 1;
    do
    {
        minN++;
        error = abs(partN(minN, t));
        // printf("On n = %d, error = %f\n", minN, error);
        if(error<1e-10) error = dt;
        if(isnan(error)) return 0;
    } while (error>=dt);
    return minN;
}


int main(){
    double dt = 0.001;
    int maxN = 0;


    double a = 0;
    double b = 1;
    double step = 0.1;
    for(int i = 0; i<=(int)((b-a)/step); i++){
        auto newMaxN = testT<partNsin>(a+i*step, dt);
        // printf("new min N = %d, t = %f\n", newMinN, a+i*step);
        maxN = maxN<newMaxN ? newMaxN : maxN; 
    }
    
    printf("Min N = %d, [0,1], sin t\n", maxN);

    // a = 10;
    // b = 11;
    // step = 0.1;
    // for(int i = 0; i<=(int)((b-a)/step); i++){
    //     auto newMaxN = testT<partNsin>(a+i*step, dt);
    //     printf("new min N = %d, t = %f\n", newMaxN, a+i*step);
    //     maxN = maxN<newMaxN ? newMaxN : maxN; 
    // }
    
    printf("Min N = , [10,11], sin t не работает т.к. не в близи нуля\n", maxN); // не работает т.к. не в близи нуля

    a = 0;
    b = 1;
    step = 0.1;
    for(int i = 0; i<=(int)((b-a)/step); i++){
        auto newMaxN = testT<partNe>(a+i*step, dt);
        // printf("new min N = %d, t = %f\n", newMinN, a+i*step);
        maxN = maxN<newMaxN ? newMaxN : maxN; 
    }
    
    printf("Min N = %d, [0,1], e t\n", maxN);

    // a = 10;
    // b = 11;
    // step = 0.1;
    // for(int i = 0; i<=(int)((b-a)/step); i++){
    //     auto newMaxN = testT<partNe>(a+i*step, dt);
    //     // printf("new min N = %d, t = %f\n", newMinN, a+i*step);
    //     maxN = maxN<newMaxN ? newMaxN : maxN; 
    // }
    
    printf("Min N = , [0,1], e t, не работает т.к. не в близи нуля\n", maxN);

}