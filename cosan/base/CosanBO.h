/**
 *@file CosanBO.h
 *@author Xinyu Zhang
 *@brief CosanBO
 *@date 2021-04-10
 */

#ifndef __COSANBO_H_INCLUDED__
#define __COSANBO_H_INCLUDED__
#include <string>
#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#endif
#include <gsl/gsl>
#include <type_traits>
#include <cosan/utils/utils.h>
#include <cosan/utils/Exceptions.h>
#include <random>


template<typename NumericType>
concept Numeric = std::is_arithmetic<NumericType>::value ;

template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;

namespace Cosan
{

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type
//    >

    /** Description: data structure for matrix. Will be used throughout the project. */
    template<Numeric NumericType>
    using CosanMatrix = Eigen::Matrix<NumericType, Eigen::Dynamic, Eigen::Dynamic> ;

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type
//    >
    /** Description: data structure for column vector. Will be used throughout the project. */
    template<Numeric NumericType>
    using CosanColVector =  Eigen::Matrix<NumericType,  Eigen::Dynamic, 1> ;

//    template<typename NumericType,
//            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type
//    >

/** Description: data structure for row vector. Will be used throughout the project. */
    template<Numeric NumericType>
    using CosanRowVector =  Eigen::Matrix<NumericType,  1, Eigen::Dynamic> ;

//    typedef std::variant<CosanMatrix<unsigned int>, CosanMatrix<unsigned long>,
//                         CosanMatrix<unsigned long long>, >

    /**
     * @brief Cosan Base Object
     * @details: Description: Base object CosanBO which all other Cosan objects inherited from.
     * */
    class CosanBO
    {
    public:
        /**
         *  @brief Default constructor.
         **/
        CosanBO(){
        }
//        virtual ~CosanBO();
//        virtual CosanBO *Shallow_copy() const;
//        virtual CosanBO *Deep_copy() const;

        /**
         *  @brief Get the name of the objects.
         *  @details Description: Get the name of the object. It should return "Abstract Object"
         **/
        virtual const std::string  GetName() const {
            return "Abstract Object";}

//        virtual bool SaveFile(const std::string &path ,const std::string & prefix = "");
//        virtual bool LoadFile(const std::string &path);
//        void PrintModel();
//        virtual bool Equals(CosanBO* other, float accuracy = 0.0);
//        virtual CosanBO* Clone();

    protected:
    };

}

#endif
