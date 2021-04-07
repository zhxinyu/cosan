//gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/selection/GridSearchTest.cpp

#include <iostream>
#include <vector>
#include <cosan/data/CosanData.h>
#include <cosan/model/CosanLinearRegression.h>
#include <cosan/model/CosanRidgeRegression.h>
#include <cosan/selection/gridsearch.h>
#include <cosan/utils/CosanMetric.h>
#include <cosan/selection/kfold.h>
int main(){
	Cosan::CosanMatrix<double> X_input;
	Cosan::CosanMatrix<double> Y_input;	
	X_input.resize(10000,5);
	Y_input.resize(10000,1);
	X_input = Eigen::Matrix<decltype(X_input)::Scalar,10000,5>::Random();
	Y_input = Eigen::Matrix<decltype(X_input)::Scalar,10000,1>::Random();
	// std::cout<<X_input <<std::endl;
	// std::cout<<Y_input <<std::endl;
	// X_input = Eigen::Matrix<X_input::Scalr,X_input.rows(),X_input.cols()>::Random();	

	Cosan::CosanData<double>  CRD(X_input,Y_input);

	Cosan::CosanRidgeRegression<decltype(X_input)::Scalar> CRRwbias(0.1);
	CRRwbias.fit(CRD.GetInput(),CRD.GetTarget());
	std::cout<<CRRwbias.GetParams()<<std::endl;
	Cosan::MeanSquareError<decltype(X_input)::Scalar> mse;
	Cosan::MeanAbsError<decltype(X_input)::Scalar> mae;
	Cosan::R2Score<decltype(X_input)::Scalar> r2;
	Cosan::MaxError<decltype(X_input)::Scalar> me;
	// Cosan::LpNormError<decltype(X_input)::Scalar>(2) lpnorm;	
    double a = 0.11;
    std::vector<double> v(10);
    std::generate(v.begin(), v.end(), [n = 1, &a]() mutable { return n++ * a; });
    Cosan::KFold kf(5);
	Cosan::GridSearch GDS(CRD,CRRwbias,mse,kf,v);
	std::cout<<GDS.GetBestParams()<<std::endl;
   // std::cout<<CRRwbias.predict(X_input)<<std::endl;


	return 0;
}