#ifndef COSAN_PREPROCESSSOR_H
#define COSAN_PREPROCESSSOR_H

#include "../base/common.h"

namespace Cosan {
    class preprocesssor {
    public:
        preprocesssor() = default;

        virtual ~preprocesssor() = default;

        virtual void fit(EigenMatrix X) = 0;

        virtual EigenMatrix transform(EigenMatrix X) = 0;
    };
}


#endif //COSAN_PREPROCESSSOR_H
