//
// Created by Xinyu Zhang on 3/26/21.
//
// gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/model/LinearRegressionTest.cpp
#include <iostream>
// #include <Eigen/Dense>
// #include <cosan/io/utils.h>
#include <cosan/data/CosanData.h>
#include <cosan/model/CosanLinearRegression.h>
#include <cosan/model/CosanRidgeRegression.h>
//using namespace Eigen;
//using namespace std;
#include <fmt/format.h>
int main() {
   Cosan::CosanRawData CD("./example_data/toy/X.csv","./example_data/toy/y.csv");
   Cosan::CosanLinearRegression CLRwbias(true);
   CLRwbias.fit(CD.GetInput(),CD.GetTarget());
   std::cout<<CLRwbias.GetBeta()<<std::endl;
   std::cout<<(CLRwbias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;   
   Cosan::CosanLinearRegression CLRwobias(false);
   CLRwobias.fit(CD.GetInput(),CD.GetTarget());
   std::cout<<CLRwobias.GetBeta()<<std::endl;  
   std::cout<<(CLRwobias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;   

   std::string output = fmt::format("The answer is {}.", 42);
   return 0;
}
