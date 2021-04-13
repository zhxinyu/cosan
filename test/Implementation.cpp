//
// Created by Xinyu Zhang on 3/26/21.
//
#include <iostream>
// #include <Eigen/Dense>
// #include <cosan/io/utils.h>
#include <cosan/selection/randomgridsearch.h>
#include <cosan/selection/gridsearch.h>
#include <cosan/selection/kfold.h>
#include <cosan/selection/timeseriessplit.h>
#include <cosan/selection/randomkfold.h>
#include <cosan/utils/utils.h>
#include <cosan/data/CosanData.h>
#include <cosan/model/CosanPCRRidge.h>
#include <cosan/model/CosanPrincipalComponentRegression.h>
#include <cosan/model/CosanRidgeRegression.h>
#include <cosan/model/CosanLinearRegression.h>
#include <cosan/preprocessing/customtransform.h>
#include <cosan/preprocessing/encoder.h>
#include <cosan/preprocessing/minmaxscaler.h>
#include <cosan/preprocessing/missingvalues.h>
#include <cosan/preprocessing/normalizer.h>
#include <cosan/preprocessing/onehotEncoder.h>
#include <cosan/preprocessing/ordinalEncoder.h>
#include <cosan/preprocessing/overunderflow.h>
#include <cosan/preprocessing/polynomialfeatures.h>
#include <cosan/preprocessing/preprocessor.h>
#include <cosan/preprocessing/principalcomponentanalysis.h>
#include <cosan/preprocessing/standardScaler.h>
// #include <cosan/model/CosanLinearRegression.h>
// #include <cosan/model/CosanRidgeRegression.h>
//using namespace Eigen;
//using namespace std;
// gcc -I. ./test/Implementation.cpp
typedef double db;
int main() {
	fmt::print("fmt library can be used", 42);
//  Data Reading
	constexpr gsl::index nrows = 3;
	constexpr gsl::index ncols = 3;


    Cosan::CosanMatrix<db> CM;
    CM.resize(nrows,ncols);
    CM<< 1,2,3,
        4,5,6,
        7,8,9;
    Cosan::CosanData<db>  CD0(CM);
    std::vector<db> inputX({1,2,3,4,5,6});
    Cosan::CosanData<db>  CD1(inputX,inputX,6,"rowfirst");
    std::cout<<CD1.GetInput()<<std::endl;
    db lb=0,ub=1;
    Cosan::CosanData<db> CD2(3,4,lb,ub);
    std::cout<<CD2.GetInput()<<std::endl;

//  Data Preprocessing
    Cosan::CosanRawData<db> CRD("./example_data/toy2/X_.csv","./example_data/toy2/Y_.csv");
    std::cout<<CRD.GetSummaryMessageX()<<std::endl;
    std::cout<<CRD.GetSummaryMessageY()<<std::endl;    
	Cosan::OverUnderFlow  OUF(CRD);	
	Cosan::MissingValues  MSV(CRD);		
	Cosan::StandardScaler SS(CRD);
	Cosan::Normalizer NM(CRD,2);
    Cosan::Encoder ED(CRD,true);
    lb = 2;
    ub=6;
	Cosan::MinmaxScaler MMS(CRD,lb,ub);	
	Cosan::PolynomialFeatures PF(CRD,{{1,0},{1,1}});
	Cosan::PrincipalComponentAnalysis PCA(CRD);
	std::cout<<PCA.GetPC()<<std::endl;
//  Model fitting
	Cosan::CosanRawData<db> CD("./example_data/toy/X.csv","./example_data/toy/y.csv");
	Cosan::CosanLinearRegression<db> CLRwbias(true);
	CLRwbias.fit(CD.GetInput(),CD.GetTarget());
	std::cout<<CLRwbias.GetBeta()<<std::endl;
	std::cout<<(CLRwbias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;   
	Cosan::CosanLinearRegression<db> CLRwobias(false);
	CLRwobias.fit(CD.GetInput(),CD.GetTarget());
	std::cout<<CLRwobias.GetBeta()<<std::endl;  
	std::cout<<(CLRwobias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;   

	db RegularizationTerm = 1;
	Cosan::CosanRidgeRegression<db> CRRwBias(RegularizationTerm,true);
	CRRwBias.fit(CD.GetInput(),CD.GetTarget());
	std::cout<<CRRwBias.GetBeta()<<std::endl;
	std::cout<<(CRRwBias.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;   

	gsl::index ncomp = 4;
	Cosan::CosanPrincipalComponentRegression<db> CPCR(ncomp);
	CPCR.fit(CD.GetInput(),CD.GetTarget());
	std::cout<<CPCR.GetBeta()<<std::endl;
	std::cout<<(CPCR.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;


	db regularier = 0.01;
	Cosan::CosanPCRRidge<db> CPCRR({ncomp,regularier});
	CPCRR.fit(CD.GetInput(),CD.GetTarget());
	std::cout<<CPCRR.GetBeta()<<std::endl;
	std::cout<<(CPCRR.predict(CD.GetInput())-CD.GetTarget()).norm()<<std::endl;
	std::cout<<CD.GetcolsX()<<std::endl;


	constexpr gsl::index nrows1 = 10000;
	constexpr gsl::index ncols1 = 10;

    Cosan::CosanMatrix<db> X_input;
    Cosan::CosanMatrix<db> Y_input;
	X_input.resize(nrows1,ncols1);
	Y_input.resize(nrows1,1);
    X_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows1,ncols1>::Random();
    Y_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows1,1>::Random();
    Cosan::CosanData CD_search(X_input,Y_input);
// 	Cosan::CosanRidgeRegression<db> CRRwBias(RegularizationTerm,true);
    Cosan::MeanSquareError<decltype(X_input)::Scalar> mse;
    db a = 0.05;
    std::vector<db> v(10);
    std::generate(v.begin(), v.end(), [n = 1, &a]() mutable { return n++ * a; });
    Cosan::KFold kf(5);
    Cosan::GridSearch GDS(CD_search,CRRwBias,mse,kf,v);
    fmt::print("The best params selected is\n ");
    std::cout<<GDS.GetBestParams()<<std::endl;
//  Grid Search

    return 0;
}
