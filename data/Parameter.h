//
// Created by Xinyu Zhang on 3/28/21.
//

#ifndef COSAN_PARAMETER_H
#define COSAN_PARAMETER_H
#include <Eigen/Dense>
#include <cosan/data/CosanMatrix.h>
namespace Cosan {
    class Parameter : public CosanMatrix {
    public:
        Parameter() : CosanMatrix() {}
    };
}
#endif //COSAN_PARAMETER_H
