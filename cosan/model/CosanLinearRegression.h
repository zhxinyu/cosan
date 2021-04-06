//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLINEARREGRESSION_H
#define COSAN_COSANLINEARREGRESSION_H
#include <cosan/model/CosanLinearModel.h>
#include <numeric>
//using namespace Eigen::indexing;
namespace Cosan
{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class CosanLinearRegression: public CosanLinearModel<NumericType> {
        public:
//          Initialization
            CosanLinearRegression(): CosanLinearModel<NumericType>(true){}
            CosanLinearRegression(bool Bias ): CosanLinearModel<NumericType>(Bias){}


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
            bool fit(CosanMatrix<NumericType>& X,const CosanMatrix<NumericType>& Y) override{

                if (MBias==true){
                    X.conservativeResize(X.rows(), X.cols()+1);
                    X.col(X.cols()-1) = CosanMatrix<NumericType>::Ones(X.rows(),1);
                }
                MBeta = (X.transpose()*X).ldlt().solve(X.transpose()*Y);
                if (MBias==true){
                    removeColumn(X,X.cols()-1);
                }
                return true;
            }
            virtual CosanMatrix<NumericType> predict(const CosanMatrix<NumericType>& X) override {
                if (MBias==true){
//                    std::vector<int> idx(X.cols()-1);
//                    std::iota(std::begin(idx), std::end(idx), 0);

//                    return (X*MBeta.block(0,0,X.cols(),1)).array()+MBeta(X.cols(),0);
                    return (X*MBeta(Eigen::seq(0,X.cols()-1),Eigen::all)).array()+MBeta(X.cols(),0);
                }
                else{return X*MBeta;}

            }

            };
}


#endif //COSAN_COSANLINEARREGRESSION_H
