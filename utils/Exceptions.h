#ifndef EXCEPTION_H
#define EXCEPTION_H

// import from other lib
#include<exception>

// import from Cosan

namespace Cosan
{
	/*
		Exception for different input matrix sizes
	*/
	class DiffSizeException: public exception
	{
		virtual const char* what()
		{
			return "The size of given matrices are different";
		};

	} DiffSize;


	/*
		Exceptin for invalid lable shape
	*/
	class InvalidLabelShapeException: public exception
	{
		virtual const char* what()
		{
			return "The shape of the labels is required to be (n ,1)";
		};
	} InvalidLabelShape;
};

#endif