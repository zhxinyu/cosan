#ifndef COSAN_METRIC_H
#define COSAN_METRIC_H

// TODO: change after integrate with module
#include<string>
#include<ArgCheck.h>
#include<Exception.h>
#include<Eigen/Dense>
#include<cosan/data/CosanData.h>

namespace Cosan
{
	/*
	count the number of errors in a prediction
	Input:
		yTrue: a refrence to a CosanMatrix object; the real labels
		yPredict: a refrence to a CosanMatrix object; the predicted labels
		threshold: double; threshold for error
	Output:
		result: double; number of mismatch between predicted
				and real labels
	*/
	double NumOfError(CosanMatrix& yTrue, CosanMatrix& yPredict, double threshold)
	{
		if 
	};

	/*
	Mean absolute error
	Input:
		yTrue: see in error_num cooments
		yPredict: see in error_num cooments
	Output:
		result: double; refer to 
				https://scikit-learn.org/stable/modules/model_evaluation.html#mean-absolute-error
	*/
	double MabsError(CosanMatrix& yTrue, CosanMatrix& yPredict){

	};

	/*
	Mean squared error
	Input:
		yTrue: see in error_num cooments
		yPredict: see in error_num cooments
	Output:
		result: double; refer to
				https://scikit-learn.org/stable/modules/model_evaluation.html#mean-squared-error
	*/
	double MseMeanError(CosanMatrix& yTrue, CosanMatrix& yPredict){

	};

	/*
	R2 score, computes the coefficient of determination
	Input:
		yTrue: see in error_num cooments
		yPredict: see in error_num cooments
	Output:
		result: double; refer to
				https://scikit-learn.org/stable/modules/model_evaluation.html#r2-score-the-coefficient-of-determination
	*/
	double R2Score(CosanMatrix& yTrue, CosanMatrix& yPredict){

	};

}

#endif