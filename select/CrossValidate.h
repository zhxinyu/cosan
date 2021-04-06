#ifndef CROSSVALIDATE_H
#define CROSSVALIDATE_H

#include<KFold.h>
#include<cosan/model/AllModels.h>
#include<cosan/utils/CosanMetric.h>

using namespace std;


namespace cosan
{
	/*
		Conduct Cross Validation on a given model 
		Inputs:
			model: CosanModel&, the reference to the model to be validated 
			X: Cosan
	*/
	double CrossValidateScore(
		CosanModel& model, 
		CosanMatrix& X, 
		CosanMatrix& Y, 
		CosanMetric& metric, 
		int fold)
	{
		vector<double> errors;
		trainBatch = KFold(X.rows(), fold).GetSplit();

		for (auto& each:trainBatch)
		{
			auto trainIdx = get<0>(each); auto testIdx = get<1>(each);
			CosanMatrix xTrain = X(trainIdx, Eigen::all); CosanMatrix yTrain = Y(trainIdx, Eigen::all);
			CosanMatrix xTest = X(testIdx, Eigen:all); CosanMatrix yTest = Y(testIdx, Eigen:all);
			model.fit(xTrain, yTrain);
			CosanMatrix yPredict = model.predict(xTest, yTest);

			metric.setAttr(yTest, yPredict,);
			errors.push_back(metric.GetError());
		}

		// GetVMean defined in CosanMetric.h
		return GetVMean(errors);
	};

}

#endif 