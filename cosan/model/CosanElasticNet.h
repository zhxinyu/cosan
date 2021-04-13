//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANELASTICNET_H
#define COSAN_COSANELASTICNET_H
#include <cosan/model/CosanLinearRegression.h>

namespace Cosan{
    template<Numeric NumericType>
    class CosanElasticNet: public CosanLinearRegression<NumericType> {

    };
}



#endif //COSAN_COSANELASTICNET_H
