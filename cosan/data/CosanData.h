#ifndef __COSANData_H_INCLUDED__
#define __COSANData_H_INCLUDED__
#include <string>
#include <Eigen/Dense>
#include <cosan/io/utils.h>
#include <cosan/base/CosanBO.h>
#include <tuple>
namespace Cosan
{
//    MISSING VALUES, STRING, NUMERICAL

    class CosanMatrix: public Eigen::MatrixXd{
    public:
        CosanMatrix(): Eigen::MatrixXd(){}
        template<typename OtherDerived>
        CosanMatrix(const Eigen::MatrixBase<OtherDerived> &other): Eigen::MatrixXd(other){}

        template<typename OtherDerived>
        CosanMatrix & operator=(const Eigen::MatrixBase <OtherDerived>& other){
            this->Eigen::MatrixXd::operator=(other);
            return *this;
        }

    } ;
    class CosanRawData: public CosanBO{
        public:
            CosanRawData()=delete;
            CosanRawData(const std::string & srcX):CosanBO(){
                SetInput(srcX);
            }
            CosanRawData(const std::string & srcX,
                      const std::string & srcY):CosanBO(){
                SetInput(srcX);
                SetTarget(srcY);
            }
            //        virtual ~CosanBO();
            void SetInput(const std::string & srcX){
                std::tie(rowsX,colsX,SummaryMessageX) = _load_csv<Eigen::MatrixXd>(srcX,X,IdxpinfX,IdxminfX,IdxmissingX,svaluesX,colCatX);
            }

            void SetTarget(const std::string & srcY){
                std::tie(rowsY,colsY,SummaryMessageY) = _load_csv<Eigen::MatrixXd>(srcY,Y,IdxpinfY,IdxminfY,IdxmissingY,svaluesY,colCatY);
                if (colCatY.size()!=0){
                    catY=true;
                }
            }
            CosanMatrix & GetInput(){
                return X;
            }
            const CosanMatrix & GetTarget() const{
                return Y;
            }

            //        virtual CosanBO *Shallow_copy() const;
            //        virtual CosanBO *Deep_copy() const;

            virtual const std::string  GetName() const {return "Raw Data Object.";}

            //        virtual bool SaveFile(const std::string &path ,const std::string & prefix = "");
            //        virtual bool LoadFile(const std::string &path);
            //        void PrintModel();
            //        virtual bool Equals(CosanBO* other, float accuracy = 0.0);
            //        virtual CosanBO* Clone();
            virtual const std::string  GetSummaryMessageX() const {return SummaryMessageX;}
            virtual const std::string  GetSummaryMessageY() const {return SummaryMessageY;}
        protected:
                CosanMatrix X;
                CosanMatrix Y;
                std::string SummaryMessageX,SummaryMessageY;
                std::vector<std::vector<uint>> IdxpinfX,IdxminfX,IdxmissingX;
                std::vector<std::vector<uint>> IdxpinfY,IdxminfY,IdxmissingY;
                std::set<uint> colCatX,colCatY;
                bool catY = false;
                uint rowsX = 0,colsX = 0;
                uint rowsY = 0,colsY = 0;
                std::vector<std::string> svaluesX,svaluesY;
        private:
            template<typename Matrix>
            std::tuple<uint,uint,std::string> _load_csv (const std::string & path,CosanMatrix& X,std::vector<std::vector<uint>>& Idxpinf,
                                                         std::vector<std::vector<uint>>& Idxminf,std::vector<std::vector<uint>>& Idxmissing,
                                                         std::vector<std::string> &svalues, std::set<uint> & colCat) {

                std::ifstream indata;
                indata.open(path);
                std::string line;
                std::vector<double> values;
                //    std::vector<std::string> svalues;
                uint rows = 0,cols = 0,col_idx=0;
                //    uint col_idx=0;
                //    std::vector<std::vector<uint>> Idxpinf,Idxminf,Idxmissing;
                //    std::set<uint> colCat;
                double result;
                std::size_t pos;
                std::string SummaryMessage;
                /**
                 *  Get the first line information
                 */

                std::getline(indata, line);
                std::stringstream lineStream(line);
                std::string cell;
                while(getline(lineStream, cell, ',')) {
                    if (cell.size()==0){
                        values.push_back(stod(std::string("nan")));
                        Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
                        col_idx++;
                        cols=std::max(cols,col_idx);
                        continue;
                    }
                    try{
                        result = std::stod(cell, &pos);
                    }catch(...){
                        svalues.push_back(cell);
                        colCat.insert(col_idx);
                        col_idx++;
                        cols=std::max(cols,col_idx);
                        continue;
                    }
                    if (pos!=cell.size()){
                        throw std::invalid_argument(
                                "Incorrect numeric format! Abort the program. The entry reads "+cell+
                                " and the position is ("+ std::to_string(rows)+","+ std::to_string(col_idx)+")");
                    }
                    values.push_back(result);
                    if (isinf(values.back())){
                        if (values.back()==std::numeric_limits<double>::infinity()){
                            Idxpinf.push_back(std::vector<uint>({rows,col_idx}));}
                        else {Idxminf.push_back(std::vector<uint>({rows,col_idx}));}
                    }
                    else if (isnan(values.back())){
                        Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
                    }
                    col_idx++;
                    cols=std::max(cols,col_idx);
                }
                rows = 1;
                col_idx = 0;


                while (std::getline(indata, line)) {
                //        std::stringstream lineStream(line);
                //        std::string cell;
                    lineStream.str("");
                    lineStream.clear(); // Clear state flags.
                    lineStream<<line;
                    while(getline(lineStream, cell, ',')) {
                        if (cell.size()==0){
                            if (colCat.find(col_idx)==colCat.end()){
                                values.push_back(stod(std::string("nan")));
                            }
                            else{
                                svalues.push_back("");
                            }
                            Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
                            col_idx++;
                            continue;
                        }
                        try{
                            result = std::stod(cell, &pos);
                        }catch(...){
                            if (colCat.find(col_idx)!=colCat.end())
                            {
                                svalues.push_back(cell);
                                colCat.insert(col_idx);
                                col_idx++;
                                continue;}
                            else{
                                throw std::invalid_argument(
                                        "Incorrect value type! Should be numeric but non-numeric input. The entry reads "+cell+
                                        " and the position is ("+ std::to_string(rows)+","+ std::to_string(col_idx)+")");
                            }
                        }
                        if (pos!=cell.size()){
                            throw std::invalid_argument(
                                    "Incorrect numeric format! Abort the program. The entry reads "+cell+
                                    " and the position is ("+ std::to_string(rows)+","+ std::to_string(col_idx)+")");
                        }
                        values.push_back(result);
                        if (isinf(values.back())){
                            if (values.back()==std::numeric_limits<double>::infinity()){
                                Idxpinf.push_back(std::vector<uint>({rows,col_idx}));}
                            else {Idxminf.push_back(std::vector<uint>({rows,col_idx}));}
                        }
                        else if (isnan(values.back())){
                            Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
                        }
                        col_idx++;
                    }
                    if (cols!=col_idx){
                        std::cout<<cols<<" "<<col_idx<<std::endl;
                        throw std::invalid_argument("Not all rows has same number of entry! First row has "+std::to_string(cols)+" columns but row "+std::to_string(rows)+" has "+std::to_string(col_idx)+" columns!" );
                    }
                    ++rows;
                    col_idx=0;
                }
                X = Eigen::Map<const Eigen::Matrix<typename Matrix::Scalar, Matrix::RowsAtCompileTime, Matrix::ColsAtCompileTime, Eigen::RowMajor> >(values.data(), rows, values.size()/rows);

                SummaryMessage+="Number of rows: "+std::to_string(rows)+"\n";
                SummaryMessage+="Number of columns: "+std::to_string(cols)+"\n";
                SummaryMessage+="Number of positive infinity values: "+std::to_string(Idxpinf.size())+". They are at \n" ;
                for(auto each :Idxpinf){
                    SummaryMessage+="("+std::to_string(each[0])+","+std::to_string(each[1])+") ";
                }
                SummaryMessage+="\n";
                SummaryMessage+="Number of negative infinity values: "+std::to_string(Idxminf.size())+". They are at \n";
                for(auto each :Idxminf){
                    SummaryMessage+="("+std::to_string(each[0])+","+std::to_string(each[1])+")"+" ";
                }
                SummaryMessage+="\n";
                SummaryMessage+="Number of missing values: "+std::to_string(Idxmissing.size())+". They are at ";
                for(auto each :Idxmissing){
                    SummaryMessage+="("+std::to_string(each[0])+","+std::to_string(each[1])+")"+" ";
                }
                SummaryMessage+="\n";
                //    for (auto fvalue:values) {std::cout<<fvalue<<std::endl;}
                SummaryMessage+="Columns of categorical values: Column ";
                for (auto idx:colCat) {
                    SummaryMessage+=std::to_string(idx)+" ";}
                SummaryMessage+="\n";

                return {rows,cols,SummaryMessage};
                }

            };
    class CosanData: public CosanRawData{
        public:
            CosanData()=delete;
            CosanMatrix & GetInput(){
                return X;
            }
            const CosanMatrix & GetTarget() const{
                return Y;
            }
            virtual const std::string  GetName() const {return "Processed Data Object.";}};
}

#endif
