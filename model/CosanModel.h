//
// Created by Xinyu Zhang on 3/27/21.
//

#ifndef COSAN_COSANMODEL_H
#define COSAN_COSANMODEL_H
#include <chrono>
#include <cosan/base/CosanBO.h>
namespace Cosan{
    enum EProblemType{
        PdNone   = 0,
        PdBinaryClassification = 1,
        PdUnivariateRegression=2,
    };
    enum EModelType{
        MdNone = 0,
        MdLinearRegression=1,
        MdRidgeRegression=2,
        MdKernelRegression=3
    };
    enum ESolverType{
        SrAuto = 0
    };
    class CosanModel: public CosanBO {
    public:
        CosanModel(): CosanBO(),MaxTrainTime(std::chrono::seconds(std::chrono::hours(1)).count()),
        SolverType(SrAuto){
        }
//        virtual ~CosanModel();
//        virtual Response* predict(const Feature* X = NULL)=0;//fixed later

        void SetMaxTrainTime(double t) { MaxTrainTime=t;}
        double GetMaxTrainTime() const {return MaxTrainTime;}

        virtual EModelType GetModelType() {return MdNone;}
        virtual EProblemType GetProblemType(){return PdNone;}
        virtual ESolverType GetSolverType() const {return SolverType;}
        void SetSolverType(ESolverType sr) {SolverType=sr;}
    protected:
        double MaxTrainTime;
        ESolverType SolverType;
    };
}

#endif //COSAN_COSANMODEL_H
