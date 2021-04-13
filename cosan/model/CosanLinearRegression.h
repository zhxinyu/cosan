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
    /**
     * y = a+bx
     * minimize \sum_{i=1}^n (y_i-a-b^T x_i)^2 -> find the optimal a and b
     * @tparam NumericType
     * @details https://en.wikipedia.org/wiki/Linear_regression
     */
    template<Numeric NumericType>
    class CosanLinearRegression: public CosanLinearModel<NumericType> {
        public:
//          Initialization
            CosanLinearRegression(): CosanLinearModel<NumericType>(false){}
            CosanLinearRegression(bool Bias ): CosanLinearModel<NumericType>(Bias){}

            template<class T,
                std::enable_if_t<std::is_same_v<std::decay_t<T>,CosanMatrix<NumericType>>,bool> =true>
            CosanLinearRegression(T&& X,const CosanMatrix<NumericType>& Y,bool Bias): CosanLinearModel<NumericType>(Bias){
                fit(X,Y);
            }

            CosanLinearRegression(CosanRawData<NumericType>& RD,bool Bias): CosanLinearModel<NumericType>(Bias){
                fit(RD.GetInput(),RD.GetTarget());
            }
            CosanLinearRegression(CosanData<NumericType>& CD,bool Bias): CosanLinearModel<NumericType>(Bias){
                    fit(CD.GetInput(),CD.GetTarget());
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
