//
// Created by Xinyu Zhang on 3/26/21.
//
// gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/preprocessor/PCATest.cpp 

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <cosan/data/CosanData.h>
#include <gsl/gsl>
#include <cosan/preprocessing/overunderflow.h>
#include <cosan/preprocessing/missingvalues.h>
#include <cosan/preprocessing/minmaxscaler.h>
#include <cosan/preprocessing/principalcomponentanalysis.h>
// #include <cosan/preprocessing/polynomialfeatures.h>
#include <vector>
#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif
#include <fmt/format.h>
#include <numeric>
//using namespace Eigen;
//using namespace std;


int main() {

	// std::cout<<	value1<<value2<<std::endl;
	// std::cout<<X.col(i).array().isNaN().sum()<<std::endl;
	Cosan::CosanMatrix X{5,3};
	X << 1,2,2,
	     4,3,4,
	     2,4,6,
	     12,51,6,
	     435,4,15;	     	     
	// (X.array().colwise()-X.colwise().minCoeff())/X.colwise().maxCoeff()-X.colwise().minCoeff();
    std::cout<<X<<std::endl;

    X.conservativeResize(X.rows(),X.cols()+1);
    X.col(X.cols()-1) = X.col(0).array().pow(1.2);

    std::cout<<X<<std::endl;

	// Cosan::CosanRawData CRD("./example_data/toy2/X_.csv","./example_data/toy2/Y_.csv");
	// std::cout<<CRD.GetSummaryMessageX()<<CRD.GetSummaryMessageY()<<std::endl;
	// Cosan::OverUnderFlow ouf(CRD);
	// Cosan::MissingValues MissV(CRD);
	// Cosan::MinmaxScaler MMS(CRD,3,5);		
	// auto [value1, value2] = CRD.GetMissingNumber();
	// std::cout<<	value1<<value2<<std::endl;
	// Cosan::PrincipalComponentAnalysis PCA(CRD,4);

	// std::cout<<M.array().isNaN().sum()<<std::endl;
	// CRD.GetTarget().rows()-CRD.GetTarget().array().isNaN().sum()
	// CRD.GetTarget().array().isNaN().select(0,CRD.GetTarget())

	// std::cout<<CRD.GetTarget().array().isNaN().select(0,CRD.GetTarget()).sum()<<std::endl;

	// std::cout<<(1-CRD.GetTarget().array().isNaN()).cast<double>().array()*CRD.GetTarget().array()<<std::endl;


    return 0;
}
