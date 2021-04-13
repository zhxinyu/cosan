#ifndef COSAN_STANDARDSCALER_H
#define COSAN_STANDARDSCALER_H

#include <cosan/preprocessing/preprocessor.h>

namespace Cosan {
    /**
     * Standardize features by removing the mean and scaling to unit variance
     */
    template<Numeric NumericType>
    class StandardScaler : public Preprocessor<NumericType> {
    public:
        StandardScaler() = default;
//        ~StandardScaler() override = default;
//        CosanMatrix standardize(const  CosanMatrix& X): Preprocessor(){
//            this->fit(X);
//            return this->transform(X);
//        };
        StandardScaler(CosanRawData<NumericType>& RD):Preprocessor<NumericType>(){
            this->fit(RD);
        }
        CosanRowVector<NumericType> GetMean() const {return this->mean;}
        CosanRowVector<NumericType> GetStd() const {return this->std;}
        void fit(CosanRawData<NumericType>& RD){
            fit(RD.GetInput());
            RD.UpdateData(transform(RD.GetInput()));
        }
        void fit(const CosanMatrix<NumericType> & X)  override {
            fmt::print("*********************************\n");
            fmt::print("Begin standardizing data \n");
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

            fmt::print("End of standardizing data. One may transform or reverse-transform by .transform(),.InvTransform() function. \n");
            fmt::print("*********************************\n");
        };
        CosanMatrix<NumericType> transform(const CosanMatrix<NumericType> & X) override{
            return (X.rowwise() - this->mean).array().rowwise() / this->std.array();
        };

        CosanMatrix<NumericType> InvTransform(const CosanMatrix<NumericType> & X) {
            return (X.array().rowwise()*(this->std.array())).array().rowwise()+this->mean.array();
        };
    private:
        CosanRowVector<NumericType> mean;
        CosanRowVector<NumericType> std;
    };
}
#endif //COSAN_STANDARDSCALER_H