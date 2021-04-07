#ifndef CROSSVALIDATE_H
#define CROSSVALIDATE_H
//#include<cosan/selection/KFold.h>
//#include<cosan/model/AllModels.h>
//#include<cosan/utils/CosanMetric.h>
#include <variant>
#include <vector>
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
		template<typename NumericType,typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type,class Model,class Metric, class Split>
        NumericType crossValidation(  CosanData<NumericType> &CRD,
                                    Model& estimator,
                                    Metric & metric,
                                    Split & split){
            CosanMatrix<NumericType>  X =  CRD.GetInput();
            CosanMatrix<NumericType> Y =  CRD.GetTarget();
            split.SetSplit(CRD.GetrowsX());
            std::vector<NumericType> errors;
            for (auto& each:split.GetSplit())
                {
                    estimator.fit(X(std::get<0>(each),Eigen::all), Y(std::get<0>(each),Eigen::all));
//                    metric.setAttr();
                    errors.push_back(metric.GetError(estimator.predict(X(std::get<1>(each),Eigen::all) ),Y(std::get<1>(each),Eigen::all)));
                }
			// GetVMean defined in CosanMetric.h
			return std::accumulate(errors.begin(), errors.end(), 0)/errors.size();
	};
}

#endif 