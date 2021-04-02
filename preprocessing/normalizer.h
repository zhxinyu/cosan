#ifndef COSAN_NORMALIZER_H
#define COSAN_NORMALIZER_H

#include "preprocesssor.h"

namespace Cosan {
    class normalizer : protected Cosan::preprocesssor {
    public:
        EigenMatrix normalize(const EigenMatrix& X);

    protected:
        void fit(EigenMatrix X) override;

        EigenMatrix transform(EigenMatrix X) override;
    };

}

#endif //COSAN_NORMALIZER_H
