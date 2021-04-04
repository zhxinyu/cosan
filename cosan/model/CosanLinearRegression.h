//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLINEARREGRESSION_H
#define COSAN_COSANLINEARREGRESSION_H
#include <cosan/model/CosanLinearModel.h>
#include <Eigen/Core>
#include <numeric>
namespace Cosan
{
    class CosanLinearRegression: public CosanLinearModel {
        public:
//          Initialization
            CosanLinearRegression(): CosanLinearModel(true){}
            CosanLinearRegression(bool Bias ): CosanLinearModel(Bias){}


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
            bool fit(CosanMatrix& X,const CosanMatrix& Y) override{

                if (MBias==true){
                    X.conservativeResize(X.rows(), X.cols()+1);
                    X.col(X.cols()-1) = Eigen::MatrixXd::Ones(X.rows(),1);
                }
                MBeta = (X.transpose()*X).ldlt().solve(X.transpose()*Y);
                if (MBias==true){
                    removeColumn(X,X.cols()-1);
                }
                return true;
            }
            virtual CosanMatrix predict(const CosanMatrix& X) override {
                if (MBias==true){
//                    std::vector<int> idx(X.cols()-1);
//                    std::iota(std::begin(idx), std::end(idx), 0);

                    return (X*MBeta.block(0,0,X.cols(),1)).array()+MBeta(X.cols(),0);
                }
                else{return X*MBeta;}

            }

            };
}


#endif //COSAN_COSANLINEARREGRESSION_H
