//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLINEARREGRESSION_H
#define COSAN_COSANLINEARREGRESSION_H
#include <cosan/model/CosanLinearModel.h>

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
            virtual EModelType GetModelType(){
                return MdLinearRegression;
            };
            virtual EProblemType GetProblemType(){
                return PdUnivariateRegression;}
            virtual const std::string GetName() const{
                return "Linear Regression/ Ordinary Least Square";}

            virtual bool fit(CosanMatrix& X,const CosanMatrix& Y){

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
            virtual CosanMatrix predict(const CosanMatrix& X){
                return X*MBeta;
            }

            };
}


#endif //COSAN_COSANLINEARREGRESSION_H
