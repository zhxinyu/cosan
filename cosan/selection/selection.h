//
// Created by Xinyu Zhang on 4/4/21.
//

#ifndef COSAN_SELECTION_H
#define COSAN_SELECTION_H


#include <random>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <variant>
//#include <cosan/base/CosanBO.h>
#include <cosan/data/CosanData.h>
#include <cosan/model/CosanModel.h>
#include <cosan/evaluation/CosanMetric.h>
#include<cosan/utils/ArgCheck.h>
#include<cosan/utils/Exceptions.h>
#include <omp.h>
//#include <mutex>
namespace Cosan{
    class Selection: public CosanBO {
        public:
            Selection():CosanBO(){}
    };
    class Search: public Selection {
    public:
        Search():Selection(){}
    };
    class Splitter : public Selection {
    public:
        Splitter() : Selection(){
            KFoldNumber = 5;
        }
        Splitter(gsl::index kfoldnumber){
            KFoldNumber = kfoldnumber;
        }
        Splitter (gsl::index nrows,gsl::index kfoldnumber) : Selection() {
            if (nrows<=kfoldnumber){
                throw SmallRows;
            }
            KFoldNumber = kfoldnumber;
            SetSplit(nrows);
        }
        gsl::index GetKFoldNumber() {return KFoldNumber;}
        virtual void SetSplit(gsl::index nrows) {}
    protected:
        gsl::index KFoldNumber = 5;
    };

}
#endif //COSAN_SELECTION_H
