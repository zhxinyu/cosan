//
// Created by Xinyu Zhang on 4/7/21.
//

#ifndef COSAN_COSANPRINCIPALCOMPONENTREGRESSION_H
#define COSAN_COSANPRINCIPALCOMPONENTREGRESSION_H

#include <cosan/model/CosanLinearModel.h>
#include <cosan/preprocessing/principalcomponentanalysis.h>
#include <numeric>
namespace Cosan
{
//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    /**
     * @tparam NumericType
     * @details https://en.wikipedia.org/wiki/Principal_component_regression
     */
    template<Numeric NumericType>
    class CosanPrincipalComponentRegression: public CosanLinearModel<NumericType> {
    public:
//          Initialization

        CosanPrincipalComponentRegression(): CosanLinearModel<NumericType>(false){
            __ncomp = 3;}
        CosanPrincipalComponentRegression(NumericType ncomp ,bool bias = false): CosanLinearModel<NumericType>(false){
            __ncomp = ncomp;}
        CosanPrincipalComponentRegression(CosanRawData<NumericType>& RD,NumericType ncomp ,bool bias = false): CosanLinearModel<NumericType>(bias=false){
                __ncomp = ncomp;
                fit(RD.GetInput(),RD.GetTarget());
        }
        CosanPrincipalComponentRegression(CosanData<NumericType>& CD,NumericType ncomp,bool bias = false ): CosanLinearModel<NumericType>(bias=false){
                __ncomp = ncomp;
                fit(CD.GetInput(),CD.GetTarget());
        }

        template<class T,
                std::enable_if_t<std::is_same_v<std::decay_t<T>,CosanMatrix<NumericType>>,bool> = true >
        CosanPrincipalComponentRegression(T&& X,const CosanMatrix<NumericType>& Y,NumericType ncomp,bool bias = false): CosanLinearModel<NumericType>(false){
            __ncomp = ncomp;
            PC = PrincipalComponentAnalysis(X,(gsl::index) ncomp).GetPC();
            DerivatedCovariate = X*PC;
            this->MBeta = (DerivatedCovariate.transpose()*DerivatedCovariate).ldlt().solve(DerivatedCovariate.transpose()*Y);
        }

        virtual EModelType GetModelType() override {
            return MdPrincipalComponentRegression;
        };

        virtual EProblemType GetProblemType()  {
            return PdUnivariateRegression;}
        virtual const std::string GetName()  const override {
            return "Principal Component Regression with least square";}

        template<class T,
                std::enable_if_t<std::is_same_v<std::decay_t<T>,CosanMatrix<NumericType>>,bool> =true>
        void fit(T&& X,const CosanMatrix<NumericType>& Y) {
            PC = PrincipalComponentAnalysis(X,__ncomp).GetPC();
            DerivatedCovariate = X*PC;
            this->MBeta = (DerivatedCovariate.transpose()*DerivatedCovariate).ldlt().solve(DerivatedCovariate.transpose()*Y);
            }

        virtual CosanMatrix<NumericType> predict(const CosanMatrix<NumericType>& X) override {
            return X*PC*(this->MBeta);
        }
        CosanMatrix<NumericType> &GetPC() {return PC;}

        void SetParams(NumericType ncomp) {__ncomp = ncomp; };
        NumericType GetParams() {return __ncomp;}

    protected:
        NumericType __ncomp ;
        CosanMatrix<NumericType> PC;
        CosanMatrix<NumericType> DerivatedCovariate;
    };
}



#endif //COSAN_COSANPRINCIPALCOMPONENTREGRESSION_H
