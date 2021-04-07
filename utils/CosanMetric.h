/*
	Created by Jiahe Chen 
*/

#ifndef COSAN_METRIC_H
#define COSAN_METRIC_H

// TODO: change after integrate with module

//import from other libraries
#include<vector>
#include<iterator>

// import from Cosan
#include<ArgCheck.h>
#include<Exception.h>
#include<cosan/data/CosanData.h>

using namespace std;

namespace Cosan
{
	/*
		Base class for metric function
	*/
	class CosanMetric
	{
		CosanMatrix& yTrue(1000, 1);
		CosanMatrix& yPredict(1000, 1);

		public:
			// Destructor
			CosanMetric()=delete;
		 	//Default constructor 
			CosanMetric()=default;
			/*
				constructor with inputs
				Inputs:
					y1: the test labels
					y2: the predicted labels
			*/
			CosanMetric(CosanMatrix& y1, CosanMatrix& y2)
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

				yTrue{y1}; 
				yPredict{y2};
			};

			

			/*
				Set the attributes, if use the default constructor
			*/
			void setAttr(CosanMatrix& y1, CosanMatrix& y2)
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

				yTrue{y1}; 
				yPredict{y2};
			};


			// returns the error rate
			virtual double GetError(){}=0;
	};

	/*
	count the number of errors in a prediction
	Parameters:
		yTrue: a refrence to a CosanMatrix object; the real labels
			   with a shape of (#_of_samples, 1)
		yPredict: a refrence to a CosanMatrix object; the predicted labels
				  with a shape of (#_of_samples, 1)
		threshold: double; threshold for error
	Output of GetError:
		result: double; number of mismatch between predicted
				and real labels
	*/
	class MaxError: public CosanMetric
	{
		// TODO: might get an error. class ihenritance grammar errors

		double GetError()
		{
			return (yTrue - yPredict).maxCoeff();
		}
	};

	
	/*
	Mean absolute error
	Parameters:
		yTrue: see in error_num cooments
		yPredict: see in error_num cooments
	Output of GetError:
		result: double; refer to 
				https://scikit-learn.org/stable/modules/model_evaluation.html#mean-absolute-error
	*/
	class MabsError: public CosanMetric
	{
		// TODO: might get an error. class ihenritance grammar errors

		double GetError()
		{
			return (yTrue - yPredict).abs().sum()/yTrue.rows();
		}
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
	class MseMeanError: public CosanMetric
	{
		// TODO: might get an error. class ihenritance grammar errors

		double GetError()
		{
			return (yTrue - yPredict).squaredNorm()/yTrue.rows();
		}
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
	class R2Score: public CosanMetric
	{
		// TODO: might get an error. class ihenritance grammar errors

		double GetError()
		{
			yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());

			return 1-(yTrue-yPredict).squaredNorm()/(yTrue-yTrueMean).squaredNorm();
		}
	};

	/*
		calculate the mean value of elements in a vector<double>
		Input:
			v: reference to a vector<double>

		Output: 
			result: double
	*/
	double getVMean(vector<double>& v)
	{
		double total = 0.0;
		int size = v.size();
		for (vector<double>::iterator it = v.begin(); it != v.end(); ++it)
		{
			total += *it;
		}

		return total/size; 
	}	
}

#endif