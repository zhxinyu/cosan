//
// Created by Xinyu Zhang on 3/26/21.
//
// gcc -I/Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan /Users/xinyuzhang/Desktop/Spring2021/c++pattern/project/cosan/test/preprocessor/OverUnderFlowTest.cpp 

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <cosan/data/CosanData.h>
#include <gsl/gsl>
#include <cosan/preprocessing/overunderflow.h>
#include <vector>
//using namespace Eigen;
//using namespace std;

typedef double NumericType;
int main() {

	Cosan::CosanRawData<NumericType> CRD("./example_data/toy2/X_.csv","./example_data/toy2/Y_.csv");
//	std::cout<<CRD.GetSummaryMessageX()<<CRD.GetSummaryMessageY()<<std::endl;
	Cosan::OverUnderFlow ouf(CRD);

	myarray = myarray.unaryExpr([](double v) { return std::isfinite(v)? v : 0.0; });

	std::cout<<(1-CRD.GetTarget().array().isNaN()).cast<double>().array()*CRD.GetTarget().array()<<std::endl;
	int a = 1;

	std::string cout;
	cout =(a==1 ? "Hello!":"I am doing good!") ;
	std::cout<<CRD.GetTarget().size() <<std::endl; 
	// std::vector<std::vector<gsl::index>> a({{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11}});
	// std::vector<std::vector<gsl::index>> b;
 //  	select(b, a, {3,4,7,9});	
	// // std::transform(a.begin(),a.end(),b.begin(),[]()->bool {});
	// std::cout<<b.size()<<std::endl;
	// for (auto each: b){
	// 	std::cout<<each[0]<<each[1]<<std::endl;
	// }

	// gsl::index c=11,d=5;
	// std::cout<<c/d<<std::endl;



    return 0;
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;
}
