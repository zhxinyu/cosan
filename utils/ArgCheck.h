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
		m1: a refrence to a CosanMatrix object
		m2: a refrence to a CosanMatrix object
	Output:
		result: bool; true, if they have the same size;
					  false, otherwise
	*/
	bool SameSize(CosanMatrix& m1, CosanMatrix& m2)
	{
		if (m1.rows() == m2.rows) && (m1.cols() == m2.cols())
			return true;
		else
			return false;
	};


	/*
	Check if the shape of the input matrix is (n, 1)
	Input:
		m1: a refrence to a CosanMatrix object
	Output:
		result: bool; true, if it has the shape (n, 1)
	*/
	bool LabelShape(CosanMatrix& m)
	{
		if (m.rows() >= 1) && (m.cols() == 1)
			return true;
		else
			return false;
	}

};

# endif