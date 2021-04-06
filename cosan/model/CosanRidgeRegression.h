//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANRIDGEREGRESSION_H
#define COSAN_COSANRIDGEREGRESSION_H
#include <cosan/model/CosanLinearRegression.h>

namespace Cosan{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class CosanRidgeRegression: public CosanLinearRegression<NumericType>{
        public:
//        Initialization
            CosanRidgeRegression()=delete;
            CosanRidgeRegression(NumericType Lambda):CosanLinearRegression<NumericType>(true){
                MLambda=Lambda;
            }
            CosanRidgeRegression(NumericType Lambda,bool Bias): CosanLinearRegression<NumericType>(Bias){
                MLambda=Lambda;
            }
            inline void SetTau(NumericType Lambda) {MLambda = Lambda; };
            double GetTau() {NumericType MLambda;}
//            bool Load(const string & path);
//            bool Save(const string & path);
            EModelType GetModelType() override {return MdRidgeRegression;};
            const std::string  GetName()  const override{ return "Linear Ridge Regression";}



            bool fit(CosanMatrix<NumericType> X,const CosanMatrix<NumericType>& Y)  {
                CosanMatrix Identity = MLambda*CosanMatrix<NumericType>::Identity(X.cols(),X.cols());
                if (MBias==true){
                    X.conservativeResize(X.rows(), X.cols()+1);
                    X.col(X.cols()-1) = CosanMatrix<NumericType>::Ones(X.rows(),1);
                    Identity.conservativeResize(Identity.rows()+1, Identity.cols()+1);
                    Identity.col(Identity.cols()-1) = CosanMatrix<NumericType>::Zero(Identity.rows(),1);
                    Identity.row(Identity.rows()-1) = CosanMatrix<NumericType>::Zero(1,Identity.cols());
                }
//                const auto& svd = X.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV);
//                const auto& s = svd.singularValues();
//                const auto r = s.rows();
//                const auto& D = s.cwiseQuotient((s.array().square() + MLambda).matrix()).asDiagonal();
//                MBeta = svd.matrixV().leftCols(r) * D * svd.matrixU().transpose().topRows(r) * Y;
                MBeta = (X.transpose()*X+Identity).ldlt().solve(X.transpose()*Y);
//                MBeta = (X.transpose()*X+CosanMatrix(MLambda*Eigen::MatrixXd::Identity(X.cols(),X.cols()))).bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(X.transpose()*Y);
//                MBeta = (X.transpose()*X+CosanMatrix(MLambda*Eigen::MatrixXd::Identity(X.cols(),X.cols()))).colPivHouseholderQr().solve(X.transpose()*Y);
                if (MBias==true){
                    removeColumn(X,X.cols()-1);
                }
                return true;
            }

        private:
            double MLambda;


    };
}

#endif //COSAN_COSANRIDGEREGRESSION_H
