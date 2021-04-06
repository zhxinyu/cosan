//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_TRAINTESTSPLIT_H
#define COSAN_TRAINTESTSPLIT_H
#include <random>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cosan/base/CosanBO.h>
#include <cosan/data/CosanData.h>
namespace Cosan{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class TrainTestSplit: public Selection {
        public:
            TrainTestSplit(std::variant<CosanRawData<NumericType>,CosanData<NumericType>>& CRD,double testRatio=0.3){
                if (CRD.GetrowsX()!=CRD.GetrowsY())
                    throw DiffSize;
                static_assert(testRatio>=0 && testRatio<=1,"Input testRatio should be between 0 and 1.");
                split(CRD,testRatio);
            }
            std::tuple<std::vector<int>>
        private:
            void split(std::variant<CosanRawData<NumericType>,CosanData<NumericType>>& CRD,double testRatio){
                nrows = CRD.GetrowsX();
                ntrain = (gsl::index) nrows*(1-testRatio);
                ntest = nrows-ntrain;
                std::iota(idx.begin(), idx.end(), 0);
                std::vector<int> idx(nrows);
                outTrain.resize(ntrain);
                outTest.resize(ntest);
                std::sample(idx.begin(), idx.end(), std::back_inserter(outTrain),
                            ntrain, std::mt19937{std::random_device{}()});
                std::sort(outTrain.begin(),outTrain.end());
                std::set_difference(idx.begin(), idx.end(), outTrain.begin(), outTrain.end(),
                                    std::inserter(outTest, outTest.begin()));
            }
            gsl::index nrows;
            gsl::index ntrain;
            gsl::index ntest ;
            std::vector<int> outTrain,outTest;
    };
}

#endif //COSAN_TRAINTESTSPLIT_H
