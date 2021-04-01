#ifndef COSAN_STANDARDSCALER_H
#define COSAN_STANDARDSCALER_H

#include "preprocesssor.h"

namespace Cosan {
    class standardScaler : protected Cosan::preprocesssor {
    public:
        standardScaler() = default;

        ~standardScaler() override = default;

        EigenMatrix standardize(EigenMatrix X);

//    private:

        void fit(EigenMatrix X) override;

        EigenMatrix transform(EigenMatrix X) override;

        EigenVector mean;
        EigenVector std;
    };

}


#endif //COSAN_STANDARDSCALER_H
