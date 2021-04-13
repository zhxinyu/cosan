#ifndef __UTILS_UTILS_H_INCLUDED__
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <gsl/gsl>
#include <numeric>
#include <random>
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

std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > TrainTestSplit(gsl::index nrows,double testRatio=0.3){
    assert(testRatio>=0 && testRatio<=1);
    gsl::index ntest = (gsl::index) nrows*(testRatio);
    gsl::index ntrain = nrows - ntest;
    std::vector<int> idx(nrows);
    std::iota(idx.begin(), idx.end(), 0);

    std::vector<gsl::index> trainIdx, testIdx;
    trainIdx.resize(ntrain);
    testIdx.resize(ntest);
    std::sample(idx.begin(), idx.end(), std::back_inserter(testIdx),
                ntest, std::mt19937{std::random_device{}()});
    std::sort(testIdx.begin(),testIdx.end());
    std::set_difference(idx.begin(), idx.end(), trainIdx.begin(), trainIdx.end(),
                        std::inserter(testIdx, testIdx.begin()));
    return {trainIdx,testIdx};
}

std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > TrainTestSplit(std::vector<gsl::index> inputIdx,double testRatio=0.3){
    assert(testRatio>=0 && testRatio<=1);
    gsl::index nrows = inputIdx.size();
    gsl::index ntest = (gsl::index) nrows*(testRatio);
    gsl::index ntrain = nrows - ntest;
    std::vector<int> idx(nrows);
    std::iota(idx.begin(), idx.end(), 0);

    std::vector<gsl::index> trainIdx, testIdx;
    trainIdx.resize(ntrain);
    testIdx.resize(ntest);
    std::sample(inputIdx.begin(), inputIdx.end(), std::back_inserter(testIdx),
                ntest, std::mt19937{std::random_device{}()});
    std::sort(testIdx.begin(),testIdx.end());
    std::sort(inputIdx.begin(),inputIdx.end());
    std::set_difference(inputIdx.begin(), inputIdx.end(), trainIdx.begin(), trainIdx.end(),
                        std::inserter(testIdx, testIdx.begin()));
    return {trainIdx,testIdx};
}

template<typename T>
std::vector<T> linspace(T start_in, T end_in, int num_in)
{

    std::vector<T> linspaced;

    double start = static_cast<double>(start_in);
    double end = static_cast<double>(end_in);
    double num = static_cast<double>(num_in);

    if (num == 0) { return linspaced; }
    if (num == 1)
    {
        linspaced.push_back(start);
        return linspaced;
    }

    double delta = (end - start) / (num - 1);
    for(int i=0; i < num-1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end);
    return linspaced;
}

template<typename T>
void print_vector(std::vector<T> vec)
{
    std::cout << "size: " << vec.size() << std::endl;
    for (T & d : vec)
        std::cout << d << " ";
    std::cout << std::endl;
}
#endif
