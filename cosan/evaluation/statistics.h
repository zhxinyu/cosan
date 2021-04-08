//
// Created by Xinyu Zhang on 4/6/21.
//

#ifndef COSAN_STATISTICS_H
#define COSAN_STATISTICS_H
#include <cosan/evaluation.evaluation.h>
template<Numeric NumericType>
namespace Cosan{
    template<Numeric NumericType>
    class SummaryStatistics: public Evaluation {
        public:
            SummaryStatistics():Evaluation(){}
            CosanMatrix<NumericType> & GetSampleCovariance(const CosanMatrix<NumericType> & X):{
                if (X.rows()<=1){
                    fmt::print("Input must have more than 1 row!")
                    throw SmallRows;
                }
                CosanMatrix<NumericType> centered = X.rowwise() - X.colwise().mean();
                SampleCovariance = (centered.adjoint() * centered) / double(X.rows() - 1);
                return SampleCovariance}

            CosanMatrix<NumericType> SampleCovariance;

    };
}

#endif //COSAN_STATISTICS_H
