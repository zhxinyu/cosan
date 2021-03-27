//
// Created by Xinyu Zhang on 3/26/21.
//
#include <iostream>
#include <Eigen/Dense>
// #include "utils.h"
#include <fstream>
#include <vector>
//using namespace Eigen;
//using namespace std;

template<typename Matrix>
Matrix load_csv (const std::string & path) {
    std::ifstream indata;

    indata.open(path);
    std::string line;
    std::vector<double> values;
    uint rows = 0;
    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream, cell, ',')) {
            values.push_back(stod(cell));
        }
        ++rows;
    }

    return Eigen::Map<const Eigen::Matrix<typename Matrix::Scalar, Matrix::RowsAtCompileTime, Matrix::ColsAtCompileTime, Eigen::RowMajor> >(values.data(), rows, values.size()/rows);
}

template<typename Matrix>
void save_csv(const std::string & path, const Matrix & matrix){
//    if (path.substr(path.size()-4)!=".csv"){
//        path.append(".csv");
//    }
    std::ofstream file(path,std::ios::out);
    if (file.is_open()){
        Eigen::IOFormat csvFmt(Eigen::FullPrecision,0,",");
        file<<matrix.format(csvFmt);
        file.close();
    }
}



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
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;
}
