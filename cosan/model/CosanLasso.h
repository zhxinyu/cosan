//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLASSO_H
#define COSAN_COSANLASSO_H
#include <cosan/model/CosanLinearRegression.h>
namespace Cosan{

    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class CosanLasso: public CosanLinearRegression<NumericType> {};
}

#endif //COSAN_COSANLASSO_H
