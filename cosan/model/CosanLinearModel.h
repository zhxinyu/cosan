//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLINEARMODEL_H
#define COSAN_COSANLINEARMODEL_H
#include <cosan/model/CosanModel.h>
#include <cosan/data/CosanData.h>

namespace Cosan{
    /**
     * @brief CosanLinear Model. All linear model inherit this object.
     * @details To initialize model object, one can do
     * @code model(); // The default constructor where the model is without intercept. @endcode
     * @code model(bool bias); @endcode
     * @code model(NumericType param, bool bias);//for model with only one parameter. Ridge regression and PCR are the cases. @endcode
     * @code model(std::vector<NumericType> params, bool bias);//for model with more than one parameter. Each parameter is the enry of params. PCR with L2 square norm is the case. @endcode
     * To initialize model object and run model fitting automatically, one can do
     * @code model(CosanRawData<NumericType> RD,NumericType param ,bool bias = false);  @endcode
     * @code model(CosanData<NumericType> CD,NumericType param ,bool bias = false); @endcode
     * @code model(CosanMatrix<NumericType> X,CosanMatrix<NumericType> Y,NumericType param,bool bias = false); @endcode
     * For model with more than 1 parameter, one should replace `NumericType param` by `std::vector<NumericType> params`.
     * @code model.fit(CosanMatrix<NumericType> X,CosanMatrix<NumericType> Y); @endcode
     * @code model.predict(CosanMatrix<NumericType> X); @endcode
     * To set new params and get current params, one can do
     * @code model.SetParams(NumericType param); //for model with more than 1 parameter, input should be std::vecotr<NumericType> params @endcode
     * @code model.GetParams(); @endcode
     * To obtain the coefficient for the model one can use
     * @code  model.GetBeta(); @endcode
     **/
    template<Numeric NumericType>
    class CosanLinearModel: public CosanModel {
    //  Initialization
        public:
            CosanLinearModel()=delete;
            CosanLinearModel(bool Bias): CosanModel(){
                Init();
                MBias=Bias;
            }
        //  Coefficients
            void SetBias(const bool NewBias){MBias = NewBias;}
            virtual void SetBeta(CosanMatrix<NumericType> InitBeta){MBeta=InitBeta;}

            const CosanMatrix<NumericType>& GetBeta() const {return MBeta;}
            bool GetBias() const {return MBias;}
    //        virtual void SetFeatures(InputFeatures* X){MInputX=X;}

//            template<class T,
//                     std::enable_if_t<std::is_same_v<std::decay_t<T>,std::vector<NumericType>>,bool> =true>
//            virtual void fit( T && X , CosanMatrix<NumericType>& Y){}

            virtual CosanMatrix<NumericType> predict(const CosanMatrix<NumericType>& X )=0;
        //  Utils
            virtual const std::string  GetName() const {return "LinearModel";}
            protected:
                CosanMatrix<NumericType> MBeta;
                bool MBias;
            private:
                void Init(){
            }
        };

}

#endif //COSAN_COSANLINEARMODEL_H
