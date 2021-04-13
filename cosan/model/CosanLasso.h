//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLASSO_H
#define COSAN_COSANLASSO_H
#include <cosan/model/CosanLinearRegression.h>
namespace Cosan{

    template<Numeric NumericType>
    class CosanLasso: public CosanLinearRegression<NumericType> {};
}

#endif //COSAN_COSANLASSO_H
