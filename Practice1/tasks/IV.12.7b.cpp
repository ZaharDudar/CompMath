#include <iostream>
#include <math.h>

/**
 * где h - высота функции x*exp(x^2) равная 1/sqrt(2) * exp(-1/2)
 */
constexpr double h = (1/std::sqrt(2)) * exp(-0.5);

/**
 *  Считает итерацию по формуле
 *  x[n+1] = h/2 * exp(x[n]^2)  
 * 
 *  
 *  сойдётся когда h x exp(x^2) < 1, тоесть к корню около 0
 */
double iter1(double x){
    return h/2 * exp(x*x);
}

/**
 *  Считает итерацию по формуле
 *  x[n+1] = sqrt(ln(x/h))  
 * 
 */
double iter2(double x){
    return sqrt(log(2*x/h));
}

int main(){
    double X0left  = 0.8;
    double X0right = 1;

    printf("%f", h/2);

    double newX = 0;
    double X = X0left;
    for(int i=0; i<1000; i++){
        newX = iter1(X);
        if(abs(newX - X) <= std::numeric_limits<double>::epsilon()) break;
        printf("step = %f\n", newX);
        X = newX;
    }
    auto leftX = X;
    printf("Левый корень = %.10f\n", X);

    newX = 0;
    X = X0right;
    for(int i=0; i<1000; i++){
        newX = iter2(X);
        if(abs(newX - X) <= std::numeric_limits<double>::epsilon()) break;

        X = newX;
    }
    printf("Правый корень = %.10f\n", X);
    auto rigthX = X;

    printf("Ширина = %.10f\n", std::abs(leftX-rigthX));
}