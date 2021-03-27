#ifndef __UTILS_H_INCLUDED__
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
#define __UTILS_H_INCLUDED__

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
#endif
