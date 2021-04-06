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

	Cosan::CosanMatrix centered = X.rowwise() - X.colwise().mean();
	Cosan::CosanMatrix cov = centered.adjoint() * centered;

	Eigen::SelfAdjointEigenSolver<Cosan::CosanMatrix> eigensolver(cov);
  	if (eigensolver.info() != Eigen::Success) {
  		throw std::invalid_argument("Cannot solve eigenvalue decomposition.");}
  	std::cout<<eigensolver.eigenvalues()<<std::endl;
	std::cout<<eigensolver.eigenvectors()<<std::endl;
	std::cout<<eigensolver.eigenvectors().rightCols(2)<<std::endl;	
	centered = eigensolver.eigenvectors().rightCols(2);
	std::vector<double> vec(eigensolver.eigenvalues().data(), eigensolver.eigenvalues().data() + eigensolver.eigenvalues().size());
	std::reverse(vec.begin(),vec.end());
	std::vector<double> runningSum(vec.size());
	std::partial_sum(vec.begin(), vec.end(), runningSum.begin(), std::plus<double>());
	for (auto & each :runningSum){
		std::cout<<each<<std::endl;
	}



	Cosan::CosanRawData CRD("./example_data/toy2/X_.csv","./example_data/toy2/Y_.csv");
	std::cout<<CRD.GetSummaryMessageX()<<CRD.GetSummaryMessageY()<<std::endl;
	Cosan::OverUnderFlow ouf(CRD);
	Cosan::MissingValues MissV(CRD);
	Cosan::MinmaxScaler MMS(CRD,3,5);		
	auto [value1, value2] = CRD.GetMissingNumber();
	std::cout<<	value1<<value2<<std::endl;
	Cosan::PrincipalComponentAnalysis PCA(CRD,4);

	// std::cout<<M.array().isNaN().sum()<<std::endl;
	// CRD.GetTarget().rows()-CRD.GetTarget().array().isNaN().sum()
	// CRD.GetTarget().array().isNaN().select(0,CRD.GetTarget())

	// std::cout<<CRD.GetTarget().array().isNaN().select(0,CRD.GetTarget()).sum()<<std::endl;

	// std::cout<<(1-CRD.GetTarget().array().isNaN()).cast<double>().array()*CRD.GetTarget().array()<<std::endl;


    return 0;
}
