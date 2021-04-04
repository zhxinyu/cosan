#ifndef COSAN_PREPROCESSSOR_H
#define COSAN_PREPROCESSSOR_H

#include <cosan/base/CosanBO.h>
#include <cosan/data/CosanData.h>
namespace Cosan {
    class Preprocessor: public CosanBO{
    public:
        Preprocessor() {}

        virtual ~Preprocessor() = default;

        virtual void fit(const CosanMatrix& X) = 0;

        virtual CosanMatrix transform(const CosanMatrix& X) = 0;
    };
}


#endif //COSAN_PREPROCESSSOR_H
