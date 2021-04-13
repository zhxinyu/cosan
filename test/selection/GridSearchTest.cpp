//gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/selection/GridSearchTest.cpp

#include <iostream>
#include <vector>
#include <string>
#include <cosan/data/CosanData.h>
// #include <cosan/model/CosanLinearModel.h>
#include <cosan/model/CosanLinearRegression.h>
#include <cosan/model/CosanRidgeRegression.h>
#include <cosan/model/CosanPCRRidge.h>
#include <cosan/selection/gridsearch.h>
#include <cosan/selection/randomgridsearch.h>
#include <cosan/evaluation/CosanMetric.h>
#include <cosan/selection/kfold.h>
#include <cosan/selection/randomkfold.h>
#include <cosan/selection/timeseriessplit.h>
typedef double db;
int main(){
	int x = 5;
	int y = 5;
	Cosan::CosanMatrix<double> X_input = Cosan::CosanMatrix<double>::Zero(x,y);
	// std::cout<<X_input.rows()<<std::endl;
	// X_input.setZero();
	std::cout<<X_input<<std::endl;	


	constexpr gsl::index nrows = 10000;
	constexpr gsl::index ncols = 5;
    Cosan::CosanMatrix<NumericType> X_input
    Cosan::CosanMatrix<NumericType> Y_input;
	X_input.resize(nrows,ncols);
	Y_input.resize(nrows,1);
    X_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows,ncols>::Random();
    Y_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows,1>::Random();
    Cosan::CosanData<NumericType>  CD(X_input,Y_input);
    Cosan::CosanPCRRidge<decltype(X_input)::Scalar> CRRwbias;
    Cosan::MeanSquareError<decltype(X_input)::Scalar> mse;
    NumericType a = 0.05;
    std::vector<NumericType> v(10);
    std::generate(v.begin(), v.end(), [n = 1, &a]() mutable { return n++ * a; });
    Cosan::KFold kf(5);
    Cosan::RandomGridSearch GDS(CD,CRRwbias,mse,kf,v);
//
//    Cosan::CosanLinearRegression<decltype(X_input)::Scalar> CRRwbias(true);
//	// X_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows,ncols>::Random();
	// Y_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows,1>::Random();
	// std::cout<<X_input <<std::endl;
	// std::cout<<Y_input <<std::endl;
//	 X_input = Eigen::Matrix<X_input::Scalr,X_input.rows(),X_input.cols()>::Random();
	Cosan::CosanData<db>  CRD(X_input,Y_input);
	// Cosan::CosanData<db>  CRD(Eigen::Matrix<decltype(X_input)::Scalar,nrows,ncols>::Random()
	// 							,Eigen::Matrix<decltype(X_input)::Scalar,nrows,1>::Random());
	// // Cosan::CosanLinearRegression<decltype(X_input)::Scalar> CRRwbias(true);
	// Cosan::CosanPCRRidge<decltype(X_input)::Scalar> CRRwbias;

	// CRRwbias.fit(CRD.GetInput(),CRD.GetTarget());
	// // std::cout<<CRRwbias.GetParams()<<std::endl;
	// Cosan::CosanMatrix<db> beta = CRRwbias.GetBeta();
	// std::cout<<CRRwbias.predict(CRD.GetInput())<<std::endl;
	// std::cout<<beta<<std::endl;
	// Cosan::MeanSquareError<decltype(X_input)::Scalar> mse;
	// Cosan::MeanAbsError<decltype(X_input)::Scalar> mae;
	// Cosan::R2Score<decltype(X_input)::Scalar> r2;
	// Cosan::MaxError<decltype(X_input)::Scalar> me;

 //    for (auto & each : v){
 //    	std::cout<<each<<std::endl;
 //    }
//    auto a = Cosan::KFoldParallel(11).GetSplit();
 //    // KFoldParallel
 //    // TimeSeriesSplitParallel
 //    // TimeSeriesSplit
 //    // RandomKFoldParallel
 //    // RandomKFold
	// // Cosan::RandomGridSearch GDS1(CRD,CRRwbias,mse,kf,v);
	// std::cout<<Cosan::RandomGridSearch(CRD,CRRwbias,mse,kf,v).GetBestParams()<<std::endl;	
	// // Cosan::RandomGridSearch GDS2(CRD,CRRwbias,mae,kf,v);
	// std::cout<<GDS2.GetBestParams()<<std::endl;
	// Cosan::RandomGridSearch GDS3(CRD,CRRwbias,r2,kf,v);
	// std::cout<<GDS3.GetBestParams()<<std::endl;	
	// Cosan::RandomGridSearch GDS4(CRD,CRRwbias,me,kf,v);
	// std::cout<<GDS4.GetBestParams()<<std::endl;	


	// std::cout<<GDS.GetBestParams()<<std::endl;
   // std::cout<<CRRwbias.predict(X_input)<<std::endl;


	return 0;
}