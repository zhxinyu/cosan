//
// Created by Xinyu Zhang on 3/26/21.
//
// gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/model/RidgeRegressionTest.cpp
#include <iostream>
// #include <Eigen/Dense>
// #include <cosan/io/utils.h>
#include <cosan/data/CosanData.h>
#include <cosan/model/CosanLinearRegression.h>
#include <cosan/model/CosanRidgeRegression.h>
//using namespace Eigen;
//using namespace std;

int main() {
   Cosan::CosanRawData CD("./example_data/toy/X.csv","./example_data/toy/y.csv");
   double RegularizationTerm = 1;
   Cosan::CosanRidgeRegression CRRwBias(RegularizationTerm,true);
   CRRwBias.fit(CD.GetInput(),CD.GetTarget());
   std::cout<<CRRwBias.GetBeta()<<std::endl;
   std::cout<<(CRRwBias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;   
   RegularizationTerm = 0.0001;
   Cosan::CosanRidgeRegression CRRwoBias(RegularizationTerm,false);
   CRRwoBias.fit(CD.GetInput(),CD.GetTarget());
   std::cout<<CRRwoBias.GetBeta()<<std::endl;
   std::cout<<(CRRwoBias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;      
//    save_csv("./example_data/toy/beta_c1.csv",CRR.GetBeta());
    return 0;
}
