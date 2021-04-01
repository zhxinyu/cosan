#ifndef __UTILS_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <vector>

#define __UTILS_H_INCLUDED__

EigenMatrix load_csv(const std::string &path) {
    std::ifstream dataIn;

    dataIn.open(path);
    std::string line;
    std::vector<float> values;
    uint rows = 0;
    while (std::getline(dataIn, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        ++rows;
    }

    return Eigen::Map<EigenMatrix>(values.data(), rows, values.size() / rows);
}


//template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
//void save_csv(const std::string &path, const Eigen::Matrix<_Scalar, _Rows, _Cols> &matrix) {
//    std::ofstream file(path, std::ios::out);
//    if (file.is_open()) {
//        Eigen::IOFormat csvFmt(Eigen::FullPrecision, 0, ",");
//        file << matrix.format(csvFmt);
//        file.close();
//    }
//}

#endif
