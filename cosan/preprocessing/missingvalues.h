//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_MISSINGVALUES_H
#define COSAN_MISSINGVALUES_H


#include <cosan/preprocessing/preprocessor.h>

namespace Cosan{
    template<Numeric NumericType>
    class MissingValues: public Preprocessor<NumericType>  {
        public:
            MissingValues()=delete;
            MissingValues(CosanRawData<NumericType>& RD):Preprocessor<NumericType>(){
                this->fit(RD);
            }

        private:
            void fit(CosanRawData<NumericType> & RD){
                fmt::print("*********************************\n");
                fmt::print("Begin cleaning up missing data!\n");
                std::set<gsl::index> MissingIdxX;
                for (auto & each: RD.GetIdxmissingX()){
                    MissingIdxX.insert(RD.GetRawToNumIdx()[each[1]]);
                }
                bool HasMissingIdxY = RD.GetIdxmissingY().size()==0 ? false :true;
                CosanMatrix<NumericType> X = RD.GetInput();

                for (auto &i : MissingIdxX ){
                    gsl::index _numofMissing = X.col(i).array().isNaN().template cast<NumericType>().sum();
                    fmt::print("For X Column {:d} has {:d} missing value(s).\n",i,_numofMissing);
                    NumericType mean = X.col(i).unaryExpr([](NumericType v) { return std::isnan(v)? 0 : v; }).sum()/(X.rows()-_numofMissing);
                    fmt::print("Fill the missing/nan entry with the column mean={:f}.\n",mean);
                    X.col(i) = X.col(i).array().isNaN().select(0,X.col(i)).array()+mean*(X.col(i).array().isNaN().template cast<NumericType>());

                }
                if (HasMissingIdxY==true){
                    gsl::index i = 0;
                    CosanMatrix<NumericType> Y = RD.GetTarget();
                    gsl::index _numofMissing = Y.col(i).array().isNaN().template cast<NumericType>().sum();
                    fmt::print("For Y has {:d} missing value(s).\n",_numofMissing);

                    NumericType mean = Y.col(i).unaryExpr([](NumericType v) { return std::isnan(v)? 0 : v; }).sum()/(Y.rows()-_numofMissing);
                    fmt::print("Fill the missing/nan entry with the column mean={:f}.\n",mean);
                    Y.col(i) = Y.col(i).array().isNaN().select(0,Y.col(i)).array()+mean*(Y.col(i).array().isNaN().template cast<NumericType>());
                    RD.UpdateData(X,Y);
                }
                else{
                    RD.UpdateData(X);
                }
                fmt::print("End of cleaning process\n");
                fmt::print("*********************************\n");
            }

    };






}


#endif //COSAN_MISSINGVALUES_H
