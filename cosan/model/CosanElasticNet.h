//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANELASTICNET_H
#define COSAN_COSANELASTICNET_H
#include <cosan/model/CosanLinearRegression.h>

namespace Cosan{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class CosanElasticNet: public CosanLinearRegression<NumericType> {

    };
}



#endif //COSAN_COSANELASTICNET_H
