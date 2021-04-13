//
// Created by Xinyu Zhang on 4/6/21.
//

#ifndef COSAN_STATISTICS_H
#define COSAN_STATISTICS_H
#include <cosan/evaluation.h>
//template<Numeric NumericType>
namespace Cosan{
    /**
     *  @brief Class for statistics results
     *  @details calculate SampleCovariance, mean, variance, median, maxNum, minNum;
     *  @code CosanMatrix<NumericType> & GetSampleCovariance(const CosanMatrix<NumericType> & X) @endcode
     *  @code NumericType GetMean(const CosanMatrix<NumericType> & X) @endcode
     *  @code NumericType GetVar(const CosanMatrix<NumericType> & X) @endcode
     *  @code NumericType GetMedian(const CosanMatrix<NumericType> & X) @endcode
     *  @code NumericType GetMax(const CosanMatrix<NumericType> & X) @endcode
     *  @code NumericType GetMin(const CosanMatrix<NumericType> & X) @endcode
     **/
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
            NumericType GetMean(const CosanMatrix<NumericType> & X){
                if (X.rows()>1 && X.cols()>1){
                    fmt::print("Mean is not defined in matrix! Calculate the mean of all entries!");
                }
                mean = X.mean();
                return mean;
            }
            NumericType GetVar(const CosanMatrix<NumericType> & X){
                if (X.rows()>1 && X.cols()>1){
                    fmt::print("Variance is not defined in matrix! Calculate the variance of all entries!");
                }
                variance = std::sqrt((X.array() - X.mean()).square().sum()/(X.size()-1));
                return variance;
            }

            NumericType GetMedian(const CosanMatrix<NumericType> & X){
                if (X.rows()>1 && X.cols()>1){
                    fmt::print("Median is not defined in matrix! Calculate the median of all entries!");
                }
                std::vector<NumericType> X_copy(X.data(),X.data()+X.size());
                if(X_copy.size()%2==0){
                    std::nth_element(X_copy.data(), X_copy.data() + X_copy.size()/2, X_copy.data()+X_copy.size());
                    std::nth_element(X_copy.data(), X_copy.data() + X_copy.size()/2-1, X_copy.data()+X_copy.size());
                    median = (*(X_copy.data()+X_copy.size()/2)+*(X_copy.data()+X_copy.size()/2-1))/2;
                }
                else{
                    std::nth_element(X_copy.data(), X_copy.data() + (X_copy.size()-1)/2, X_copy.data()+X_copy.size());
                    median = *(X_copy.data() + (X_copy.size()-1)/2);
                }
                return median;
            }

            NumericType GetMax(const CosanMatrix<NumericType> & X){
                if (X.rows()>1 && X.cols()>1){
                    fmt::print("Variance is not defined in matrix! Calculate the minimum of all entries!");
                }
                maxNum = X.maxCoeff();
                return maxNum;
            }
            NumericType GetMin(const CosanMatrix<NumericType> & X){
                if (X.rows()>1 && X.cols()>1){
                    fmt::print("Variance is not defined in matrix! Calculate the minimum of all entries!");
                }
                minNum = X.minCoeff();
                return minNum;
            }

        CosanMatrix<NumericType> SampleCovariance;
        NumericType mean;
        NumericType variance;
        NumericType median;
        NumericType maxNum;
        NumericType minNum;
    };

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    /**
     * @brief Calculate the mean of std::vector<NumericType>
     * @tparam NumericType
     * @param v
     * @return NumericType
     */
    template<Numeric NumericType>
    NumericType getVMean(const std::vector<NumericType>& v){
        return std::accumulate(v.begin(), v.end(), 0)/v.size();
//        NumericType total = 0;
//        int size = v.size();
//        std::accumulate(v.begin(), v.end(), 0)/v.size();
//
//        for (vector<double>::iterator it = v.begin(); it != v.end(); ++it)
//        {
//            total += *it;
//        }
//
//        return total/size;
    }
}

}

#endif //COSAN_STATISTICS_H
