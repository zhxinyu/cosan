#ifndef CROSSVALIDATE_H
#define CROSSVALIDATE_H
//#include<cosan/selection/KFold.h>
//#include<cosan/model/AllModels.h>
//#include<cosan/utils/CosanMetric.h>
#include <variant>
#include <vector>
#include<cosan/selection/selection.h>
namespace Cosan
{
	/*
		Conduct Cross Validation on a given model 
		Inputs:
			model: CosanModel&, the reference to the model to be validated;
	        metric: from CosanMetric class;
	        CRD: const std::variant<CosanRawData<NumericType>;
	        split: from splittor class.
//	*/
//    NumericType crossValidation(const std::variant<CosanRawData<NumericType>,CosanData<NumericType>> &CRD,
//                                Model& estimator,
//                                Metric & metric,
//                                Split & split){
//		template<typename NumericType,
//                 Derived<CosanModel> Model,
//                 Derived<CosanMetric<NumericType>> Metric,
//                 Derived<Splitter> Split,
//                 typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type >
        template<Numeric NumericType,
                Derived<CosanModel> Model,
                Derived<CosanMetric<NumericType>> Metric,
                Derived<Splitter> Split>
        NumericType crossValidation(CosanData<NumericType> &CRD,
                                    Model& estimator,
                                    Metric & metric,
                                    Split & split){
            split.SetSplit(CRD.GetrowsX());
            CosanMatrix<NumericType> X = CRD.GetInput();
            CosanMatrix<NumericType> Y = CRD.GetTarget();
            std::vector<NumericType> errors;
            errors.resize(split.GetKFoldNumber());
            std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_idx = split.GetSplit();
//            #pragma omp parallel for
            for (gsl::index i =0;i<split.GetKFoldNumber();i++){
                    auto & each = split_idx[i];
                    CosanMatrix<NumericType>  X_train = X(std::get<0>(each),Eigen::all),Y_train = Y(std::get<0>(each),Eigen::all);
                    CosanMatrix<NumericType>  X_test =  X(std::get<1>(each),Eigen::all),Y_test =  Y(std::get<1>(each),Eigen::all);
                    estimator.fit(X_train, Y_train);
                    errors[i] = metric.GetError(estimator.predict(X_test ),Y_test);
                }
			return std::accumulate(errors.begin(), errors.end(), 0)/errors.size();
	};

//    template<typename NumericType,
//            Derived<CosanModel> Model,
//            Derived<CosanMetric<NumericType>> Metric,
//            Derived<Splitter> Split,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type >
    template<Numeric NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split>
    NumericType crossValidationParallel(CosanData<NumericType> &CRD,
                                Model& estimator,
                                Metric & metric,
                                Split & split, int nthreads = -1){
        split.SetSplit(CRD.GetrowsX());
        CosanMatrix<NumericType> X = CRD.GetInput();
        CosanMatrix<NumericType> Y = CRD.GetTarget();
        std::vector<NumericType> errors;
        errors.resize(split.GetKFoldNumber());
        std::vector< std::tuple<std::vector<gsl::index>,std::vector<gsl::index> > > split_idx = split.GetSplit();
        if (nthreads == -1){
            omp_set_num_threads(omp_get_max_threads());
        }
        else{
            omp_set_num_threads(nthreads);
        }
        #pragma omp parallel for
        for (gsl::index i =0;i<split.GetKFoldNumber();i++){
            auto & each = split_idx[i];
            CosanMatrix<NumericType>  X_train = X(std::get<0>(each),Eigen::all),Y_train = Y(std::get<0>(each),Eigen::all);
            CosanMatrix<NumericType>  X_test =  X(std::get<1>(each),Eigen::all),Y_test =  Y(std::get<1>(each),Eigen::all);
            estimator.fit(X_train, Y_train);
            errors[i] = metric.GetError(estimator.predict(X_test ),Y_test);
        }
        return std::accumulate(errors.begin(), errors.end(), 0)/errors.size();
    };


}

#endif 