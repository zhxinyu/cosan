/*
	Created by Jiahe Chen 
*/

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
		Base class for metric function
	*/
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	class CosanMetric: CoasnBo{
		CosanMatrix<NumericType>& yTrue;
		CosanMatrix<NumericType>& yPredict;
//        CosanMatrix<NumericType> yTrue;
//        CosanMatrix<NumericType> yPredict;
        NumericType error;
		public:
            NumericType GetError() {return error;}
			/*
				Default constructor 
			*/
			CosanMetric(const CosanMatrix<NumericType>& y1, const CosanMatrix<NumericType>& y2)
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


			// Delete the default constructor?
			CosanMetric()=delete;


		// returns the error rate
		virtual NumericType GetError(){}=0;
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
		result: NumericType; number of mismatch between predicted
				and real labels
	*/
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	class NumOfError: public CosanMetric<NumericType>
	{
        NumericType Mthreshold;

		public:
			NumOfError(CosanMatrix<NumericType>& y1, CosanMatrix<NumericType>& y2, NumericType threshold): CosanMetric<NumericType>(y1, y2)
			{
				Mthreshold{threshold};
                error = GetError();
			}

        NumericType GetError()
		{
			return ((yTrue - yPredict) > Mthreshold).count();
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
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	class MeanAbsError: public CosanMetric<NumericType>
	{
		// TODO: might get an error. class ihenritance grammar errors
        public:
            MeanAbsError(CosanMatrix<NumericType>& y1, CosanMatrix<NumericType>& y2): CosanMetric<NumericType>(y1, y2)
            {
                error = GetError();
            }
	    private:
            NumericType GetError()
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
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	class MeanSquareError: public CosanMetric<NumericType>
	{
		// TODO: might get an error. class ihenritance grammar errors
	    public:
            MeanSquareError(CosanMatrix<NumericType>& y1, CosanMatrix<NumericType>& y2): CosanMetric<NumericType>(y1, y2)
                {
                    error = GetError();
                }
        private:
            NumericType GetError()
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
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	class R2Score: public CosanMetric<NumericType>
	{
		// TODO: might get an error. class ihenritance grammar errors
        public:
            R2Score(CosanMatrix<NumericType>& y1, CosanMatrix<NumericType>& y2): CosanMetric<NumericType>(y1, y2)
            {
                error = GetError();
            }
	    private:
            NumericType GetError()
            {
    //			yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());

                return 1-(yTrue-yPredict).squaredNorm()/(yTrue.array()-yTrue.mean()).matrix().squaredNorm();
            }
	};

    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class MaxError: public CosanMetric<NumericType>
    {
        // TODO: might get an error. class ihenritance grammar errors
        public:
            MaxError(CosanMatrix<NumericType>& y1, CosanMatrix<NumericType>& y2): CosanMetric<NumericType>(y1, y2)
            {
                error = GetError();
            }
        NumericType GetError()
        {
//			yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());

            return (yTrue-yPredict).abs().maxcoeff();
        }
    };

	
}

#endif