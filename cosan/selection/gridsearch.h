#ifndef TUNING_H
#define TUNING_H

// TODO: change after integrate with module

// import from Cosan
// TODO #include<> cross validate here
#include<cosan/selection/crossvalidation.h>
#include<cosan/selection/selection.h>
namespace Cosan
{
    /**
     * Hyperparameter tuning for supervised models that have one or more hyperparameter(s) to tune
     * Input required:
     * estimator: class Model&, a model whose hyperparameters need to be tuned;
     * metric: class Metric&, a metric to use in cross-validation
     * split: Split &  splitter method;*
     * paramGrid: a vector of hyperparameters combination. For each entry of the vector, it corresponds to one choice of hyperparameter combination;
     * Ouput: call .GetBestParams() to get the best hyperparameters combination.
     * the choice of the hyper-parameter in paramGrid that forms the most accurate model
    **/
    template<Numeric NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split>
    class GridSearch: public Search{
            public:
                GridSearch() = delete;
                GridSearch(  CosanData<NumericType> &CRD,
                           Model & estimator,
                           Metric & metric,
                           Split & split,
                           const std::vector<NumericType> & paramGrid): Search() {
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

    /**
     * @details parallel version for grid search
     * Hyperparameter tuning for supervised models that have one or more hyperparameter(s) to tune
     * Input required:
     * estimator: class Model&, a model whose hyperparameters need to be tuned;
     * metric: class Metric&, a metric to use in cross-validation
     * split: Split &  splitter method;*
     * paramGrid: a vector of hyperparameters combination. For each entry of the vector, it corresponds to one choice of hyperparameter combination;
     * nthreads: int. number of threads to be used for parallel computing.
     * Ouput: call .GetBestParams() to get the best hyperparameters combination.
     * the choice of the hyper-parameter in paramGrid that forms the most accurate model
    **/
    template<Numeric NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split>
    class GridSearchParallel: public Search{
    public:
        GridSearchParallel() = delete;
//                GridSearch(const std::variant<CosanRawData<NumericType>,CosanData<NumericType>> &CRD,
//                           Model & estimator,
//                           Metric & metric,
//                           Split & split,
//                           const std::vector<std::variant<NumericType,std::vector<NumericType>>> & paramGrid): Selection() {
        GridSearchParallel(  CosanData<NumericType> &CRD,
                     Model & estimator,
                     Metric & metric,
                     Split & split,
                     const std::vector<NumericType> & paramGrid, int nthreads = -1): Search() {
            NumericType minError = std::numeric_limits<NumericType>::infinity();
            std::vector<NumericType> allError(paramGrid.size());
            if (nthreads == -1){
                omp_set_num_threads(omp_get_max_threads());
            }
            else{
                omp_set_num_threads(nthreads);
            }
            #pragma omp parallel for
            for (gsl::index i = 0; i < paramGrid.size(); ++i){
                estimator.SetParams(paramGrid[i]);
                allError[i] = crossValidation(CRD, estimator, metric, split);
            }
            bestParam =paramGrid[std::distance(allError.begin(), std::min_element(allError.begin(), allError.end()))];
        }
        auto GetBestParams(){return bestParam;}

    private:
        NumericType bestParam;};


//    template<typename NumericType,
//            Derived<CosanModel> Model,
//            Derived<CosanMetric<NumericType>> Metric,
//            Derived<Splitter> Split,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    template<Numeric NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split>
    class GridSearchMulti: public Search{
    public:
        GridSearchMulti() = delete;
//                GridSearch(const std::variant<CosanRawData<NumericType>,CosanData<NumericType>> &CRD,
//                           Model & estimator,
//                           Metric & metric,
//                           Split & split,
//                           const std::vector<std::variant<NumericType,std::vector<NumericType>>> & paramGrid): Selection() {
        GridSearchMulti(  CosanData<NumericType> &CRD,
                     Model & estimator,
                     Metric & metric,
                     Split & split,
                     const std::vector<std::vector<NumericType>> & paramGrid): Search() {
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
        std::vector<NumericType> bestParam;};

//    template<typename NumericType,
//            Derived<CosanModel> Model,
//            Derived<CosanMetric<NumericType>> Metric,
//            Derived<Splitter> Split,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    template<Numeric NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split>
    class GridSearchMultiParallel: public Search{
    public:
        GridSearchMultiParallel() = delete;
//                GridSearch(const std::variant<CosanRawData<NumericType>,CosanData<NumericType>> &CRD,
//                           Model & estimator,
//                           Metric & metric,
//                           Split & split,
//                           const std::vector<std::variant<NumericType,std::vector<NumericType>>> & paramGrid): Selection() {
        GridSearchMultiParallel(  CosanData<NumericType> &CRD,
                          Model & estimator,
                          Metric & metric,
                          Split & split,
                          const std::vector<std::vector<NumericType>> & paramGrid,
                          int nthreads = -1): Search() {
            NumericType minError = std::numeric_limits<NumericType>::infinity();
            std::vector<NumericType> allError(paramGrid.size());
            if (nthreads == -1){
                omp_set_num_threads(omp_get_max_threads());
            }
            else{
                omp_set_num_threads(nthreads);
            }
            #pragma omp parallel for
            for (gsl::index i = 0; i < paramGrid.size(); ++i){
                estimator.SetParams(paramGrid[i]);
                allError[i] = crossValidation(CRD, estimator, metric, split);
            }
            bestParam =paramGrid[std::distance(allError.begin(), std::min_element(allError.begin(), allError.end()))];
        }
        auto GetBestParams(){return bestParam;}

    private:
        std::vector<NumericType> bestParam;};

}
#endif