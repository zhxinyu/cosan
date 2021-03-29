//
// Created by Xinyu Zhang on 3/26/21.
//
#include <iostream>
// #include <Eigen/Dense>
// #include <cosan/io/utils.h>
#include <cosan/data/CosanData.h>
#include <cosan/model/CosanLinearRegression.h>
#include <cosan/model/CosanRidgeRegression.h>
//using namespace Eigen;
//using namespace std;

int main() {
    Cosan::CosanData CD("./data/toy/X.csv","./data/toy/y.csv");
    // Cosan::CosanLinearRegression CLR(true);
    // CLR.fit(CD.GetInput(),CD.GetTarget());

    double RegularizationTerm = 1;
    Cosan::CosanRidgeRegression CRR(RegularizationTerm,true);
    CRR.fit(CD.GetInput(),CD.GetTarget());
    std::cout<<CRR.GetBeta()<<std::endl;    
    save_csv("./data/toy/beta_c1.csv",CRR.GetBeta());

//    m(0, 0) = 3;
//    m(1, 0) = 2.5;
//    m(0, 1) = -1;
//    m(1,1)  = m(1,0)+m(0,1);
//    std::cout<<y.rows()<<y.cols()<<std::endl;
    // Eigen::MatrixXd beta = (X.transpose()*X).ldlt().solve(X.transpose()*y);
    
    return 0;
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;
}
