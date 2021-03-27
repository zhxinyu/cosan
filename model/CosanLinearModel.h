//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANLINEARMODEL_H
#define COSAN_COSANLINEARMODEL_H
#include <cosan/model/CosanModel.h>
#include <cosan/data/CosanColumnVector.h>

namespace cosan{
    class InputFeatures;
    class OutputValues;
    class OuputUniRegression*
    class OutputBinaryLabels*

    class CosanLinearModel: public CMachine {
    public CosanLinearModel();
    public CosanLinearModel(bool Bias);
    virtual ~CosanLinearModel();
    CosanLinearModel(CosanLinearModel* Model);
    virtual bool train(InputFeatures* X = NULL);

};

}


#endif //COSAN_COSANLINEARMODEL_H
