#ifndef __UTILS_H_INCLUDED__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <math.h>
#include <Eigen/Dense>
#include <gsl/gsl>
#define __UTILS_H_INCLUDED__
#include <cosan/base/CosanBO.h>
namespace Cosan{
    /**
     * @brief General string to number conversion function
     * @details As we allow for user-determined numeric type `NumericType`, the detailed implementation or functions needed maybe slightly
     * different among each other. For instance, when we are trying to read data from `csv` file. Different data type requires different
     * string-to-numeric function. For `double`, one is required `std::stod` while 'std::stof' is the candidate function if
     * `float` is chosen. To take care of this variant before running time, we conside the static-i. The feature
     * allows us to discard branches of an if statement at compile-time based on a constant expression condition. In the following
     * code as an example, we define a template function with input requiring `NumericType` as numeric and then the implementation
     * is decided via `if constexpr` statement.
     **/
    template<Numeric NumericType>
    NumericType StringToNum(const std::string& arg, std::size_t* pos = 0) {
        static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
        if constexpr (std::is_same_v<NumericType, unsigned long>) {
            return std::stoul(arg,pos);
        }
        else if constexpr (std::is_same_v<NumericType, unsigned long long>){
            return std::stoull(arg,pos);
        }
        else if constexpr (std::is_same_v<NumericType, int>){
            return std::stoi(arg,pos);
        }
        else if constexpr (std::is_same_v<NumericType, long>){
            return std::stol(arg,pos);
        }
        else if constexpr (std::is_same_v<NumericType, long long>){
            return std::stoll(arg,pos);
        }
        else if constexpr (std::is_same_v<NumericType, float>){
            return std::stof(arg,pos);
        }
        else if constexpr (std::is_same_v<NumericType, double>){
            return std::stod(arg,pos);
        }
        else{
            return std::stold(arg,pos);
        }
    }
}

template<typename Matrix>
Matrix load_csv1 (const std::string & path) {
    std::ifstream indata;

    indata.open(path);
    std::string line;
    std::vector<double> values;
    gsl::index rows = 0;
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
