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

    /** principal component regression with L2 square penaly term on coefficient beta.
     * @tparam NumericType
     * @details https://en.wikipedia.org/wiki/Principal_component_regression
     */
    template<Numeric NumericType>
    class CosanPCRRidge: public CosanPrincipalComponentRegression<NumericType>  {
        public:
    //          Initialization
            CosanPCRRidge(): CosanPrincipalComponentRegression<NumericType>(){}
            CosanPCRRidge(std::vector<NumericType> params,bool bias=false  ): CosanPrincipalComponentRegression<NumericType>(params[0]){
                MLambda = params[1];}

            CosanPCRRidge(CosanRawData<NumericType>& RD,std::vector<NumericType> params ,bool bias = false ): CosanPrincipalComponentRegression<NumericType>(params[0]){
                    MLambda = params[1];
                    fit(RD.GetInput(),RD.GetTarget());
                }
            CosanPCRRidge(CosanData<NumericType>& CD,std::vector<NumericType> params ,bool bias = false ): CosanPrincipalComponentRegression<NumericType>(params[0]){
                    MLambda = params[1];
                    fit(CD.GetInput(),CD.GetTarget());
                }
            template<class T,
                std::enable_if_t<std::is_same_v<std::decay_t<T>,CosanMatrix<NumericType>>,bool> = true >
            CosanPCRRidge(T&& X,const CosanMatrix<NumericType>& Y,std::vector<NumericType> params,bool bias = false): CosanPrincipalComponentRegression<NumericType>(params[0]){
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
            void SetParams(std::vector<NumericType> params) {
                this->__ncomp = params[0];
                MLambda = params[1]; };
            NumericType GetParams() {return {this->__ncomp ,MLambda};}
            CosanMatrix<NumericType> &GetPC() {return this->PC;}
        private:
            NumericType MLambda;
        };
}


#endif //COSAN_COSANPCRRIDGE_H
