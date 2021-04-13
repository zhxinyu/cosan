//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_MINMAXSCALER_H
#define COSAN_MINMAXSCALER_H

#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    template<Numeric NumericType>
    class MinmaxScaler: public Preprocessor<NumericType>  {
        public:
            MinmaxScaler()=delete;
            MinmaxScaler(CosanRawData<NumericType>& RD):Preprocessor<NumericType>(){
                this->fit(RD);
            }
            MinmaxScaler(CosanRawData<NumericType>& RD,NumericType to_lb,NumericType to_ub):Preprocessor<NumericType>(){
                this->fit(RD,to_lb,to_ub);
            }

        private:
            void fit(CosanRawData<NumericType> & RD){
                fmt::print("*********************************\n");
                fmt::print("Begin transformation X to [0,1]!\n");
                CosanMatrix<NumericType> X = RD.GetInput();
                X = (X.array().rowwise()-X.colwise().minCoeff().array()).rowwise()/(X.colwise().maxCoeff()-X.colwise().minCoeff()).array();
                RD.UpdateData(X);
                fmt::print("End of transformation X to [0,1]\n");
                fmt::print("*********************************\n");
            }
            void fit(CosanRawData<NumericType> & RD, NumericType to_lb,NumericType to_ub){
                fmt::print("*********************************\n");
                fmt::print("Begin transformation to X to [{:},{:}]!\n",to_lb,to_ub);
                CosanMatrix<NumericType> X = RD.GetInput();
                X = (X.array().rowwise()-X.colwise().minCoeff().array()).rowwise()/(X.colwise().maxCoeff()-X.colwise().minCoeff()).array();
                X = X.array()*(to_ub-to_lb)+to_lb;
                RD.UpdateData(X);
                fmt::print("End of transformation to X to [{:},{:}]!\n",to_lb,to_ub);
                fmt::print("*********************************\n");
            }
    };
}


#endif //COSAN_MINMAXSCALER_H
