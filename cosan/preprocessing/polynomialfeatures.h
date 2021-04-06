//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_POLYNOMIALFEATURES_H
#define COSAN_POLYNOMIALFEATURES_H
#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class PolynomialFeatures: public Preprocessor<NumericType>  {
        public:
            PolynomialFeatures()=delete;
            PolynomialFeatures(CosanRawData<NumericType> &RD, std::vector<std::pair<gsl::index,NumericType>> um): Preprocessor<NumericType>(){
                fmt::print("*********************************\n");
                fmt::print("Begin to generating polynomial features!!\n");

                decltype(auto) X = RD.GetInput();
                __polynomialFeatures.conservativeResize(X.rows(),um.size());
//                std::cout<<um.size()<<std::endl;
//                X.conservativeResize(X.rows(),X.cols()+um.size());
                gsl::index i = 0;
                for (const auto & each : um) {
                    if (each.second>=3){
                        fmt::print("Your choice of power {:f} may be too big. High potential of overflow!",each.second);
                    }
                    __polynomialFeatures.col(i) = X.col(each.first).array().pow(each.second);
                    fmt::print("Generating power {:f} of Column {:d}!\n",each.second,each.first);
                    i++;
                }
                fmt::print("Finish generating polynomial features! Use .GetPolynomialFeatures() to get access it.\n");
                fmt::print("*********************************\n");
            }

//            PolynomialFeatures(CosanRawData<NumericType> &RD,
//                               std::vector<std::pair<std::pair<gsl::index,NumericType>,std::pair<gsl::index,NumericType>> > um2): Preprocessor<NumericType>(){
//                fmt::print("*********************************\n");
//                fmt::print("Begin to generating polynomial features!!\n");
//
//                decltype(auto) X = RD.GetInput();
//                __polynomialFeatures.conservativeResize(X.rows(),um2.size());
//                gsl::index i = 0;
//                for (const auto & each: um2) {
//                    if (each.first.second>=3 || each.second.second>=3){
//                        fmt::print("Your choice of power {:f}/{:f} may be too big. High potential of overflow!",each.first.second,each.second.second);
//                    }
//                    __polynomialFeatures.col(i) = X.col(each.first.first).array().pow(each.first.second)*X.col(each.second.first).array().pow(each.second.second);
//                    fmt::print("Generating interactive power: power {:f} of Column {:d} times power {:f} of Column {:d}! \n",each.first.second,each.first.first,each.second.second,each.second.first);
//
//                    i++;
//                }
//                fmt::print("Finish generating polynomial features! Use .GetPolynomialFeatures() to get access it.\n");
//                fmt::print("*********************************\n");
//
//            }

//
//        PolynomialFeatures(CosanRawData<NumericType> &RD, std::vector<std::pair<gsl::index,NumericType>> um1,
//                               std::vector<std::pair<std::pair<gsl::index,NumericType>,std::pair<gsl::index,NumericType>> > um2): Preprocessor<NumericType>(){
//                    fmt::print("*********************************\n");
//                    fmt::print("Begin to generating polynomial features!!\n");
//
//                    decltype(auto) X = RD.GetInput();
//                    __polynomialFeatures.conservativeResize(X.rows(),um1.size()+um2.size());
//                    gsl::index i = 0;
//                    for (const auto & each : um1) {
//                        if (each.second>=3){
//                            fmt::print("Your choice of power {:f} may be too big. High potential of overflow!",each.second);
//                        }
//                        __polynomialFeatures.col(i) = X.col(each.first).array().pow(each.second);
//                        fmt::print("Generating power {:f} of Column {:d}!\n",each.second,each.first);
//                        i++;
//                    }
//                    for (const auto & each: um2) {
//                        if (each.first.second>=3 || each.second.second>=3){
//                            fmt::print("Your choice of power {:f}/{:f} may be too big. High potential of overflow!",each.first.second,each.second.second);
//                        }
//                        __polynomialFeatures.col(i) = X.col(each.first.first).array().pow(each.first.second)*X.col(each.second.first).array().pow(each.second.second);
//                        fmt::print("Generating interactive power: power {:f} of Column {:d} times power {:f} of Column {:d}! \n",each.first.second,each.first.first,each.second.second,each.second.first);
//
//                        i++;
//                    }
//                    fmt::print("Finish generating polynomial features! Use .GetPolynomialFeatures() to get access it.\n");
//                    fmt::print("*********************************\n");
//
//            }
            decltype(auto) GetPolynomialFeatures(){return __polynomialFeatures;}
            void UpdatePolynomialFeatures(CosanMatrix<NumericType> inputX ){return __polynomialFeatures = inputX;  }
        private:
            CosanMatrix<NumericType> __polynomialFeatures;

    };
}


#endif //COSAN_POLYNOMIALFEATURES_H
