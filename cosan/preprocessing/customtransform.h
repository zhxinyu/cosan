//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_CUSTOMTRANSFORM_H
#define COSAN_CUSTOMTRANSFORM_H
#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class CustomerTransform: public Preprocessor<NumericType>  {
        public:
            CustomerTransform()=delete;
            CustomerTransform(CosanRawData<NumericType>& RD,decltype(RD.GetType()) customTransform(decltype(RD.GetType())) ):Preprocessor<NumericType>() {
                fmt::print("*********************************\n");
                fmt::print("Begin to generating customized features!!\n");

                decltype(auto) X = RD.GetInput();
                __customFeatures = customTransform(X);
                fmt::print("*********************************\n");
                fmt::print("End of generating customized features!!\n");

        }
            decltype(auto) GetCustomFeatures(){return __customFeatures;}
        private:
            decltype(auto) __customFeatures;

};
}

#endif //COSAN_CUSTOMTRANSFORM_H
