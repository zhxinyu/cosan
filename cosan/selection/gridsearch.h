#ifndef TUNING_H
#define TUNING_H

// TODO: change after integrate with module

// import from Cosan
// TODO #include<> cross validate here
#include<cosan/selection/crossvalidation.h>
#include<cosan/selection/selection.h>
namespace Cosan
{
    /*
        Hyperparameter tuning for supervised models that have one or more hyperparameter(s) to tune
        Input required:
            estimator: class Model&, a model whose hyperparameters need to be tuned;
            metric: class Metric&, a metric to use in cross-validation
            paramGrid: a vector of hyperparameters combination. For each entry of the vector, it corresponds to one choice of hyperparameter combination;
            nthreads: int, the number of threads used. Default is 1.
        Ouput: call .GetBestParams() to get the best hyperparameters combination.
            the choice of the hyper-parameter in paramGrid that forms the most accurate model
    */
    template<typename NumericType,class Model,
            class Metric, class Split,
                    typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class GridSearch: public Selection{
            public:
                GridSearch() = delete;
//                GridSearch(const std::variant<CosanRawData<NumericType>,CosanData<NumericType>> &CRD,
//                           Model & estimator,
//                           Metric & metric,
//                           Split & split,
//                           const std::vector<std::variant<NumericType,std::vector<NumericType>>> & paramGrid): Selection() {
            GridSearch(  CosanData<NumericType> &CRD,
                       Model & estimator,
                       Metric & metric,
                       Split & split,
                       const std::vector<NumericType> & paramGrid): Selection() {
                    NumericType minError = std::numeric_limits<NumericType>::infinity();
                    NumericType currError;
                    decltype(bestParam) currParam;
                    for (gsl::index i = 0; i < paramGrid.size(); ++i){
                        currParam = paramGrid[i];
                        estimator.SetParams(paramGrid[i]);
                        currError = crossValidation(CRD, estimator, metric, split);
                        if (currError < minError)
                        {
                            minError = currError;
                            bestParam = currParam;
                        }
                    }
                }
                auto GetBestParams(){return bestParam;}

            private:
                NumericType bestParam;};
}
#endif