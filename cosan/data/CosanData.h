#ifndef __COSANData_H_INCLUDED__
#define __COSANData_H_INCLUDED__
#include <string>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <cosan/io/utils.h>
#include <cosan/base/CosanBO.h>
#include <tuple>
#include <unordered_map>
#include <vector>
//typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> EigenMatrix;
namespace Cosan
{
//    class CosanMatrix: public Eigen::MatrixXd{
//    public:
//        CosanMatrix(): Eigen::MatrixXd(){}
//        CosanMatrix(int row, int col ): Eigen::MatrixXd(row,col){}
//        template<typename OtherDerived>
//        CosanMatrix(const Eigen::MatrixBase<OtherDerived> &other): Eigen::MatrixXd(other){}
//
//        template<typename OtherDerived>
//        CosanMatrix & operator=(const Eigen::MatrixBase <OtherDerived>& other){
//            this->Eigen::MatrixXd::operator=(other);
//            return *this;
//        }
//
//    template<typename NumericType,
//             typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    template<Numeric NumericType>
    class CosanRawData: public CosanBO{
        public:
            CosanRawData():CosanBO(){}
            CosanRawData(const std::string & srcX):CosanBO(){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
                if (std::is_same_v<NumericType, bool>){
                    throw std::invalid_argument(
                            "We do not accept bool at this moment. Try unsigned int, unsigned long, unsigned long long, int, "
                            "long, long, float, double ,long double.");
                }

                SetInput(srcX);}

            CosanRawData(const std::string & srcX,
                      const std::string & srcY):CosanBO(){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
                if (std::is_same_v<NumericType, bool>){
                    throw std::invalid_argument(
                            "We do not accept bool at this moment. Try unsigned int, unsigned long, unsigned long long, int, "
                            "long, long, float, double ,long double.");
                }

                SetInput(srcX);
                SetTarget(srcY);
            }
            //        virtual ~CosanBO();
            void SetInput(const std::string & srcX){
                std::tie(rowsX,colsX,SummaryMessageX) = _load_csv(srcX,X,IdxpinfX,IdxminfX,IdxmissingX,svaluesX,colCatX);
            }

            void SetTarget(const std::string & srcY){
                std::tie(rowsY,colsY,SummaryMessageY) = _load_csv(srcY,Y,IdxpinfY,IdxminfY,IdxmissingY,svaluesY,colCatY);
                if (colCatY.size()!=0){
                    catY=true;
                }
            }

            void UpdateData(const CosanMatrix<NumericType>& inputX){
                X = inputX;
            }
            void UpdateData(const CosanMatrix<NumericType>& inputX,const CosanMatrix<NumericType>  &inputY){
                X = inputX;
                Y = inputY;
            }


            void UpdateCat(const std::vector<std::string>  & inputX){
                svaluesX = inputX;
            }
            void UpdateCat(const std::vector<std::string>  & inputX,const std::vector<std::string>  & inputY){
                svaluesX = inputX;
                svaluesY = inputY;
            }


            CosanMatrix<NumericType>  GetInput()  {
                return X;
            }
            CosanMatrix<NumericType>  GetTarget()  {
                return Y;
            }

            const CosanMatrix<NumericType>&  GetInput()  const {
                return X;
            }
            const CosanMatrix<NumericType>&  GetTarget()  const {
                return Y;
            }

            std::tuple<gsl::index,gsl::index> GetMissingNumber(){
                return {X.array().isNaN().template cast<NumericType>().sum(),Y.array().isNaN().template cast<NumericType>().sum()};
            }

            //        virtual CosanBO *Shallow_copy() const;
            //        virtual CosanBO *Deep_copy() const;

            virtual const std::string  GetName() const {return "Raw Data Object.";}

            //        virtual bool SaveFile(const std::string &path ,const std::string & prefix = "");
            //        virtual bool LoadFile(const std::string &path);
            //        void PrintModel();
            //        virtual bool Equals(CosanBO* other, float accuracy = 0.0);
            //        virtual CosanBO* Clone();
            const std::string&  GetSummaryMessageX() const {return SummaryMessageX;}
            const std::string&  GetSummaryMessageY() const {return SummaryMessageY;}
            std::unordered_map<gsl::index,gsl::index> & GetRawToNumIdx(){return _raw2numIdx;}
            std::unordered_map<gsl::index,gsl::index> & GetRawToCatIdx(){return _raw2catIdx;}
            std::vector<std::vector<gsl::index>>   GetIdxpinfX() const {return IdxpinfX;}
            std::vector<std::vector<gsl::index>>   GetIdxminfX() const {return IdxminfX;}
            std::vector<std::vector<gsl::index>>   GetIdxmissingX() const {return  IdxmissingX;}

            std::vector<std::vector<gsl::index>> GetIdxpinfY() const {return  IdxpinfY;}
            std::vector<std::vector<gsl::index>>  GetIdxminfY()  const {return  IdxminfY;}
            std::vector<std::vector<gsl::index>> GetIdxmissingY()  const {return  IdxmissingY;}
            std::set<gsl::index>  GetcolCatX()  const{return colCatX;}
            std::set<gsl::index>  GetcolCatY()  const {return colCatY;}
            bool GetcatY() const {return catY;}
            gsl::index GetrowsX()  {
                rowsX=X.rows();
                return rowsX;
            }
            gsl::index GetrowsY()  {
                rowsY=Y.rows();
                return rowsY;
            }
            gsl::index GetcolsX() {
                colsX = X.cols();
                return colsX;
            }
            gsl::index GetcolsY()  {
                colsY = Y.cols();
                return colsY;
            }

            std::vector<std::string>  GetsvaluesX()  const {return svaluesX;}
            std::vector<std::string>  GetsvaluesY()  const {return svaluesY;}

            CosanMatrix<NumericType> GetType(){return __TYPE;}
        protected:
                CosanMatrix<NumericType> X;
                CosanMatrix<NumericType> Y;
                CosanMatrix<NumericType> __TYPE;
                std::string SummaryMessageX,SummaryMessageY;
                std::vector<std::vector<gsl::index>> IdxpinfX,IdxminfX,IdxmissingX;
                std::vector<std::vector<gsl::index>> IdxpinfY,IdxminfY,IdxmissingY;
                std::set<gsl::index> colCatX,colCatY;
                bool catY = false;
                gsl::index rowsX = 0,colsX = 0;
                gsl::index rowsY = 0,colsY = 0;
                std::vector<std::string> svaluesX,svaluesY;
        private:

            std::unordered_map<gsl::index,gsl::index> _raw2numIdx,_raw2catIdx;
            // template<typename Matrix>
            std::tuple<gsl::index,gsl::index,std::string> _load_csv (const std::string & path, CosanMatrix<NumericType>& X,std::vector<std::vector<gsl::index>>& Idxpinf,
                                                         std::vector<std::vector<gsl::index>>& Idxminf,std::vector<std::vector<gsl::index>>& Idxmissing,
                                                         std::vector<std::string> &svalues, std::set<gsl::index> & colCat) {

                std::ifstream indata;
                indata.open(path);
                std::string line;
                std::vector<NumericType> values;
                //    std::vector<std::string> svalues;
                gsl::index rows = 0,cols = 0,col_idx=0;
                //    uint col_idx=0;
                //    std::vector<std::vector<uint>> Idxpinf,Idxminf,Idxmissing;
                //    std::set<uint> colCat;
                NumericType result;
                std::size_t pos;
                std::string SummaryMessage;

                //   stod -> "-23","-12E1","-+nan" (is a double type), "+\- inf","+\- infinity", "jklsgfd","1235lkjfg",
//                 first row: empty/nonempty: empty-> numerical nan,
    //                 not empty-> can read numeric ->  it is indeed a correct numeric format
//                                                  ->  wrong format i.e. "1235lkjfg" throw error
    //                          -> cannot read numeric->  then consider this as category

//              then set colCat, cols,
                //   numeric-format,
        //

                /**
                 *  Get the first line information
                 */

                std::getline(indata, line);
                std::stringstream lineStream(line);
                std::string cell;
                while(getline(lineStream, cell, ',')) {
                    if (cell.size()==0){
                        values.push_back(StringToNum<NumericType>(std::string("nan")));
                        Idxmissing.push_back(std::vector<gsl::index>({rows,col_idx}));
                        col_idx++;
                        cols=std::max(cols,col_idx);
                        continue;
                    }
                    try{
                        result = StringToNum<NumericType>(cell, &pos);
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
                        if (values.back()==std::numeric_limits<NumericType>::infinity()){
                            Idxpinf.push_back(std::vector<gsl::index>({rows,col_idx}));}
                        else {Idxminf.push_back(std::vector<gsl::index>({rows,col_idx}));}
                    }
                    else if (isnan(values.back())){
                        Idxmissing.push_back(std::vector<gsl::index>({rows,col_idx}));
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
                                values.push_back(StringToNum<NumericType>(std::string("nan")));
                            }
                            else{
                                svalues.push_back("");
                            }
                            Idxmissing.push_back(std::vector<gsl::index>({rows,col_idx}));
                            col_idx++;
                            continue;
                        }
                        try{
                            result = StringToNum<NumericType>(cell, &pos);
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
                            if (values.back()==std::numeric_limits<NumericType>::infinity()){
                                Idxpinf.push_back(std::vector<gsl::index>({rows,col_idx}));}
                            else {Idxminf.push_back(std::vector<gsl::index>({rows,col_idx}));}
                        }
                        else if (isnan(values.back())){
                            Idxmissing.push_back(std::vector<gsl::index>({rows,col_idx}));
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
                X.resize(rows,values.size()/rows);
                gsl::index i =0,__cols =  values.size()/rows;
                for (auto &each :values ){
                    X(i/__cols,i%__cols) = each;
                    i++;
                }

//                        Eigen::Map<const CosanMatrix<NumericType>>(values.data(), rows, values.size()/rows);

                SummaryMessage+="Number of rows: "+std::to_string(rows)+"\n";
                SummaryMessage+="Number of columns: "+std::to_string(cols)+"\n";
                SummaryMessage+="Number of positive infinity values: "+std::to_string(Idxpinf.size())+". They are at " ;
                for(auto each :Idxpinf){
                    SummaryMessage+="("+std::to_string(each[0])+","+std::to_string(each[1])+") ";
                }
                SummaryMessage+="\n";
                SummaryMessage+="Number of negative infinity values: "+std::to_string(Idxminf.size())+". They are at ";
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
                gsl::index j = 0 ;
                for (gsl::index i = 0;i<cols;i++){
                    if (colCat.find(i)==colCat.end()){
                        _raw2numIdx[i] = j;
                        j++;}
                }
                j = 0 ;
                for (gsl::index i = 0;i<cols;i++){
                    if(colCat.find(i)!=colCat.end()){
                        _raw2catIdx[i]=j;
                        j++;
                    }
                }


                return {rows,cols,SummaryMessage};


                }

            };

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    template<Numeric NumericType>
    class CosanData: public CosanRawData<NumericType>{
        public:
            CosanData()=default;
            CosanData(const CosanMatrix<NumericType> & inputX):CosanRawData<NumericType>(){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
                this->X = inputX;
            }
            CosanData(const CosanMatrix<NumericType>&  inputX,const CosanMatrix<NumericType>& inputY):CosanRawData<NumericType>(){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
                this->X = inputX;
                this->Y = inputY;}

            virtual const std::string  GetName() const {return "Processed Data Object.";}
        private:
    };
}

#endif
