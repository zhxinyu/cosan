#ifndef __UTILS_UTILS_H_INCLUDED__
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <gsl/gsl>
#define __UTILS_UTILS_H_INCLUDED__

template<typename Matrix>
void removeRow(Matrix& matrix, gsl::index rowToRemove)
{
    gsl::index numRows = matrix.rows()-1;
    gsl::index numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols).eval();

    matrix.conservativeResize(numRows,numCols);
}
template<typename Matrix>
void removeColumn(Matrix& matrix, gsl::index colToRemove)
{
    gsl::index numRows = matrix.rows();
    gsl::index numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove).eval();

    matrix.conservativeResize(numRows,numCols);
}

template <typename T>
void select(std::vector<T>& result, const std::vector<T>& in, const std::vector<typename std::vector<T>::size_type>& s) {
    result.reserve(s.size());
    std::transform(s.begin(), s.end(), std::back_inserter(result),
                   [&in](typename std::vector<T>::size_type idx) {
                       return in.at(idx);
                   });
}


#endif
