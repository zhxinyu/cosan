#ifndef COSAN_METRIC_H
#define COSAN_METRIC_H

// TODO: change after integrate with module

// import from other lib
#include<string>
#include<exception>
#include<Eigen/Dense>

// import from Cosan
#include<ArgCheck.h>
#include<Exception.h>
#include<cosan/data/CosanData.h>

namespace Cosan
{
	/*
	count the number of errors in a prediction
	Input:
		yTrue: a refrence to a CosanMatrix object; the real labels
			   with a shape of (#_of_samples, 1)
		yPredict: a refrence to a CosanMatrix object; the predicted labels
				  with a shape of (#_of_samples, 1)
		threshold: double; threshold for error
	Output:
		result: double; number of mismatch between predicted
				and real labels
	*/
	double NumOfError(CosanMatrix& yTrue, CosanMatrix& yPredict, double threshold)
	{
		// check if the input matrices have the same size
		if (!SameSize(yTrue, yPredict))
		{
			throw DiffSize;
		}

		// check the shape of the input
		if (!LabelShape(yTrue))
		{
			throw InvalidLabelShape;
		}

		// TODO: type check if the input type gets expanded

		return ((yTrue - yPredict) > threshold).count();
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
	double MabsError(CosanMatrix& yTrue, CosanMatrix& yPredict)
	{
		// check if the input matrices have the same size
		if (!SameSize(yTrue, yPredict)){
			throw DiffSize;
		}

		// check the shape of the input
		if (!LabelShape(yTrue))
		{
			throw InvalidLabelShape;
		}

		// TODO: type check if the input type gets expanded

		return (yTrue - yPredict).abs().sum()/yTrue.rows()
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
	double MseMeanError(CosanMatrix& yTrue, CosanMatrix& yPredict)
	{
		// check if the input matrices have the same size
		if (!SameSize(yTrue, yPredict)){
			throw DiffSize;
		}

		// check the shape of the input
		if (!LabelShape(yTrue))
		{
			throw InvalidLabelShape;
		}

		// TODO: type check if the input type gets expanded

		return (yTrue - yPredict).squaredNorm()/yTrue.rows();
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
	double R2Score(CosanMatrix& yTrue, CosanMatrix& yPredict)
	{
		// check if the input matrices have the same size
		if (!SameSize(yTrue, yPredict)){
			throw DiffSize;
		}

		// check the shape of the input
		if (!LabelShape(yTrue))
		{
			throw InvalidLabelShape;
		}

		// TODO: type check if the input type gets expanded

		yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());

		return 1-(yTrue-yPredict).squaredNorm()/(yTrue-yTrueMean).squaredNorm();
	};

}

#endif