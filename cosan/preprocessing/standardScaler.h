#ifndef COSAN_STANDARDSCALER_H
#define COSAN_STANDARDSCALER_H

#include <cosan/preprocessing/preprocessor.h>

namespace Cosan {
    class StandardScaler : public Preprocessor {
    public:
        StandardScaler() = default;
        ~StandardScaler() override = default;
        CosanMatrix standardize(const  CosanMatrix& X){
            this->fit(X);
            return this->transform(X);
        };
        CosanRowVector GetMean() const {return this->mean;}
        CosanRowVector GetStd() const {return this->std;}

        void fit(const CosanMatrix & X) override {
            this->mean = X.colwise().mean();
            this->std = ((X.rowwise() - this->mean).array().pow(2).colwise().sum() / X.rows()).sqrt();
            if ((this->std.array()==0).any()==true){
                std::cout<<"Error!"<<std::endl;
                for (gsl::index  idx = 0;idx<this->std.size();idx++ ){
                    if (this->std[idx]==0){
                        std::cout<<"Column "<<idx<<" has identical values!"<<std::endl;
                    }
                }
                throw std::invalid_argument(
                        "Check your column! Some column has identical values!"
                );
            }
        };
        CosanMatrix transform(const CosanMatrix & X) override{
            return (X.rowwise() - this->mean).array().rowwise() / this->std.array();
        };

        CosanMatrix InvTransform(const CosanMatrix & X) {
            return (X.array().rowwise()*(this->std.array())).array().rowwise()+this->mean.array();
        };
    private:
        CosanRowVector mean;
        CosanRowVector std;
    };
}


#endif //COSAN_STANDARDSCALER_H