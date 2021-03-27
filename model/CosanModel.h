//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANMODEL_H
#define COSAN_COSANMODEL_H
#include "base/CosanBO.h"
namespace cosan{

    class InputFeatures;
    class OutputValues;

    enum EModelType{
        md_None = 0,
        md_LinearRegression=1,
        md_RidgeRegression=2,
        md_KernelRegression=3
    };
    enum ESolverType{
        sr_Auto = 0
    };
    enum EProblemType{
        pm_Binary = 0,
        pm_UniRegression=1,
//        pm_MultiClassification=2,
//        pm_MultiRegression=3
    };

    class CosanModel: public CosanBO{
    public:
        CosanModel();
        virtual ~CosanModel();
        virtual bool fit(InputFeatures* X = NULL,OutputValues* y = NULL);
        virtual OutputValues* predict(InputFeatures* X = NULL);//fixed later

        virtual OutputBinaryLabels* predict(InputFeatures* X = NULL);
        virtual OuputUniRegression* predict(InputFeatures* X = NULL);

        void SetMaxTrainTime(double t);
        double GetMaxTrainTime();

        virtual EModelType GetModelType();
        void SetSolverType(ESolverType sr);
        ESolverType GetSolverType();
    protect:
        double MaxTrainTime;
        OutputValues* = y;
        ESolverType SolverType;
    };

}

#endif //COSAN_COSANMODEL_H
