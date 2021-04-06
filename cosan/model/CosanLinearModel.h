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
//            CosanLinearModel(bool Bias): CosanModel(){
//                Init();
//                MBias=Bias;
//            };

    //        CosanLinearModel(CosanLinearModel* Model);

        //  Coefficients
            void SetBias(const bool NewBias){MBias = NewBias;}
            virtual void SetBeta(const CosanMatrix& InitBeta){MBeta=InitBeta;}

            CosanMatrix<NumericType>& GetBeta() {return MBeta;}
            bool GetBias() const {return MBias;}


    //        virtual void SetFeatures(InputFeatures* X){MInputX=X;}

            virtual bool fit( CosanMatrix<NumericType>& X ,const CosanMatrix<NumericType>& Y)=0;
            virtual CosanMatrix<NumericType> predict(const CosanMatrix<NumericType>& X )=0;//fixed later
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
