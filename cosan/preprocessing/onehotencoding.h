//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_ONEHOTENCODING_H
#define COSAN_ONEHOTENCODING_H

#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class OnehotEncoding: public Preprocessor<NumericType>  {


    };
}


#endif //COSAN_ONEHOTENCODING_H
