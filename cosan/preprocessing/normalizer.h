#ifndef COSAN_NORMALIZER_H
#define COSAN_NORMALIZER_H

#include <cosan/preprocessing/preprocessor.h>
#include <set>
namespace Cosan {
    /**
     *
     * Scale input vectors individually to unit norm (vector length).
     */
    template<Numeric NumericType>
    class Normalizer : public Preprocessor<NumericType> {
    public:
        Normalizer(CosanRawData<NumericType>& RD): Preprocessor<NumericType>() {
            p = 2;
            this->fit(RD);
        }
        ~Normalizer() override = default;
        Normalizer(CosanRawData<NumericType>& RD, int new_p): Preprocessor<NumericType>(){
            if (plist.find(new_p)==plist.end()){
                throw std::invalid_argument(
                        "Choose p from 1, 2 or std::numeric_limits<int>::max()!"
                        );
            }
            p = new_p;
            this->fit(RD);
        }
//        CosanMatrix normalize(const CosanMatrix& X){
//            return transform(X);
//        }
        int Getp() const {return p;}
        CosanColVector<NumericType> GetSampleNorm(){return SampleNorm;}
        void Setp(int new_p) {p=new_p;}
    protected:
        void fit(CosanRawData<NumericType> & RD)  {
            RD.UpdateData(transform(RD.GetInput()));
        }
        void fit(const CosanMatrix<NumericType> & X) override { }

        CosanMatrix<NumericType> transform(const CosanMatrix<NumericType> &X) override{
            fmt::print("*********************************\n");
            fmt::print("Begin normalizing data using norm {:d}!\n",p);
//            SampleNorm = X.rowwise().template lpNorm<2>();
            switch(p){
                case 1:
                    SampleNorm = X.rowwise().template lpNorm<1>();
                    break;
                case std::numeric_limits<int>::max():
                    SampleNorm = X.rowwise().template lpNorm<Eigen::Infinity>();
                    break;
                default:
                    SampleNorm = X.rowwise().template lpNorm<2>();
            }
            bool _exist_zero = (SampleNorm.array()==0).any();
            if (_exist_zero==true){
                fmt::print("Caveat: some row has norm-p equals to zero!\n");
            }
            fmt::print("End of normalizing data using norm {:d} One may get norm of each row by GetSampleNorm().\n",p);
            fmt::print("*********************************\n");
            return (X.array().colwise())/((SampleNorm.array()==0).template cast<NumericType>()+SampleNorm.array());
        }
    private:
        int p;
        bool exist_zero;
        CosanColVector<NumericType> SampleNorm;
        std::set<int> plist = {1,2,std::numeric_limits<int>::max()};
    };

}

#endif //COSAN_NORMALIZER_H