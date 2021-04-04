#ifndef COSAN_NORMALIZER_H
#define COSAN_NORMALIZER_H

#include <cosan/preprocessing/preprocessor.h>
#include <set>
namespace Cosan {
    class Normalizer : public Preprocessor {
    public:
        Normalizer(): Preprocessor() {
            p = 2;
        }
        ~Normalizer() override = default;
        Normalizer(int new_p): Preprocessor(){
            if (plist.find(new_p)==plist.end()){
                throw std::invalid_argument(
                        "Choose p from 1, 2 or std::numeric_limits<int>::max()!"
                        );
            }
            p = new_p;
        }
        CosanMatrix normalize(const CosanMatrix& X){
            return transform(X);
        }
        int Getp() const {return p;}
        void Setp(int new_p) {p=new_p;}
    protected:
        void fit(const CosanMatrix & X) override {}
        CosanMatrix transform(const CosanMatrix &X) override{
            SampleNorm = X.rowwise().template lpNorm<2>();
            switch(p){
                case 1:
                    SampleNorm = X.rowwise().lpNorm<1>();
                    break;
                case std::numeric_limits<int>::max():
                    SampleNorm = X.rowwise().lpNorm<Eigen::Infinity>();
                    break;
                default:
                    SampleNorm = X.rowwise().lpNorm<2>();
            }
            exist_zero = (SampleNorm.array()==0).any();
            return (X.array().colwise())/((SampleNorm.array()==0).cast<double>()+SampleNorm.array());
        }
    private:
        int p;
        bool exist_zero;
        CosanColVector SampleNorm;
        std::set<int> plist = {1,2,std::numeric_limits<int>::max()};
    };

}

#endif //COSAN_NORMALIZER_H