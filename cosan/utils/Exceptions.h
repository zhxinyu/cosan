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
	class DiffSizeException: public std::exception
	{
		virtual const char* what()
		{
			return "The size of given matrices are different";
		};

	} DiffSize;

    class TooSmallSizeException: public std::exception
    {
        virtual const char* what()
        {
            return "The number of rows is too small";
        };

    } SmallRows;


	/*
		Exceptin for invalid lable shape
	*/
	class InvalidLabelShapeException: public std::exception
	{
		virtual const char* what()
		{
			return "The shape of the matrix is required to be (n ,1)";
		};
	} InvalidLabelShape;
};

#endif