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
#include <cosan/utils/ArgCheck.h>
#include <cosan/utils/Exceptions.h>
#include <cosan/data/CosanData.h>

namespace Cosan
{
	/*
		Base class for metric function
	*/
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	class CosanMetric: public CosanBO{
		public:
        // Delete the default constructor.
            CosanMetric(): CosanBO(){}
            // returns the error rate
            virtual NumericType GetError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue)=0;
			/*
				Default constructor 
			*/
			CosanMetric(const CosanMatrix<NumericType>& yPredict, const CosanMatrix<NumericType>& yTrue):CosanBO()
			{
                setAttr(yPredict,yTrue);
			};
            /*
                Set the attributes, if use the default constructor
            */
            void setAttr(CosanMatrix<NumericType> yPredict, CosanMatrix<NumericType> yTrue)
            {
                // check if the input matrices have the same size
                if (!SameSize(yPredict, yTrue))
                {
                    throw DiffSize;
                }
                // check the shape of the input
                if (!LabelShape(yPredict))
                {
                    throw InvalidLabelShape;
                }
                GetError();
            }

        protected:
            NumericType error;
            };


//	/*
//	count the number of errors in a prediction
//	Parameters:
//		yTrue: a refrence to a CosanMatrix object; the real labels
//			   with a shape of (#_of_samples, 1)
//		yPredict: a refrence to a CosanMatrix object; the predicted labels
//				  with a shape of (#_of_samples, 1)
//		threshold: double; threshold for error
//	Output of GetError:
//		result: NumericType; number of mismatch between predicted
//				and real labels
//	*/
//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
//	class NumOfError: public CosanMetric<NumericType>
//	{
//        NumericType Mthreshold;
//
//		public:
//			NumOfError(CosanMatrix<NumericType>& y1, CosanMatrix<NumericType>& y2, NumericType threshold): CosanMetric<NumericType>(y1, y2)
//			{
//				Mthreshold{threshold};
//                error = GetError();
//			}
//
//        NumericType GetError()
//		{
//			return ((yTrue - yPredict) > Mthreshold).count();
//		}
//	};

	
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
        public:
	        MeanAbsError():CosanMetric<NumericType>(){}
            MeanAbsError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue): CosanMetric<NumericType>(yPredict, yTrue){}
            NumericType GetError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue){
                this->error = (yPredict - yTrue).array().abs().sum()/yPredict.rows();
                return this->error ;
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
	    public:
            MeanSquareError():CosanMetric<NumericType>(){}
            MeanSquareError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue): CosanMetric<NumericType>(yPredict, yTrue){}
            NumericType GetError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue){
                this->error =(yTrue - yPredict).squaredNorm()/yTrue.rows();
                return this->error;
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
        public:
            R2Score():CosanMetric<NumericType>(){}
            R2Score(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue): CosanMetric<NumericType>(yPredict, yTrue){}
            NumericType GetError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue){
    //			yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());
                this->error = 1-(yTrue-yPredict).squaredNorm()/(yTrue.array()-yTrue.mean()).matrix().squaredNorm();
                return this->error;
            }
	};

    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class MaxError: public CosanMetric<NumericType>
    {
        public:
            MaxError():CosanMetric<NumericType>(){}
            MaxError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue): CosanMetric<NumericType>(yPredict, yTrue){}
        NumericType GetError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue)
        {
//			yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());
            this->error = (yTrue-yPredict).array().abs().maxCoeff();
            return this->error;
        }
    };

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
//    class LpNormError: public CosanMetric<NumericType>
//    {
//        public:
//            LpNormError()=delete;
//            LpNormError(gsl::index inputp ):CosanMetric<NumericType>(){ p = inputp;}
//            LpNormError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue): CosanMetric<NumericType>(yPredict, yTrue){}
//            NumericType GetError(CosanMatrix<NumericType>& yPredict, CosanMatrix<NumericType>& yTrue)
//            {
//                this->error = (yTrue-yPredict).rowwise().template lpNorm<this->p>();
//                return this->error;
//            }
//            gsl::index Getp(){return p;}
//        private:
//            gsl::index p;
//
//    };

    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    NumericType getVMean(std::vector<NumericType>& v){
        return std::accumulate(v.begin(), v.end(), 0)/v.size();
//        NumericType total = 0;
//        int size = v.size();
//        std::accumulate(v.begin(), v.end(), 0)/v.size();
//
//        for (vector<double>::iterator it = v.begin(); it != v.end(); ++it)
//        {
//            total += *it;
//        }
//
//        return total/size;
    }
}

#endif