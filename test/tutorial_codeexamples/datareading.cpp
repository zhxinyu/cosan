//
// Created by Xinyu Zhang on 3/26/21.
//
#include <iostream>
#include <cosan/data/CosanData.h>
typedef double NumericType;
int main() {
    Cosan::CosanRawData<NumericType> CRD("./example_data/toy2/X_.csv");
    std::cout<<CRD.GetSummaryMessageX()<<std::endl;
    int nrows = 3;
    int ncols = 3;
    Cosan::CosanMatrix<NumericType> CM;
    CM.resize(nrows,ncols);
    CM<< 1,2,3,
        4,5,6,
        7,8,9;
    Cosan::CosanData<NumericType>  CD(CM);
    std::vector<NumericType> inputX({1,2,3,4,5,6});
    Cosan::CosanData<NumericType>  CD1(inputX,inputY,"rowfirst");
    std::cout<<CD1.GetInput()<<std::endl;
    NumericType lb=0,ub=1;
    Cosan::CosanData<NumericType> CD2(3,4,lb,ub);
    std::cout<<CD2.GetInput()<<std::endl;
    return 0;
}

