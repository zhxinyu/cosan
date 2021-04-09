//
// Created by Xinyu Zhang on 3/26/21.
//
// gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/preprocessor/StandardScalerTest.cpp 

#include <iostream>
// #include <Eigen/Dense>
// #include <cosan/io/utils.h>
#include <cosan/preprocessing/standardScaler.h>
#include <vector>
//using namespace Eigen;
//using namespace std;

int main() {

    EigenMatrix X{3,3};
    X << 2, -1, 2,
         2, 0, 0,
         1, 1, -1;
    Cosan::StandardScaler ss1{};
    ss1.fit(X);
    std::cout << ss1.GetMean() << '\n' << std::endl;
    std::cout << ss1.GetStd() << '\n' << std::endl;
    std::cout << ss1.transform(X)<< '\n' << std::endl;
    std::cout << ss1.InvTransform(ss1.transform(X))<< '\n' << std::endl;    

    Cosan::StandardScaler ss2{};
    std::cout << ss2.standardize(X) << std::endl;

    return 0;
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;
}
