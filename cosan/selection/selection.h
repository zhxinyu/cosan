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

#include <cosan/base/CosanBO.h>
#include <cosan/data/CosanData.h>
#include<cosan/utils/ArgCheck.h>
#include<cosan/utils/Exceptions.h>
//#include <omp.h>
//#include <mutex>
namespace Cosan{
    class Selection: public CosanBO {
        public:
            Selection():CosanBO(){}
    };
}
#endif //COSAN_SELECTION_H
