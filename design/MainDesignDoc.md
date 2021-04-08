# Cosan Design Doc V0.8

##### Team member: Jiahe Chen (jc5348), Xinyu Zhang (xz2691), Zida Zhou (zz2791)

## Motivation: 
TODO
(Fun fact: why the project is named Cosan - )

## Type
The arithmetic data type stored in our iterable data containor is defined as 
```
template<typename NumericType,
typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
``` 
That is, an integral type or a floating-point.

## Module Structure
TODO: Add the class hierarchy diagram

### Key Classes

##### [Data Preprocessing](https://github.com/gchenra/cosan/blob/jiahe/design/PreprocessDesignDoc.md)

##### [Linear Model](https://github.com/gchenra/cosan/blob/jiahe/ModelDesignDoc.md)

##### [Model Selection & Evaluation](https://github.com/gchenra/cosan/blob/jiahe/SelectDesignDoc.md)

### Base Classes

##### CosanBO
Cosan Base Objects. 

This class is the base that is inherited by all classes and models. 

##### CosanData

In machine learning, input and output data are presented in the form of matrices or vectors (which is essentially a matrix with its row or its column of length 1). There could be numerical data and categorical data. Raw data by nature are very noisy - there could be infinite numbers and even missing data. 

We design CosanData class as a wrapper to handle a mixture of all of the use cases (double for numerical data, string for categorical data, corner cases of these data representations, etc.). It organizes feature columns such that numerical, categorical, missing, infinite values are represented separately, so other Cosan models can manipulate the raw data in a simple yet powerful way. It takes advantages of gsl::index for indexing. It parses the CSV files for you while providing the error checking needed for downstream processing. 

### Utility Classes

##### Time Series Spliter 
Location: `cosan\selection\timeseriessplit.h`

##### Kfold & Random Kfold
Location: `cosan\selection\kfold.h` & `cosan\selection\randomkfold.h`

##### ArgCheck
Location: `cosan\utils\ArgCheck.h`

##### Exception
Location: `cosan\utils\Exception.h`

##### Other Utility fuctions
Location: `cosan\utils\utils.h`


## General Topics

## Used Open Resource Libraries 
##### Eigen
##### gsl
##### Multithreading

## Future work and extensibility

## Appendix

### Other open source alternatives

Shogun

sklearn

R



----


*Last updated: April 06, 2021*
