#ifndef TUNING_H
#define TUNING_H

// TODO: change after integrate with module

// import from other lib
#include<string>
#include<exception>
#include<Eigen/Dense>

// import from Cosan
// TODO #include<> cross validate here
#include<cosan/utils/ArgCheck.h>
#include<cosan/utils/Exception.h>
#include<cosan/utils/CosanMetric.h>

namespace cosan
{
	/*
		Hyperparameter tuning for linear models that 
		only have one hyperparameter
		Input:
			estimator: CosanLinearModel&, a model whose hyperparameters need to tuned
			metric: CosanMetric&, a metric to use in cross-validation 
			paramGrid: CosanMatrix&, a (n, 1) matrix of possible values for a hyperparameter
			nJob: int, the number of threads used. Default is one
		Ouput: 
			the value of the parameter in paramGrid that forms 
			the most accurate model
	*/
	double GridSearch1(
		CosanLinearModel& estimator, 
		CosanMetric& metric, 
		CosanMatrix& paramGrid, 
		CosanMatrix& X,
		CosanMatrix& Y,
		int fold,
		int nJob=1)
	{
		// TODO: implement multi-threading later
		// expect the shape to be (n,1)
		if (!LabelShape(paramGrid))
			throw InvalidLabelShapeException;

		// iterator thru the paramgrid and do cross-validation on each
		// TODO: potential error rows() return non int
		int numOfRows = paramGrid.rows();
		double minError = INFINITY, bestParam = 0.0, curError = 0.0, curParam = 0.0;
		for (int i = 0; i < numOfRows; ++i)
		{
			curParam = paramGrid(i, 1);
			estimator = estimator.setTau(curParam);
			curError = crossValidate(estimator, metric, X, Y, fold);
			if (curError < minError)
			{
				minError = curError;
				bestParam = curParam;
			}			
		}
		return bestParam;
	};


	/*
		Hyperparameter tuning for linear models that 
		only have one hyperparameter
		Input:
			estimator: 
			metric
			paramGrid:
			nJob:
		Ouput: 
			column vector of the combination of hyperparameters that form 
			the most accurate model
	
	CosanMatrix& GridSearchND(
		CosanLinearModel& estimator, 
		CosanMetric& metric, 
		CosanMatrix& paramGrid, 
		int nJob)
	{

	};
	*/


}


#endif