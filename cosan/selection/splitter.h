//
// Created by Xinyu Zhang on 4/6/21.
//

#ifndef COSAN_SPLITTER_H
#define COSAN_SPLITTER_H
#include <cosan/selection/selection.h>
#include <omp.h>
//#include <mutex>
namespace Cosan {
    class Splitter : public Selection {
        public:
            Splitter() : Selection() {}
    };

}


#endif //COSAN_SPLITTER_H
