#include <iostream>
#include <vector>
#include <fstream>
#include "interpolators/spline.hpp"
#include "interpolators/newton.hpp"



int main(){
    std::vector<double> x = {
        1910,
        1920,
        1930,
        1940,
        1950,
        1960,
        1970,
        1980,
        1990,
        2000
    };
    std::vector<double> u = {
        92'228'496 ,
        106'021'537 ,
        123'202'624 ,
        132'164'569 ,
        151'325'798 ,
        179'323'175 ,
        203'211'926 ,
        226'545'805 ,
        248'709'873 ,
        281'421'906
    };
    // std::vector<double> x = {
    //     0,
    //     1,
    //     2
    // };
    // std::vector<double> u = {
    //     0,
    //     1,
    //     4
    // };


    Newton newtonPol(x, u);
    spline mySpline(x, u);

    std::ofstream file("/home/zahar/Edu/CompMath/CompMath/Practice1/tasks/output/out.csv");
    double a=1910;
    double b=2010;
    double rightAnswer=308745538;
    double step=5;
    printf("In 2010 will be: %d by Newton polynom\n", (int) newtonPol.interpolate(2010));
    for(int stepIdx = 0; stepIdx <= ((b-a)/step); stepIdx++){
        file<<a+stepIdx*step<<","<<newtonPol.interpolate(a+stepIdx*step)<<"\n";
    }
    file.close();


    file.open("/home/zahar/Edu/CompMath/CompMath/Practice1/tasks/output/outSpline.csv");
    printf("In 2010 will be: %d by Cubic Spline polynom\n", (int)mySpline.interpolate(2010));
    for(int stepIdx = 0; stepIdx <= ((b-a)/step); stepIdx++){
        file<<a+stepIdx*step<<","<<mySpline.interpolate(a+stepIdx*step)<<"\n";
    }
    file.close();
    printf("Difference Newton is %.4e, with relative error %0.4f %%\n", newtonPol.interpolate(2010) - (int)mySpline.interpolate(2010), (newtonPol.interpolate(2010) - (int)mySpline.interpolate(2010)) * 100 / rightAnswer);
    printf("Difference Cubic Spline %.4e, with relative error %0.4f %%", std::abs(mySpline.interpolate(2010) - rightAnswer), std::abs(mySpline.interpolate(2010) - rightAnswer)*100/ rightAnswer);
}