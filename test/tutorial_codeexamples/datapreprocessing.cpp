//
// Created by Xinyu Zhang on 3/26/21.
//
#include <iostream>
#include <cosan/data/CosanData.h>
#include <cosan/preprocessing/overunderflow.h>
#include <cosan/preprocessing/missingvalues.h>
#include <cosan/preprocessing/normalizer.h>
#include <cosan/preprocessing/standardScaler.h>
#include <cosan/preprocessing/encoder.h>
#include <cosan/preprocessing/minmaxscaler.h>
#include <cosan/preprocessing/polynomialfeatures.h>

typedef double NumericType;
int main() {
    Cosan::CosanRawData<NumericType> CRD("./example_data/toy2/X_.csv","./example_data/toy2/y.csv");
    Cosan::OverUnderFlow ouf(CRD);
    Cosan::MissingValues MissV(CRD);
    Cosan::Normalizer NM(CRD,2);   
    Cosan::StandardScaler SS(CRD);       
    Cosan::Encoder ED(CRD,true);
    NumericType lb=0,ub=1;    
    Cosan::MinmaxScaler MMS(CRD,lb,ub);

    return 0;
}
//    

    // Cosan::CosanLinearRegression CLR(true);
//     CLR.fit(CD.GetInput(),CD.GetTarget());

    // std::cout<<CD.GetrowsX()<<" "<<CD.GetcolsX()<<" "<<std::endl;
    // for (auto each : CD.GetIdxpinfX()) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
    // for (auto each : CD.GetIdxminfX()) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
    // for (auto each : CD.GetIdxmissingX()) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
    // for (auto each : CD.GetcolCatX()) {std::cout<<each<<std::endl;}
    // for (auto each : CD.GetsvaluesX()) {std::cout<<each<<std::endl;}
    // for (const auto & [ key, value ] : CD.GetRawToNumIdx()){
    // 	std::cout<<key<<":"<<value<<std::endl;}
    // for (const auto & [ key, value ] : CD.GetRawToCatIdx()){
    // 	std::cout<<key<<":"<<value<<std::endl;}    	

//     Cosan::CosanRawData CD1("./example_data/toy2/X_2.csv");

//     // Cosan::CosanLinearRegression CLR(true);
// //     CLR.fit(CD.GetInput(),CD.GetTarget());
//     std::cout<<CD1.GetSummaryMessageX()<<std::endl;
//     // std::cout<<CD.GetrowsX()<<" "<<CD.GetcolsX()<<" "<<std::endl;
//     // for (auto each : CD.GetIdxpinfX()) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
//     // for (auto each : CD.GetIdxminfX()) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
//     // for (auto each : CD.GetIdxmissingX()) {std::cout<<each[0]<<" "<<each[1]<<std::endl;}
//     // for (auto each : CD.GetcolCatX()) {std::cout<<each<<std::endl;}
//     // for (auto each : CD.GetsvaluesX()) {std::cout<<each<<std::endl;}
//     for (const auto & [ key, value ] : CD1.GetRawToNumIdx()){
//     	std::cout<<key<<":"<<value<<std::endl;}
//     for (const auto & [ key, value ] : CD1.GetRawToCatIdx()){
//     	std::cout<<key<<":"<<value<<std::endl;}    	

    // std::cout<<CD.GetInput()<<std::endl;

//    double RegularizationTerm = 1;
//    Cosan::CosanRidgeRegression CRR(RegularizationTerm,true);
//    CRR.fit(CD.GetInput(),CD.GetTarget());
//    std::cout<<CRR.GetBeta()<<std::endl;
//    save_csv("./example_data/toy/beta_c1.csv",CRR.GetBeta());

//    m(0, 0) = 3;
//    m(1, 0) = 2.5;
//    m(0, 1) = -1;
//    m(1,1)  = m(1,0)+m(0,1);
//    std::cout<<y.rows()<<y.cols()<<std::endl;
    // Eigen::MatrixXd beta = (X.transpose()*X).ldlt().solve(X.transpose()*y);
    
    
//
//    m.transposeInPlace();
//    cout<<m<<endl;
//    m.resize(1,4);
//    cout<<n<<endl;

