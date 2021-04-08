//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLINEARREGRESSION_H
#define COSAN_COSANLINEARREGRESSION_H
#include <cosan/model/CosanLinearModel.h>
#include <numeric>
namespace Cosan
{
//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    template<Numeric NumericType>
    class CosanLinearRegression: public CosanLinearModel<NumericType> {
        public:
//          Initialization
            CosanLinearRegression(): CosanLinearModel<NumericType>(true){}
            CosanLinearRegression(bool Bias ): CosanLinearModel<NumericType>(Bias){}
            CosanLinearRegression(CosanMatrix<NumericType>& X,const CosanMatrix<NumericType>& Y,bool Bias): CosanLinearModel<NumericType>(Bias){
                fit(X,Y);
            }
//          Load and Save Model
//            virtual bool Load(const string & path);
//            virtual bool Save(const string & path);

//
            virtual EModelType GetModelType() override {
                return MdLinearRegression;
            };
            virtual EProblemType GetProblemType() override {
                return PdUnivariateRegression;}
            virtual const std::string GetName()  const override {
                return "Linear Regression/ Ordinary Least Square";}

            template<class T,
                      std::enable_if_t<std::is_same_v<std::decay_t<T>,CosanMatrix<NumericType>>,bool> =true
                              >
            void fit(T&& X,const CosanMatrix<NumericType>& Y) {
                if (this->MBias==true){
                    X.conservativeResize(X.rows(), X.cols()+1);
                    X.col(X.cols()-1) = CosanMatrix<NumericType>::Ones(X.rows(),1);
                }
                this->MBeta = (X.transpose()*X).ldlt().solve(X.transpose()*Y);
                if (this->MBias==true){
                    removeColumn(X,X.cols()-1);
                }
            }
//            void fit(CosanMatrix<NumericType>&& X,const CosanMatrix<NumericType>& Y) override{
//                if (this->MBias==true){
//                    X.conservativeResize(X.rows(), X.cols()+1);
//                    X.col(X.cols()-1) = CosanMatrix<NumericType>::Ones(X.rows(),1);
//                }
//                this->MBeta = (X.transpose()*X).ldlt().solve(X.transpose()*Y);
//                if (this->MBias==true){
//                    removeColumn(X,X.cols()-1);
//                }
//            }
            virtual CosanMatrix<NumericType> predict(const CosanMatrix<NumericType>& X) override {
                if (this->MBias==true){
//                    std::vector<int> idx(X.cols()-1);
//                    std::iota(std::begin(idx), std::end(idx), 0);

//                    return (X*MBeta.block(0,0,X.cols(),1)).array()+MBeta(X.cols(),0);
                    return (X*this->MBeta(Eigen::seq(0,X.cols()-1),Eigen::all)).array()+this->MBeta(X.cols(),0);
                }
                else{return X*this->MBeta;}
            }

    };
}


#endif //COSAN_COSANLINEARREGRESSION_H
