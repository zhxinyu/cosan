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
    /**
     *  @brief Raw Data container.
     *  @details Every constructor needs to have at least one input. To obtain CosanRawData, three constructors can be used:
     *  @code CosanRawData(const std::string & srcX); @endcode
     *  @code CosanRawData(const std::string & srcX, const std::string & srcY); @endcode
     **/
    template<Numeric NumericType>
    class CosanRawData: public CosanBO{
        public:
            CosanRawData()=default;
        /**
         *  @brief Constructor: Read data X and Y from csv files and form raw data container.
         *  @param[in] srcX path to the csv file of data X;
         *  @param[in] srcY path to the csv file of data Y.
         *  @note X and Y are from two separate csv files. For the data format of csv files, see Tutorial.
         **/
         CosanRawData(const std::string & srcX, const std::string & srcY):CosanBO(){
//             static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
             if (std::is_same_v<NumericType, bool>){
                 throw std::invalid_argument(
                         "We do not accept bool at this moment. Try unsigned int, unsigned long, unsigned long long, int, "
                         "long, long, float, double ,long double.");
             }
             SetInput(srcX);
             SetTarget(srcY);
         }
        /**
         *  @brief Constructor: Read data X from csv and form raw data container.
         *  @param[in] srcX path to the csv file of data X.
         **/
        CosanRawData(const std::string & srcX):CosanBO(){
//            static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
            if (std::is_same_v<NumericType, bool>){
                throw std::invalid_argument(
                        "We do not accept bool at this moment. Try unsigned int, unsigned long, unsigned long long, int, "
                        "long, long, float, double ,long double.");
            }
            SetInput(srcX);}
        //        virtual ~CosanBO();

        /**
         *  @brief Update input X from csv file.
         *  @param[in] srcX path to the csv file of data X.
         *  @details
         **/
         void SetInput(const std::string & srcX){
             std::tie(rowsX,colsX,SummaryMessageX) = _load_csv(srcX,X,IdxpinfX,IdxminfX,IdxmissingX,svaluesX,colCatX);
         }
        /**
         *  @brief Update target Y from csv file.
         *  @param[in] srcY path to the csv file of data Y.
         *  @details
         **/
         void SetTarget(const std::string & srcY){
             std::tie(rowsY,colsY,SummaryMessageY) = _load_csv(srcY,Y,IdxpinfY,IdxminfY,IdxmissingY,svaluesY,colCatY);
             if (colCatY.size()!=0){
                 catY=true;
             }
         }
        /**
         *  @brief Concatenate X using CosanMatrix<NumericType> input X. Add new columns
         *  @param[in] const CosanMatrix<NumericType>& inputX
         *
         *  @details Add new columns.
         **/
         void ConcatenateData(const CosanMatrix<NumericType>& inputX){
             if (GetrowsX()!=inputX.rows()){
                 throw std::invalid_argument(fmt::format("To concatenate, the number of rows from inputX should match with original X. Current nrow of X is {:}", GetrowsX() ));
             }
             for (gsl::index i = 0 ;i<inputX.cols();i++){
                 X.conservativeResize(X.rows(), X.cols()+1);
                 X.col(X.cols() - 1) = inputX.col(i);
             }
         }
        /**
         *  @brief Update X using CosanMatrix<NumericType> input X
         *  @param[in] const CosanMatrix<NumericType>& inputX
         *  @details
         **/
        void UpdateData(const CosanMatrix<NumericType>& inputX){
            X = inputX;
        }
        /**
         *  @brief Update X and Y using CosanMatrix<NumericType> inputX,inputY
         *  @param[in] const CosanMatrix<NumericType>& inputX,const CosanMatrix<NumericType>& inputY
         *  @details
         **/
         void UpdateData(const CosanMatrix<NumericType>& inputX,const CosanMatrix<NumericType>  &inputY){
             X = inputX;
             Y = inputY;
         }
        /**
         *  @brief Update categorical vector svaluesX using std::vector<std::string>  & inputX
         *  @param[in] const std::vector<std::string>  & inputX
         *  @details
         **/
         void UpdateCat(const std::vector<std::string>  & inputX){
             svaluesX = inputX;
         }
        /**
         *  @brief Update categorical vector svaluesX,svaluesY using std::vector<std::string>  & inputX,inputY
         *  @param[in] const std::vector<std::string>  & inputX,inputY
         *  @details
         **/
         void UpdateCat(const std::vector<std::string>  & inputX,const std::vector<std::string>  & inputY){
             svaluesX = inputX;
             svaluesY = inputY;
         }

        /**
         *  @brief Get a copy of CosanMatrix<NumericType> X
         **/
         CosanMatrix<NumericType>  GetInput()  {
             return X;
         }
        /**
         *  @brief Get a copy of CosanMatrix<NumericType> Y
         **/
         CosanMatrix<NumericType>  GetTarget()  {
             return Y;
         }
        /**
         *  @brief Get a const reference to const CosanMatrix<NumericType> X
         **/
         const CosanMatrix<NumericType>&  GetInput()  const {
             return X;
         }
        /**
         *  @brief Get a const reference to const CosanMatrix<NumericType> Y
         **/
         const CosanMatrix<NumericType>&  GetTarget()  const {
             return Y;
         }
        /**
         *  @brief Get the total number data information
         *  @return std::tuple<# missing of X,#missing of Y>
         **/
        std::tuple<gsl::index,gsl::index> GetMissingNumber(){
             return {X.array().isNaN().template cast<NumericType>().sum(),Y.array().isNaN().template cast<NumericType>().sum()};
         }

         //        virtual CosanBO *Shallow_copy() const;
         //        virtual CosanBO *Deep_copy() const;
        /**
         *  @brief Get the name of the objects
         *  @return std::string
         **/
         virtual const std::string  GetName() const {return "Raw Data Object.";}

         //        virtual bool SaveFile(const std::string &path ,const std::string & prefix = "");
         //        virtual bool LoadFile(const std::string &path);
         //        void PrintModel();
         //        virtual bool Equals(CosanBO* other, float accuracy = 0.0);
         //        virtual CosanBO* Clone();
        /**
         *  @brief Get the summary message on reading csv file on X
         *  @return std::string
         **/
         const std::string&  GetSummaryMessageX() const {return SummaryMessageX;}
        /**
         *  @brief Get the summary message on reading csv file on Y
         *  @return std::string
         **/
         const std::string&  GetSummaryMessageY() const {return SummaryMessageY;}
        /**
         *  @brief Raw data column index to numeric data matrix X column index
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::unordered_map<gsl::index,gsl::index> & GetRawToNumIdx(){return _raw2numIdx;}
        /**
         *  @brief Raw data column index to categorical data column index
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::unordered_map<gsl::index,gsl::index> & GetRawToCatIdx(){return _raw2catIdx;}
        /**
         *  @brief Get the position of positive infinity in the origin data X
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::vector<std::vector<gsl::index>>   GetIdxpinfX() const {return IdxpinfX;}
        /**
         *  @brief Get the position of negative infinity in the origin data X
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::vector<std::vector<gsl::index>>   GetIdxminfX() const {return IdxminfX;}
        /**
         *  @brief Get the position of missing in the origin data X
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::vector<std::vector<gsl::index>>   GetIdxmissingX() const {return  IdxmissingX;}
        /**
         *  @brief Get the position of positive infinity in the origin data Y
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::vector<std::vector<gsl::index>> GetIdxpinfY() const {return  IdxpinfY;}
        /**
         *  @brief Get the position of negative infinity in the origin data Y
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::vector<std::vector<gsl::index>>  GetIdxminfY()  const {return  IdxminfY;}
        /**
         *  @brief Get the position of missing in the origin data Y
         *  @return std::unordered_map<gsl::index,gsl::index>
         **/
         std::vector<std::vector<gsl::index>> GetIdxmissingY()  const {return  IdxmissingY;}
        /**
         *  @brief Get the column index (in the origin X of csv file) where the column is of categorical type.
         *  @return std::set<gsl::index>
         **/
         std::set<gsl::index>  GetcolCatX()  const{return colCatX;}
        /**
         *  @brief Get the column index (in the origin Y of csv file) where the column is of categorical type.
         *  @return std::set<gsl::index>
         *  @note If Y is one dimension, the size of return should be one. Otherwise it is empty.
         **/
        std::set<gsl::index>  GetcolCatY()  const {return colCatY;}
        /**
         *  @brief True if Y is categorical data type. False otherwise.
         *  @return bool
         **/
         bool GetcatY() const {return catY;}

        /**
         *  @brief Get the number of rows for X.
         *  @return gsl::index
         **/
         gsl::index GetrowsX()  {
             rowsX=X.rows();
             return rowsX;
         }
        /**
         *  @brief Get the number of rows for Y.
         *  @return gsl::index
         **/
        gsl::index GetrowsY()  {
             rowsY=Y.rows();
             return rowsY;
         }
        /**
         *  @brief Get the number of columns for X.
         *  @return gsl::index
         **/
         gsl::index GetcolsX() {
             colsX = X.cols();
             return colsX;
         }
        /**
         *  @brief Get the number of columns for Y.
         *  @return gsl::index
         **/
        gsl::index GetcolsY()  {
             colsY = Y.cols();
             return colsY;
         }
        /**
         *  @brief Get the vector of categorical data from X. order: row first.
         *  @return std::vector<std::string>
         *  @note it is a std::vector of std::string. Strings are stored row-first.
         **/
         std::vector<std::string>  GetsvaluesX()  const {return svaluesX;}
        /**
         *  @brief Get the vector of categorical data from Y. order: row first.
         *  @return std::vector<std::string>
         *  @note it is a std::vector of std::string. Strings are stored row-first.
         **/
         std::vector<std::string>  GetsvaluesY()  const {return svaluesY;}
        /**
         *  @return an empty CosanMatrix<NumericType> data structure
         *  @note it is used to determined CosanMatrix<NumericType> data type.
         **/
        CosanMatrix<NumericType> GetType(){return __TYPE;}
     protected:
            /**
             *  @brief Numeric data from origin CSV file for X.
             **/
             CosanMatrix<NumericType> X;
            /**
             *  @brief Numeric data from origin CSV file for Y.
             **/
             CosanMatrix<NumericType> Y;
             CosanMatrix<NumericType> __TYPE;
            /**
             *  @brief Loading message.
             **/
             std::string SummaryMessageX,SummaryMessageY;
            /**
             *  @brief position for positive, negative infinity and missing values.
             **/
             std::vector<std::vector<gsl::index>> IdxpinfX,IdxminfX,IdxmissingX;
             std::vector<std::vector<gsl::index>> IdxpinfY,IdxminfY,IdxmissingY;
            /**
             *  @brief column idx in the origin data that is categorical data.
             **/
             std::set<gsl::index> colCatX,colCatY;
            /**
             *  @brief true mean respone variable Y is categorical data.
             **/
             bool catY = false;
            /**
             *  @brief number of rows.
             **/
             gsl::index rowsX = 0,colsX = 0;
            /**
             *  @brief number of columns
             **/
             gsl::index rowsY = 0,colsY = 0;
            /**
             * Get the vector of categorical data from original data. order: row first.
             */
             std::vector<std::string> svaluesX,svaluesY;
     private:
         std::unordered_map<gsl::index,gsl::index> _raw2numIdx,_raw2catIdx;
         // template<typename Matrix>

        /**
         * @brief load data from csv
         * @details We accept data file in `csv` format where each data is of dimension n\times p  where n (the number of rows)
         * is number of samples and `p` (the number of columns) denotes number of features. Each data entry is separated by ","
         * and allows for positive/negative infinity (user-specific `NumericType` is `float`,`double` or `long double`),
         * missing values (either emptry entry between two contiguous comma "," or NAN expression ) and non-number string.
         * If user-specific `NumericType` is `float`,`double` or `long double`, acceptable numeric expressions also include
         * hexadecimal and variants of decimal float-poing expression (see [this](https://en.cppreference.com/w/cpp/string/basic_string/stof) for more details).
         * It will throw ``std::invalid_argument`` if the the entry read is not-a-number expression except this entry is
         * of categorical type.
         *
         * We determine each column's data type (either numeric or categorical) by the first row.
         * We treat every entry as numeric if it is a number (whether it is ordinal or numerical) and treat every entry
         * that does not start with a numeric as categorical (also called nominal data specifically). For those starting
         * with a numeric but containing non-numeric character, ```std::invalid_argument``` will be thrown.
         **/
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
    /**
     *  @brief Data container.
     *  @details Every constructor needs to have at least one input. To obtain CosanData, the following constructors can be used:
     *  @code CosanData(gsl::index nrows,gsl::index ncols,NumericType lb=0,NumericType ub = 1) @endcode
     *  @code CosanData(const CosanMatrix<NumericType> & inputX) @endcode
     *  @code CosanData(const CosanMatrix<NumericType>&  inputX,const CosanMatrix<NumericType>& inputY) @endcode
     *  @code CosanData(const std::vector<NumericType>&  inputX,gsl::index nrows,const std::string & order = "rowfirst") @endcode
     *  @code CosanData(const std::vector<NumericType>&  inputX,const std::vector<NumericType>&  inputY,gsl::index nrows,const std::string & order = "rowfirst") @endcode
     **/
    template<Numeric NumericType>
    class CosanData: public CosanRawData<NumericType>{
        public:
            CosanData()=default;
            /**
             *  @brief Generate random matrix with each entry uniformly sampled from lb to lb. Dimension is nrows by ncols.
             **/
            CosanData(gsl::index nrows,gsl::index ncols,NumericType lb=0,NumericType ub = 1):CosanRawData<NumericType>(){
                this->X.resize(nrows,ncols);
                std::default_random_engine generator;
                std::uniform_real_distribution<double> distribution(lb,ub);
                for (gsl::index  i = 0;i<nrows*ncols;i++){
                    this->X(i/ncols,i%ncols) =distribution(generator);
                }
            }
            /**
             *  @brief Get CosanData from CosanMatrix<NUmericType> inputX
             **/
            CosanData(const CosanMatrix<NumericType> & inputX):CosanRawData<NumericType>(){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
                this->X = inputX;
            }
            /**
             *  @brief Get CosanData from CosanMatrix<NUmericType> inputX, inputY
             **/
            CosanData(const CosanMatrix<NumericType>&  inputX,const CosanMatrix<NumericType>& inputY):CosanRawData<NumericType>(){
                static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
                this->X = inputX;
                this->Y = inputY;}
            /**
             *  @brief Get CosanData from std::vector inputX, fill the data either by 'rowfirst' or 'columnfirst'.
             **/
            CosanData(const std::vector<NumericType>&  inputX,gsl::index nrows,const std::string & order = "rowfirst"):CosanRawData<NumericType>(){
                if (nrows>inputX.size() || inputX.size()%nrows!=0){
                    throw std::invalid_argument(
                            fmt::format("Incorrect nrows specification, should be less than or equal to input vector size and size is divisible by nrows. Input vector size is "
                                        "{:} and nrows is {:}",inputX.size(),nrows));
                }
                this->X.resize(nrows,inputX.size()/nrows);
                gsl::index i =0,__cols=inputX.size()/nrows;
                if (order=="columnfirst"){
                    i =0;
                    for (auto &each :inputX ){
                        this->X(i%nrows,i/nrows) = each;
                        i++;
                    }
                    return;
                }
                i =0;
                for (auto &each :inputX ){
                    this->X(i/__cols,i%__cols) = each;
                    i++;
                }
                return;
            }


            /**
             *  @brief Get CosanData from std::vector inputX and inputY, fill the data either by 'rowfirst' or 'columnfirst'.
             **/
            CosanData(const std::vector<NumericType>&  inputX,const std::vector<NumericType>&  inputY,gsl::index nrows,const std::string & order = "rowfirst"):CosanRawData<NumericType>(){
                if (nrows>inputX.size() || inputX.size()%nrows!=0 || nrows!=inputY.size()){
                    throw std::invalid_argument(
                            fmt::format("Incorrect nrows specification, should be less than or equal to input vector size and size is divisible by nrows. inputY size should also be equal to nrows."
                                        "inputX vector size is {:}, inputY vector size is {:} and nrows is {:}",inputX.size(),inputY.size(),nrows));
                }
                this->X.resize(nrows,inputX.size()/nrows);
                this->Y.resize(nrows,1);
                gsl::index i =0,__cols=inputX.size()/nrows;
                for (auto &each:inputY){
                    this->Y(i,0) = each;
                    i++;
                }
                if (order=="columnfirst"){
                    i =0;
                    for (auto &each :inputX ){
                        this->X(i%nrows,i/nrows) = each;
                        i++;
                    }
                    return;
                }
                i =0;
                for (auto &each :inputX ){
                    this->X(i/__cols,i%__cols) = each;
                    i++;
                }
                return;
            }

            /**
             *  @brief Get the name of the object.
             **/
            virtual const std::string  GetName() const {return "Processed Data Object.";}
        private:
    };
}

#endif
