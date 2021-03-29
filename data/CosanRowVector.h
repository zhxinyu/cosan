//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANROWVECTOR_H
#define COSAN_COSANROWVECTOR_H
#include <Eigen/Dense>

namespace Cosan{
    class CosanRowVector : public Eigen::RowVectorXd {
        public:
            CosanRowVector():Eigen::RowVectorXd(){}
    };
}

#endif //COSAN_COSANROWVECTOR_H
