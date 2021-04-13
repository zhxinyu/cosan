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
#include <cosan/evaluation/evaluation.h>
namespace Cosan {
    /*
        Base class for metric function
    */
//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>

    /**
     *  @brief CosanMetric class for metric functionality.
     *  @param[in] yPredict data for prediction
     *  @param[in] yTrue    data for truth
     *  @details Initialize metric class by
     *  @code CosanMetric(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) @endcode
     *  Get the metric error by
     *  @code GetError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) @endcode
     **/
    template<Numeric NumericType>
    class CosanMetric : public Evaluation {
    public:
        // Delete the default constructor.
        CosanMetric() : Evaluation() {}

        /*
            Default constructor
        */
        CosanMetric(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) : Evaluation() {
            setAttr(yPredict, yTrue);
        };

        // returns the error rate
        virtual NumericType
        GetError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) {
            return 0;
        };

        /*
            Set the attributes, if use the default constructor
        */
        void setAttr(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) {
            // check if the input matrices have the same size
            if (!SameSize(yPredict, yTrue)) {
                throw DiffSize;
            }
            // check the shape of the input
            if (!LabelShape(yPredict)) {
                throw InvalidLabelShape;
            }
            GetError(yPredict, yTrue);
        }

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

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value, NumericType>::type>
    /**
     *  @brief Mean absolute error
     *  @details https://scikit-learn.org/stable/modules/model_evaluation.html#mean-absolute-error
     **/
    template<Numeric NumericType>
    class MeanAbsError : public CosanMetric<NumericType> {
    public:
        MeanAbsError() : CosanMetric<NumericType>() {}

        MeanAbsError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue)
                : CosanMetric<NumericType>(yPredict, yTrue) {}

        NumericType
        GetError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) override {
            this->error = (yPredict - yTrue).array().abs().sum() / yPredict.rows();
            return this->error;
        }
    };


    /**
     *  @brief Mean squared error
     *  @details https://scikit-learn.org/stable/modules/model_evaluation.html#mean-squared-error
     **/
    template<Numeric NumericType>
    class MeanSquareError : public CosanMetric<NumericType> {
    public:
        MeanSquareError() : CosanMetric<NumericType>() {}

        MeanSquareError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue)
                : CosanMetric<NumericType>(yPredict, yTrue) {}

        NumericType
        GetError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) override {
            this->error = (yTrue - yPredict).squaredNorm() / yTrue.rows();
            return this->error;
        }
    };


    /**
     *  @brief R2 square
     *  @details https://scikit-learn.org/stable/modules/model_evaluation.html#r2-score-the-coefficient-of-determination
     **/
    template<Numeric NumericType>
    class R2Score : public CosanMetric<NumericType> {
    public:
        R2Score() : CosanMetric<NumericType>() {}

        R2Score(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue)
                : CosanMetric<NumericType>(yPredict, yTrue) {}

        NumericType
        GetError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) override {
            //			yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());
            this->error = 1 - (yTrue - yPredict).squaredNorm() / (yTrue.array() - yTrue.mean()).matrix().squaredNorm();
            return this->error;
        }
    };
    /**
     *  @brief maximum error
     *  @details https://scikit-learn.org/stable/modules/model_evaluation.html#max-error
     **/
    template<Numeric NumericType>
    class MaxError : public CosanMetric<NumericType> {
    public:
        MaxError() : CosanMetric<NumericType>() {}

        MaxError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue)
                : CosanMetric<NumericType>(yPredict, yTrue) {}

        NumericType
        GetError(const CosanMatrix <NumericType> &yPredict, const CosanMatrix <NumericType> &yTrue) override {
//			yTrueMean = Constant(yTrue.rows(), yTrue.cols(). yTrue.mean());
            this->error = (yTrue - yPredict).array().abs().maxCoeff();
            return this->error;
        }
    };

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
//    class LpNormError: public CosanMetric<NumericType>
//    {
//        public:
//            LpNormError()=delete;s
//            LpNormError(NumericType inputp ):CosanMetric<NumericType>(){ p = inputp;}
//            LpNormError(const CosanMatrix<NumericType>& yPredict,const  CosanMatrix<NumericType>& yTrue): CosanMetric<NumericType>(yPredict, yTrue){}
//            NumericType GetError(const CosanMatrix<NumericType>& yPredict,const CosanMatrix<NumericType>& yTrue) override
//            {
//                switch(p){
//                    case (NumericType) 1:
//                        this->error = (yTrue-yPredict).template lpNorm<1>();
//                        break;
//                    case (NumericType) 2:
//                        this->error = (yTrue-yPredict).template lpNorm<2>();
//                        break;
//                    case std::numeric_limits<NumericType>::max():
//                        this->error = (yTrue-yPredict).template lpNorm<Eigen::Infinity>();
//                        break;
//                    default:
//                        this->error = std::pow((yTrue-yPredict).cwiseAbs().array().pow(p).sum(), 1.0/p);
//                }
//                return this->error;
//            }
//            NumericType Getp(){return p;}
//        private:
//            NumericType p;
//    };


}
#endif