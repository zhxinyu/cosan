#ifndef COSAN_METRIC_H
#define COSAN_METRIC_H

// TODO: change after integrate with module
#include<string>
#include<Eigen/Dense>
#include<cosan/data/CosanData.h>

namespace Cosan
{
	/*
	count the number of errors in a prediction
	Input:
		y_true: CosanMatrix; the real labels
		y-predict: CosanMatrix; the predicted labels
	Output:
		result: double; number of mismatch between predicted
				and real labels
	*/
	double error_num(CosanMatrix& y_true, CosanMatrix& y_predict);

	/*
	Mean absolute error
	Input:
		y_true: see in error_num cooments
		y-predict: see in error_num cooments
	Output:
		result: double; refer to 
				https://scikit-learn.org/stable/modules/model_evaluation.html#mean-absolute-error
	*/
	double mabs_error(CosanMatrix& y_true, CosanMatrix& y_predict);

	/*
	Mean squared error
	Input:
		y_true: see in error_num cooments
		y-predict: see in error_num cooments
	Output:
		result: double; refer to
				https://scikit-learn.org/stable/modules/model_evaluation.html#mean-squared-error
	*/
	double mse_mean(CosanMatrix& y_true, CosanMatrix& y_predict);

	/*
	R2 score, computes the coefficient of determination
	Input:
		y_true: see in error_num cooments
		y-predict: see in error_num cooments
	Output:
		result: double; refer to
				https://scikit-learn.org/stable/modules/model_evaluation.html#r2-score-the-coefficient-of-determination
	*/
	double r2_score(CosanMatrix& y_true, CosanMatrix& y_predict);

}

#endif