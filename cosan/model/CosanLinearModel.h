//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLINEARMODEL_H
#define COSAN_COSANLINEARMODEL_H
#include <cosan/model/CosanModel.h>
#include <cosan/data/CosanData.h>

namespace Cosan{
//    class Parameter;
//    class Feature;
//    class Response;
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
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
