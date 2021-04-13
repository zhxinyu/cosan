//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_CUSTOMTRANSFORM_H
#define COSAN_CUSTOMTRANSFORM_H
#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    template<Numeric NumericType>
    class CustomTransform: public Preprocessor<NumericType>  {
        public:
            CustomTransform()=delete;
            CustomTransform(CosanRawData<NumericType>& RD,std::vector<NumericType> newInput):Preprocessor<NumericType>() {
                if (newInput.size()!= RD.GetrowsX()){
                    throw std::invalid_argument(
                            fmt::format("newInput does not have the same number of row as RD.X. newInput size is {:d} and RD.X has rows {:d}",newInput.size(),RD.GetrowsX() ));
                }
                fmt::print("*********************************\n");
                fmt::print("Begin to generating customized features!!\n");

//                decltype(auto) X = RD.GetInput();
//                __customFeatures = customTransform(X);
                __customFeatures = Eigen::Map<const CosanMatrix<NumericType>>(newInput.data(), RD.GetrowsX(), 1);
                fmt::print("End of generating customized features. One may get access to the new features via .GetCustomFeatures()!\n");
                fmt::print("*********************************\n");
                RD.ConcatenateData(__customFeatures);
                fmt::print("Notice that CRD.X has been modified. The dimension of X is ({:},{:}). {:} columns of new features have been added.\n",RD.GetrowsX(),RD.GetcolsX(),__customFeatures.cols());
        }
            decltype(auto) GetCustomFeatures(){return __customFeatures;}
        private:
            CosanMatrix<NumericType> __customFeatures;
};
}

#endif //COSAN_CUSTOMTRANSFORM_H
