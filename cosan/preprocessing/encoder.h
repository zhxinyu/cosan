#ifndef COSAN_ENCODER_H
#define COSAN_ENCODER_H

#include <cosan/preprocessing/preprocessor.h>
#include <string>

namespace Cosan {
    template<Numeric NumericType>
    class Encoder: public Preprocessor<NumericType> {
//            Encoder() = default;
//
//            Encoder(std::vector<std::unordered_map<std::string, gsl::index>> categories) {
//                this->categories = categories;
//            }
//
//            ~Encoder() = default;
//
//        enum HANDLE_UNKNOWN {
//            IGNORE,
//            ERROR
//        }
//        ;
    public:
        Encoder() = delete;
        Encoder(CosanRawData <NumericType> &RD,bool add_back =false) : Preprocessor<NumericType>() {
            fit(RD);
            if (add_back==true){
                RD.ConcatenateData(CatMatrix);
                fmt::print("Notice that CRD.X has been modified. The dimension of X is ({:},{:}). {:} columns of one-hot encodings have been added.\n",RD.GetrowsX(),RD.GetcolsX(),CatMatrix.cols());
            }
        }
        void fit(CosanRawData <NumericType> &RD) {
            fmt::print("*********************************\n");
            fmt::print("Begin encoding categorical data !\n");

            gsl::index colCat = RD.GetcolCatX().size();
            std::vector <std::string> svaluesX = RD.GetsvaluesX();
            gsl::index totalCol = 0;
            std::vector<std::vector<std::string>> svalues;
            svalues = std::vector < std::vector <
                      std::string >> (colCat, std::vector<std::string>(svaluesX.size() / colCat, ""));
            CosanMatrix <NumericType> OneHotMatrixi;
            for (gsl::index col = 0; col < colCat; col++) {
                std::unordered_map <std::string, gsl::index> categoryToOrdinal{};
                for (gsl::index row = 0; row < svaluesX.size() / colCat; row++) {
                    svalues[col][row] = svaluesX[row * colCat + col];
                    if (categoryToOrdinal.find(svalues[col][row]) == categoryToOrdinal.end()) {
                        categoryToOrdinal.insert({svalues[col][row], categoryToOrdinal.size()});
                    }
                }
                this->categories.push_back(categoryToOrdinal);
                OneHotMatrixi = CosanMatrix<NumericType>::Zero(svaluesX.size() / colCat, categoryToOrdinal.size());
                for (gsl::index row = 0; row < svaluesX.size() / colCat; row++) {
                    OneHotMatrixi(row, categoryToOrdinal[svalues[col][row]]) = 1;
                }
                if (col == 0) {
                    CatMatrix = OneHotMatrixi;
                } else {
                    for (gsl::index i = 0; i < OneHotMatrixi.cols(); i++) {
                        CatMatrix.conservativeResize(CatMatrix.rows(), CatMatrix.cols() + 1);
                        CatMatrix.col(CatMatrix.cols() - 1) = OneHotMatrixi.col(i);
                    }
                }

            }
            fmt::print("Finish encoding categorical data! Get access to the newly-generated additional matrix via .GetCatMatrix()\n");
            fmt::print("*********************************\n");
        }
//            virtual std::vector<int> getEncoding(int colIdx, const std::string &category) = 0;
        CosanMatrix<NumericType> & GetCatMatrix() {return CatMatrix;}
        std::vector <std::unordered_map<std::string, gsl::index>> getCategories() const {
            return this->categories;}
    private:

        std::vector<std::unordered_map<std::string, gsl::index>> categories;
        CosanMatrix<NumericType> CatMatrix;
    };
}


#endif //COSAN_ENCODER_H
