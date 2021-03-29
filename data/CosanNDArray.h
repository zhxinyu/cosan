//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANNDARRAY_H
#define COSAN_COSANNDARRAY_H
#include <Eigen/Dense>

namespace Cosan{
    class CosanNDArray : public Eigen::ArrayXXd {
        public:
            CosanNDArray():Eigen::ArrayXXd(){}
    };
}
#endif //COSAN_COSANNDARRAY_H
