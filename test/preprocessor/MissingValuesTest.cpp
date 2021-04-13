//
// Created by Xinyu Zhang on 3/26/21.
//
// gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/preprocessor/MissingValuesTest.cpp 

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <cosan/data/CosanData.h>
#include <gsl/gsl>
#include <cosan/preprocessing/overunderflow.h>
#include <cosan/preprocessing/missingvalues.h>
#include <vector>
//using namespace Eigen;
//using namespace std;


int main() {

	Cosan::CosanRawData<double> CRD("./example_data/toy2/X_.csv","./example_data/toy2/Y_.csv");
	std::cout<<CRD.GetSummaryMessageX()<<CRD.GetSummaryMessageY()<<std::endl;
	Cosan::OverUnderFlow ouf(CRD);
	Cosan::MissingValues MissV(CRD);	
	auto [value1, value2] = CRD.GetMissingNumber();
	std::cout<<	value1<<value2<<std::endl;
	// std::cout<<X.col(i).array().isNaN().sum()<<std::endl;
	// Eigen::MatrixXd M{3,3};
	// M << 1,2,2,
	//      4,3,4,
	//      2,4,6;
	// std::cout<<M.array().isNaN().sum()<<std::endl;
	// CRD.GetTarget().rows()-CRD.GetTarget().array().isNaN().sum()
	// CRD.GetTarget().array().isNaN().select(0,CRD.GetTarget())

	// std::cout<<CRD.GetTarget().array().isNaN().select(0,CRD.GetTarget()).sum()<<std::endl;

	// std::cout<<(1-CRD.GetTarget().array().isNaN()).cast<double>().array()*CRD.GetTarget().array()<<std::endl;


    return 0;
}
