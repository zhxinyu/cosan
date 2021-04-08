//
// Created by Xinyu Zhang on 4/7/21.
//

#ifndef COSAN_COSANPCRRIDGE_H
#define COSAN_COSANPCRRIDGE_H

#include <cosan/model/CosanPrincipalComponentRegression.h>
#include <cosan/preprocessing/principalcomponentanalysis.h>
#include <numeric>
namespace Cosan
{
    template<typename NumericType= double,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class CosanPCRRidge: public CosanPrincipalComponentRegression<NumericType>  {
        public:
    //          Initialization
            CosanPCRRidge(): CosanPrincipalComponentRegression<NumericType>(){}
            CosanPCRRidge(gsl::index ncomp  ): CosanPrincipalComponentRegression<NumericType>(ncomp){}

            CosanPCRRidge(CosanMatrix<NumericType>& X,const CosanMatrix<NumericType>& Y,std::vector<NumericType> params): CosanPrincipalComponentRegression<NumericType>(false){
                this->__ncomp = params[0];
                MLambda = params[1];
                this->PC = PrincipalComponentAnalysis(X,this->__ncomp).GetPC();
                this->DerivatedCovariate = X*(this->PC);
                CosanMatrix<NumericType> Identity = MLambda*CosanMatrix<NumericType>::Identity((this->PC).cols(),(this->PC).cols());
                this->MBeta = ((this->DerivatedCovariate).transpose()*(this->DerivatedCovariate)+Identity).ldlt().solve((this->DerivatedCovariate).transpose()*Y);
            }

            virtual EModelType GetModelType() override {
                return MdRidgePrincipalComponentRegression;
            };

            virtual EProblemType GetProblemType()  {
                return PdUnivariateRegression;}
            virtual const std::string GetName()  const override {
                return "Principal Component Regression with least square and ridge regularization";}

            template<class T,
                    std::enable_if_t<std::is_same_v<std::decay_t<T>,CosanMatrix<NumericType>>,bool> =true
            >
            void fit(T&& X,const CosanMatrix<NumericType>& Y) {
                this->PC = PrincipalComponentAnalysis(X,this->__ncomp).GetPC();
                this->DerivatedCovariate = X*(this->PC);
                CosanMatrix<NumericType> Identity = MLambda*CosanMatrix<NumericType>::Identity((this->PC).cols(),(this->PC).cols());
                this->MBeta = ((this->DerivatedCovariate).transpose()*(this->DerivatedCovariate)+Identity).ldlt().solve((this->DerivatedCovariate).transpose()*Y);
            }

            CosanMatrix<NumericType> &GetPC() {return this->PC;}
        private:
            NumericType MLambda;
        };
}


#endif //COSAN_COSANPCRRIDGE_H
