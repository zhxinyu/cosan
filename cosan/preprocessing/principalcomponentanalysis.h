//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_PRINCIPALCOMPONENTANALYSIS_H
#define COSAN_PRINCIPALCOMPONENTANALYSIS_H
#include <numeric>
#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    class PrincipalComponentAnalysis: public Preprocessor<NumericType>  {
        public:
            PrincipalComponentAnalysis()=delete;
            PrincipalComponentAnalysis(CosanRawData<NumericType>& RD,gsl::index ncom = 3):Preprocessor<NumericType>(){
                ncom = std::min(ncom,RD.GetcolsX());
                this->fit(RD,ncom);
            }
            CosanMatrix<NumericType> GetPC(){return PrincipalComponent;}
        private:
            CosanMatrix<NumericType> PrincipalComponent;
            void fit(CosanRawData<NumericType>& RD,gsl::index ncom){
                fmt::print("*********************************\n");
                fmt::print("Begin PCA on Input Data X. Select the first {:} principal components\n",ncom);
                CosanMatrix<NumericType> X = RD.GetInput();
                CosanMatrix<NumericType> centered = X.rowwise() - X.colwise().mean();
                CosanMatrix<NumericType> cov = centered.adjoint() * centered;

                Eigen::SelfAdjointEigenSolver<CosanMatrix<NumericType>> eigensolver(cov);
                if (eigensolver.info() != Eigen::Success) {
                    throw std::invalid_argument("Cannot solve eigenvalue decomposition.");}

                std::vector<NumericType> vec(eigensolver.eigenvalues().data(), eigensolver.eigenvalues().data() + eigensolver.eigenvalues().size());
                std::reverse(vec.begin(),vec.end());
                std::vector<NumericType> runningSum(vec.size());
                std::partial_sum(vec.begin(), vec.end(), runningSum.begin(), std::plus<NumericType>());
                for (gsl::index i =0;i<runningSum.size();i++){
                    fmt::print("The first {:} principal components explains {:f}% of the total variance.\n",i,runningSum[i]/runningSum.back()*100);
                    if (runningSum[i]/runningSum.back()>0.98 and i>=8){
                        break;
                    }
                }
//                std::cout<<eigensolver.eigenvalues()<<std::endl;
//                std::cout<<eigensolver.eigenvectors()<<std::endl;
//                std::cout<<eigensolver.eigenvectors().rightCols(1)<<std::endl;
                fmt::print("Finsh PCA on Input Data X. The first {:} principal components explains {:f}% of the total variance.\n",ncom,runningSum[ncom]/runningSum.back()*100);
                fmt::print("Uer .GetPC() function to get the principal components.\n" );
                fmt::print("*********************************\n");
                PrincipalComponent = eigensolver.eigenvectors().rightCols(ncom);
            }


    };
}




#endif //COSAN_PRINCIPALCOMPONENTANALYSIS_H
