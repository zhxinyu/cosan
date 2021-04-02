#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <math.h>
#include <limits>
int main(int argc, char *argv[]) {
//    std::stringstream indata(std::string("125,23,,nan,-nan,infinity,-inf,0, 1E1vdfz,'bd'\n 1,2,3,4,5,6,7,8,9,'as'"));
//    std::stringstream indata(std::string("125,'',,nan,-nan,infinity,-inf,0,1E1,'bd','ac'\n 1,'a',2,4,5,6,7,8,9,'as','sd"));
//    std::stringstream indata(std::string("125,'',,nan,-nan,infinity,-inf,0,1E1fds,'bd','ac'\n 1,1,'abc',4,9,'as','sd' "));
//    std::stringstream indata(std::string("125,'',,nan,-nan,infinity,-inf,0,1E1,'bd','ac'\n 1,1,'abc',4,9,'as','sd' "));
//    std::stringstream indata(std::string("125,'',,nan,-nan,infinity,-inf,0,1E1,'bd','ac'\n 1,1,2fd,4,9,'as','sd' "));
//    std::stringstream indata(std::string("125,'',,nan,-nan,infinity,-inf,0,1E1,'bd','ac'\n "
//                                                 "  1, 1,2,4,  9, 25,5,235,53, 'as','sd' "));

//    std::stringstream indata(std::string("125,'',,nan,-nan,infinity,-inf,0,1E1,'bd','ac'\n "
//                                         "  1, 1,2,4,  9, 25,5,235,Infinity, 'fs','sd' "));
//
    std::ifstream indata;
    indata.open(argv[1]);
    std::string line;
    std::vector<double> values;
    std::vector<std::string> svalues;
    uint rows = 0,cols = 0,col_idx=0;
    std::vector<std::vector<uint>> Idxpinf,Idxminf,Idxmissing;
    std::set<uint> colCat;
    double result;
    std::size_t pos;

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


    std::cout<<"Number of rows: "<<rows<<std::endl;
    std::cout<<"Number of columns: "<<cols<<std::endl;
    std::cout<<"Number of positive infinity values: "<<Idxpinf.size()<<". They are at " ;
    for(auto each :Idxpinf){
        std::cout<<"("<<each[0]<<","<<each[1]<<")"<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Number of negative infinity values: "<<Idxminf.size()<<". They are at ";
    for(auto each :Idxminf){
        std::cout<<"("<<each[0]<<","<<each[1]<<")"<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Number of missing values: "<<Idxmissing.size()<<". They are at ";
    for(auto each :Idxmissing){
        std::cout<<"("<<each[0]<<","<<each[1]<<")"<<" ";
    }
    std::cout<<std::endl;
//    for (auto fvalue:values) {std::cout<<fvalue<<std::endl;}
    std::cout<<"Columns of categorical values: Column ";
    for (auto idx:colCat) {std::cout<<idx<<" ";}
    std::cout<<std::endl;
//    std::cout<<svalues.size()<<std::endl;
//    svalues.push_back("");
//    std::cout<<svalues.size()<<std::endl;
//    std::cout<<svalues[0]<<"HAHA"<<svalues.back()<<"HAHA"<<std::endl;
//    std::cout<<(svalues[0].compare(svalues.back()))<<std::endl;
    return 0;
}
