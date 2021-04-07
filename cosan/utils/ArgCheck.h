#ifndef Arg_CHECK_H
#define Arg_CHECK_H

// import from other lib 
#include<string>
#include<Eigen/Dense>

// import from Cosan
#include<cosan/data/CosanData.h>

/*
	a collection of utility functions to check the 
	size and type of the given objects
*/

namespace Cosan
{
	/*
	Check if the two input matrix has the same size
	Input:
		m1: a refrence to a CosanMatrix<NumericType> object
		m2: a refrence to a CosanMatrix<NumericType> object
	Output:
		result: bool; true, if they have the same size;
					  false, otherwise
	*/
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	bool SameSize(const CosanMatrix<NumericType>& m1, const CosanMatrix<NumericType>& m2)
	{
		if ((m1.rows() == m2.rows) && (m1.cols() == m2.cols() ) ){
			return true;}
		else{
			return false;}
	};

	/*
	Check if the shape of the input matrix is (n, 1)
	Input:
		m1: a refrence to a CosanMatrix<NumericType> object
	Output:
		result: bool; true, if it has the shape (n, 1)
	*/
    template<typename NumericType,
            typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
	bool LabelShape(const CosanMatrix<NumericType>& m)
	{
		if ((m.rows() >= 1) && (m.cols() == 1)) {
		    return true;}
		else{
			return false;}
	}

};

# endif