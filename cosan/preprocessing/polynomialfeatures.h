//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_POLYNOMIALFEATURES_H
#define COSAN_POLYNOMIALFEATURES_H
#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    /**
     * Generate polynomial and interaction features. Generate a new feature matrix consisting of all polynomial combinations of the features with degree less than or equal to the specified degree.
     */
    template<Numeric NumericType>
    class PolynomialFeatures: public Preprocessor<NumericType>  {
        public:
            PolynomialFeatures()=delete;
            PolynomialFeatures(CosanRawData<NumericType> &RD, std::vector<std::pair<gsl::index,NumericType>> um,bool add_back = false): Preprocessor<NumericType>(){
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
                if (add_back==true){
                    RD.ConcatenateData(__polynomialFeatures);
                    fmt::print("Notice that CRD.X has been modified. The dimension of X is ({:},{:}). {:} columns of polynomial features have been added.\n",RD.GetrowsX(),RD.GetcolsX(),__polynomialFeatures.cols());
                }
            }
            void SetInteractionFeatures(CosanRawData<NumericType> &RD,std::pair<gsl::index,gsl::index> pair,bool add_back = false){
                fmt::print("*********************************\n");
                fmt::print("Begin generating interaction features between {:d} and {:d}!!\n",pair.first,pair.second);
                decltype(auto) X = RD.GetInput();
                __interactionFeatures.conservativeResize(X.rows(),1);
                __polynomialFeatures.col(0) = X.col(pair.first).array()*X.col(pair.second).array();
                fmt::print("End of generating interaction features. Get access to it via .GetInteractionFeatures()\n",pair.first,pair.second);
                fmt::print("*********************************\n");
                if (add_back==true){
                    RD.ConcatenateData(__interactionFeatures);
                    fmt::print("Notice that CRD.X has been modified. The dimension of X is ({:d},{:d}). {:d} columns of interaction features have been added.\n",RD.GetrowsX(),RD.GetcolsX(),__interactionFeatures.cols());
                }

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
            decltype(auto) GetInteractionFeatures(){return __interactionFeatures;}
            void UpdatePolynomialFeatures(CosanMatrix<NumericType> inputX ){return __polynomialFeatures = inputX;  }
        private:
            CosanMatrix<NumericType> __polynomialFeatures;
            CosanMatrix<NumericType> __interactionFeatures;
    };
}


#endif //COSAN_POLYNOMIALFEATURES_H
