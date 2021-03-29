//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANCOLUMNVECTOR_H
#define COSAN_COSANCOLUMNVECTOR_H
#include <Eigen/Dense>

using namespace Cosan{
class CosanColumnVector: public Eigen::VectorXd {
    public:
        CosanColumnVector():Eigen::VectorXd(){}
};
}

#endif //COSAN_COSANCOLUMNVECTOR_H
