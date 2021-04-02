#ifndef __UTILS_H_INCLUDED__
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <math.h>
#include <Eigen/Dense>

#define __UTILS_H_INCLUDED__

//typedef struct {
//    double fValue;
//    std::string sValue;
//    enum value_tag {type_string,type_float};
//    value_tag type;
//} CsvData;

//
//template<typename Matrix>
//std::tuple<uint,uint,std::string> _load_csv (const std::string & path,cosan::CosanMatrix& X,std::vector<std::vector<uint>>& Idxpinf,
//                 std::vector<std::vector<uint>>& Idxminf,std::vector<std::vector<uint>>& Idxmissing,
//                 std::vector<std::string> &svalues, std::set<uint> & colCat) {
//
//    std::ifstream indata;
//    indata.open(path);
//    std::string line;
//    std::vector<double> values;
////    std::vector<std::string> svalues;
//    uint rows = 0,cols = 0,col_idx=0;
////    uint col_idx=0;
////    std::vector<std::vector<uint>> Idxpinf,Idxminf,Idxmissing;
////    std::set<uint> colCat;
//    double result;
//    std::size_t pos;
//    std::string SummaryMessage;
///**
// *  Get the first line information
// */
//
//    std::getline(indata, line);
//    std::stringstream lineStream(line);
//    std::string cell;
//    while(getline(lineStream, cell, ',')) {
//        if (cell.size()==0){
//            values.push_back(stod(std::string("nan")));
//            Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
//            col_idx++;
//            cols=std::max(cols,col_idx);
//            continue;
//        }
//        try{
//            result = std::stod(cell, &pos);
//        }catch(...){
//            svalues.push_back(cell);
//            colCat.insert(col_idx);
//            col_idx++;
//            cols=std::max(cols,col_idx);
//            continue;
//        }
//        if (pos!=cell.size()){
//            throw std::invalid_argument(
//                    "Incorrect numeric format! Abort the program. The entry reads "+cell+
//                    " and the position is ("+ std::to_string(rows)+","+ std::to_string(col_idx)+")");
//        }
//        values.push_back(result);
//        if (isinf(values.back())){
//            if (values.back()==std::numeric_limits<double>::infinity()){
//                Idxpinf.push_back(std::vector<uint>({rows,col_idx}));}
//            else {Idxminf.push_back(std::vector<uint>({rows,col_idx}));}
//        }
//        else if (isnan(values.back())){
//            Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
//        }
//        col_idx++;
//        cols=std::max(cols,col_idx);
//    }
//    rows = 1;
//    col_idx = 0;
//
//
//    while (std::getline(indata, line)) {
////        std::stringstream lineStream(line);
////        std::string cell;
//        lineStream.str("");
//        lineStream.clear(); // Clear state flags.
//        lineStream<<line;
//        while(getline(lineStream, cell, ',')) {
//            if (cell.size()==0){
//                if (colCat.find(col_idx)==colCat.end()){
//                    values.push_back(stod(std::string("nan")));
//                }
//                else{
//                    svalues.push_back("");
//                }
//                Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
//                col_idx++;
//                continue;
//            }
//            try{
//                result = std::stod(cell, &pos);
//            }catch(...){
//                if (colCat.find(col_idx)!=colCat.end())
//                {
//                    svalues.push_back(cell);
//                    colCat.insert(col_idx);
//                    col_idx++;
//                    continue;}
//                else{
//                    throw std::invalid_argument(
//                            "Incorrect value type! Should be numeric but non-numeric input. The entry reads "+cell+
//                            " and the position is ("+ std::to_string(rows)+","+ std::to_string(col_idx)+")");
//                }
//            }
//            if (pos!=cell.size()){
//                throw std::invalid_argument(
//                        "Incorrect numeric format! Abort the program. The entry reads "+cell+
//                        " and the position is ("+ std::to_string(rows)+","+ std::to_string(col_idx)+")");
//            }
//            values.push_back(result);
//            if (isinf(values.back())){
//                if (values.back()==std::numeric_limits<double>::infinity()){
//                    Idxpinf.push_back(std::vector<uint>({rows,col_idx}));}
//                else {Idxminf.push_back(std::vector<uint>({rows,col_idx}));}
//            }
//            else if (isnan(values.back())){
//                Idxmissing.push_back(std::vector<uint>({rows,col_idx}));
//            }
//            col_idx++;
//        }
//        if (cols!=col_idx){
//            std::cout<<cols<<" "<<col_idx<<std::endl;
//            throw std::invalid_argument("Not all rows has same number of entry! First row has "+std::to_string(cols)+" columns but row "+std::to_string(rows)+" has "+std::to_string(col_idx)+" columns!" );
//        }
//        ++rows;
//        col_idx=0;
//    }
//    X = Eigen::Map<const Eigen::Matrix<typename Matrix::Scalar, Matrix::RowsAtCompileTime, Matrix::ColsAtCompileTime, Eigen::RowMajor> >(values.data(), rows, values.size()/rows);
//
//    SummaryMessage+="Number of rows: "+std::to_string(rows)+"\n";
//    SummaryMessage+="Number of columns: "+std::to_string(cols)+"\n";
//    SummaryMessage+="Number of positive infinity values: "+std::to_string(Idxpinf.size())+". They are at \n" ;
//    for(auto each :Idxpinf){
//        SummaryMessage+="("+std::to_string(each[0])+","+std::to_string(each[1])+") ";
//    }
//    SummaryMessage+="\n";
//    SummaryMessage+="Number of negative infinity values: "+std::to_string(Idxminf.size())+". They are at \n";
//    for(auto each :Idxminf){
//        SummaryMessage+="("+std::to_string(each[0])+","+std::to_string(each[1])+")"+" ";
//    }
//    SummaryMessage+="\n";
//    SummaryMessage+="Number of missing values: "+std::to_string(Idxmissing.size())+". They are at ";
//    for(auto each :Idxmissing){
//        SummaryMessage+="("+std::to_string(each[0])+","+std::to_string(each[1])+")"+" ";
//    }
//    SummaryMessage+="\n";
////    for (auto fvalue:values) {std::cout<<fvalue<<std::endl;}
//    SummaryMessage+="Columns of categorical values: Column ";
//    for (auto idx:colCat) {
//        SummaryMessage+=std::to_string(idx)+" ";}
//    SummaryMessage+="\n";
//
//    return {rows,cols,SummaryMessage};
//}

template<typename Matrix>
Matrix load_csv1 (const std::string & path) {
    std::ifstream indata;

    indata.open(path);
    std::string line;
    std::vector<double> values;
    uint rows = 0;
    while (std::getline(indata, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        while (getline(lineStream, cell, ',')) {
            values.push_back(stod(cell));
        }
        ++rows;
    }

    return Eigen::Map<const Eigen::Matrix<typename Matrix::Scalar, Matrix::RowsAtCompileTime, Matrix::ColsAtCompileTime, Eigen::RowMajor> >(values.data(), rows, values.size()/rows);
}


template<typename Matrix>
void save_csv(const std::string & path, const Matrix & matrix){
//    if (path.substr(path.size()-4)!=".csv"){
//        path.append(".csv");
//    }
    std::ofstream file(path,std::ios::out);
    if (file.is_open()){
        Eigen::IOFormat csvFmt(Eigen::FullPrecision,0,",");
        file<<matrix.format(csvFmt);
        file.close();
    }
}

void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove,0,numRows-rowToRemove,numCols) = matrix.block(rowToRemove+1,0,numRows-rowToRemove,numCols).eval();

    matrix.conservativeResize(numRows,numCols);
}

void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove).eval();

    matrix.conservativeResize(numRows,numCols);
}

#endif
