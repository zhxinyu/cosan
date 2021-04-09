#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <Eigen/Dense>
#include <math.h>
#include <cosan/io/utils.h>
int main(int argc, char *argv[]){
    CosanMatrix X;
    std::string SummaryMessageX;
    std::vector<std::vector<uint>> IdxpinfX,IdxminfX,IdxmissingX;
    std::set<uint> colCatX;
    uint rowsX = 0,colsX = 0;
    std::vector<std::string> svaluesX;
//    std::cout<<isinf(stod(std::string("inf")))<<std::endl;
//    std::tie(rowsX,colsX,SummaryMessageX) = _load_csv<Eigen::MatrixXd>(argv[1],X,IdxpinfX,IdxminfX,IdxmissingX,svaluesX,colCatX);
    std::cout<<rowsX<<" "<<colsX<<" "<<std::endl;
    for (auto each : IdxpinfX) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
    for (auto each : IdxminfX) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
    for (auto each : IdxmissingX) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
    for (auto each : colCatX) {std::cout<<each<<std::endl;}
    for (auto each : svaluesX) {std::cout<<each<<std::endl;}
    std::cout<<X<<std::endl;
    return 0;
}
