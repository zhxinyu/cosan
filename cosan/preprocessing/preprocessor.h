#ifndef COSAN_PREPROCESSSOR_H
#define COSAN_PREPROCESSSOR_H

#include <cosan/base/CosanBO.h>
#include <cosan/data/CosanData.h>
namespace Cosan {
//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
    /**
     * Base class for precessor
     *
     */
    template<Numeric NumericType>
    class Preprocessor: public CosanBO{
    public:
        Preprocessor():CosanBO() {};

        virtual ~Preprocessor() = default;

        virtual void fit(const CosanMatrix<NumericType> & X){}

        virtual CosanMatrix<NumericType> transform(const CosanMatrix<NumericType> & X) {
            return CosanMatrix<NumericType>();
        };
    };
}


#endif //COSAN_PREPROCESSSOR_H
