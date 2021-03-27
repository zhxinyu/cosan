//
// Created by Xinyu Zhang on 3/26/21.
//
// #include <iostream>
// #include <Eigen/Dense>
#include "utils.h"
//using namespace Eigen;
//using namespace std;

int main() {
    Eigen::MatrixXd X = load_csv<Eigen::MatrixXd>("./data/toy/X.csv");
    Eigen::MatrixXd y = load_csv<Eigen::MatrixXd>("./data/toy/y.csv");

//    m(0, 0) = 3;
//    m(1, 0) = 2.5;
//    m(0, 1) = -1;
//    m(1,1)  = m(1,0)+m(0,1);
//    std::cout<<y.rows()<<y.cols()<<std::endl;
    Eigen::MatrixXd beta = (X.transpose()*X).ldlt().solve(X.transpose()*y);
    save_csv("./data/toy/beta_c.csv",beta);
    return 0;
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;
}
