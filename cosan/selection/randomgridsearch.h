//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_RANDOMGRIDSEARCH_H
#define COSAN_RANDOMGRIDSEARCH_H

#include<cosan/selection/crossvalidation.h>
#include<cosan/selection/selection.h>
namespace Cosan{
    template<typename NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class RandomGridSearch: public Search{
    public:
        RandomGridSearch() = delete;
        RandomGridSearch(CosanData<NumericType> &CRD,
                         Model & estimator,
                         Metric & metric,
                         Split & split,
                         const std::vector<NumericType> & paramGrid,long unsigned int nsamples= 100): Search() {
            NumericType minError = std::numeric_limits<NumericType>::infinity();

            NumericType currError;
            std::vector<NumericType> RandomChoice;
            std::sample(paramGrid.begin(), paramGrid.end(), std::back_inserter(RandomChoice),
                        std::min({paramGrid.size(),nsamples}), std::mt19937{std::random_device{}()});

            decltype(bestParam) currParam;
            for (gsl::index i = 0; i < RandomChoice.size(); ++i){
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


    template<typename NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class RandomGridSearchParallel: public Search{
    public:
        RandomGridSearchParallel() = delete;
        RandomGridSearchParallel(CosanData<NumericType> &CRD,
                         Model & estimator,
                         Metric & metric,
                         Split & split,
                         const std::vector<NumericType> & paramGrid,long unsigned int nsamples = 100,int nthreads = -1): Search() {
            NumericType minError = std::numeric_limits<NumericType>::infinity();

            NumericType currError;
            std::vector<NumericType> RandomChoice;
            std::sample(paramGrid.begin(), paramGrid.end(), std::back_inserter(RandomChoice),
                        std::min({paramGrid.size(),nsamples}), std::mt19937{std::random_device{}()});

            std::vector<NumericType> allError(RandomChoice.size());
            if (nthreads == -1){
                omp_set_num_threads(omp_get_max_threads());
            }
            else{
                omp_set_num_threads(nthreads);
            }
            #pragma omp parallel for
            for (gsl::index i = 0; i < RandomChoice.size(); ++i){
                estimator.SetParams(RandomChoice[i]);
                allError[i] = crossValidation(CRD, estimator, metric, split);
            }
            bestParam =RandomChoice[std::distance(allError.begin(), std::min_element(allError.begin(), allError.end()))];

            }
        auto GetBestParams(){return bestParam;}

    private:
        NumericType bestParam;};


    template<typename NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class RandomGridSearchMulti: public Search{
    public:
        RandomGridSearchMulti() = delete;
        RandomGridSearchMulti(  CosanData<NumericType> &CRD,
                          Model & estimator,
                          Metric & metric,
                          Split & split,
                          const std::vector<std::vector<NumericType>> & paramGrid,
                          long unsigned int nsamples = 100): Search() {
            NumericType minError = std::numeric_limits<NumericType>::infinity();
            NumericType currError;
            std::vector<std::vector<NumericType>> RandomChoice;
            std::sample(paramGrid.begin(), paramGrid.end(), std::back_inserter(RandomChoice),
                        std::min({paramGrid.size(),nsamples}), std::mt19937{std::random_device{}()});

            decltype(bestParam) currParam;

            for (gsl::index i = 0; i < RandomChoice.size(); ++i){
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


    template<typename NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class RandomGridSearchMultiParallel: public Search{
    public:
        RandomGridSearchMultiParallel() = delete;
        RandomGridSearchMultiParallel(  CosanData<NumericType> &CRD,
                                Model & estimator,
                                Metric & metric,
                                Split & split,
                                const std::vector<std::vector<NumericType>> & paramGrid,
                                long unsigned int nsamples = 100,int nthreads = -1): Search() {
            NumericType minError = std::numeric_limits<NumericType>::infinity();
            NumericType currError;
            std::vector<NumericType> RandomChoice;
            std::sample(paramGrid.begin(), paramGrid.end(), std::back_inserter(RandomChoice),
                        std::min({paramGrid.size(),nsamples}), std::mt19937{std::random_device{}()});
            std::vector<std::vector<NumericType>> allError(paramGrid.size());
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
#endif //COSAN_RANDOMGRIDSEARCH_H
