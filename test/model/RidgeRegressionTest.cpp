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
typedef double db;
int main() {
   Cosan::CosanRawData<db> CD("./example_data/toy/X.csv","./example_data/toy/y.csv");
   db RegularizationTerm = 1;
   Cosan::CosanRidgeRegression<db> CRRwBias(RegularizationTerm,true);
   CRRwBias.fit(CD.GetInput(),CD.GetTarget());
   std::cout<<CRRwBias.GetBeta()<<std::endl;
   std::cout<<(CRRwBias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;   
   return 0;
}
