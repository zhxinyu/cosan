//gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/ItemplateTest.cpp 
#include <iostream>
#include <cosan/data/CosanData.h>
#include <cosan/preprocessing/overunderflow.h>
#include <cosan/preprocessing/missingvalues.h>
#include <cosan/preprocessing/standardScaler.h>
#include <cosan/preprocessing/normalizer.h>
#include <cosan/preprocessing/minmaxscaler.h>
#include <cosan/preprocessing/polynomialfeatures.h>
#include <cosan/preprocessing/principalcomponentanalysis.h>
int main(){
	Cosan::CosanRawData<long double> CRD("./example_data/toy2/X_.csv");
    std::cout<<CRD.GetSummaryMessageX()<<std::endl;	
	Cosan::OverUnderFlow  OUF(CRD);	
	// std::cout<<CRD.GetrowsX()<<std::endl;
 //    std::cout<<CRD.GetInput()<<std::endl;    	
	Cosan::MissingValues  MSV(CRD);		
	Cosan::StandardScaler SS(CRD);
	Cosan::Normalizer NM(CRD,2);
	// double a = 2,b=6;
	Cosan::MinmaxScaler MMS(CRD,(long double )2,(long double )6);	
	Cosan::PolynomialFeatures PF(CRD,{{1,0},{1,1}});
	Cosan::PrincipalComponentAnalysis PCA(CRD);
	std::cout<<PCA.GetPC()<<std::endl;
	Cosan::CosanMatrix<double> M;
	M.resize(4,2);
	M<<1,2,3,4,5,6,7,8;
	std::vector idx = {0,2};
	std::cout<<M<<std::endl;
	std::cout<<M(idx,Eigen::all)<<std::endl;
	return 0;
}