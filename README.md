# Cosan 

##### Team member: Jiahe Chen (jc5348), Xinyu Zhang (xz2691), Zida Zhou (zz2791)

## Overview:
We aim to write an open-source machine learning library Cosan for C++ which provides a data mining and data predictive analytics framework. It implements a selected range of simple and efficient data processing procedures and machine learning algorithms and is designed to interoperate with C++ scientific computing library Eigen/xtensor. 

## Getting started

### How to install Cosan
To use Cosan, you just need to download Cosan source code and include the header files in your program. The header files are the same for all platforms. It is not necessary to use CMake or install anything. In order for your compiler to locate the header files, you can copy or symlink the Cosan folder to ```/usr/local/include```, or specify the path to Cosan when you compile your program.

### How to compile and run Cosan

```g++ -I /path/to/cosan/ your_program.cpp -o your_program && ./your_program```


### Hello World programs

#### Data input
Cosan supports various ways of getting the input dataset. One of the most common ones is to parse the data from a csv file. 

```
Cosan::CosanRawData CD("./path/to/example.csv");
```

You can also choose to create your own dataset when initializing the object.

```
Cosan::CosanMatrix X{3,3};
    X << 1, -1, 2,
         2, 0, 0,
         0, 1, -1;
```

CosanRawData will fulfill your needs with different kinds of data types and all sorts of operations.

#### Preprocessing
Usually the first step when doing data analytics is dataset transformation and preprocessing. 

```
    Cosan::standardScaler ss{};
    std::cout << ss.standardize(CD) << std::endl;
```

#### Linear Models

```
Cosan::CosanRawData CD("./example_data/X.csv","./example_data/y.csv");
Cosan::CosanLinearRegression CLR()
CLRwbias.fit(CD.GetInput(),CD.GetTarget());
std::cout<<CLRwbias.GetBeta()<<std::endl;
```

#### Model selection

# Cosan Design Doc V1.0

## Motivation: 
TODO
(Fun fact: why the project is named Cosan - )

## Type Template
We make use of template and concept to define a numerical type(an integral type or a floating-point). \
This type is widely used throughout our library in `CosanData`, `CosanMatrix`, `CosanModel`, etc.
It implementation is as follow.
```
template<typename NumericType,
concept Numeric = std::is_arithmetic<NumericType>::value;
``` 
We also define another template to restrict type of objects we can use.
The implementaion is as follow.
```
template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;
```
This is to restrict U to be the base of T.

## Module Structure
<img src="class_hierarchy.png" alt="class hierarchy chart" width="800"/>

### Key Classes

##### [Data Preprocessing](https://github.com/gchenra/cosan/blob/xinyu/design/PreprocessDesignDoc.md)

##### [Linear Model](https://github.com/gchenra/cosan/blob/xinyu/design/ModelDesignDoc.md)

##### [Model Selection & Evaluation](https://github.com/gchenra/cosan/blob/xinyu/design/SelectDesignDoc.md)

### Base Classes

##### CosanBO
Location: `cosan\base\CosanBO.h` \
Cosan Base Objects. 

This class is the base that is inherited by all classes and models. 

##### CosanData
Location: `cosan\data\CosanData.h` \

In machine learning, input and output data are presented in the form of matrices or vectors (which is essentially a matrix with its row or its column of length 1). There could be numerical data and categorical data. Raw data by nature are very noisy - there could be infinite numbers and even missing data. 

We design CosanData class as a wrapper to handle a mixture of all of the use cases (double for numerical data, string for categorical data, corner cases of these data representations, etc.). It organizes feature columns such that numerical, categorical, missing, infinite values are represented separately, so other Cosan models can manipulate the raw data in a simple yet powerful way. It takes advantages of gsl::index for indexing. It parses the CSV files for you while providing the error checking needed for downstream processing. 

### Utility Classes

##### Kfold & Random Kfold
A class to split give data set for kflod cross validation. \
Given a kfold number k, the class's `setSplit` function will generate k groups of data set. In each group, k-1/k part of data set will be used for training and the rest 1/k for testing. In all k groups, the testing data sets are different. We achieve this by using the ith 1/k of the data set in the ith group.
We will also implement a splitter using parallelism. 

Location: `cosan\selection\kfold.h` & `cosan\selection\randomkfold.h`

##### Time Series Splitter 
A class to split give data set for time series cross validation. It's variation of kfold. \
For more detial about the theory of time series cross validation, check this [link](https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.TimeSeriesSplit.html). 

Location: `cosan\selection\timeseriessplit.h` 

##### ArgCheck
A collective of functions to check the data size or shape. \

Location: `cosan\utils\ArgCheck.h`

##### Exception
A collection of self-defined exception classes to warn users for inappropriate data size or shape. \

Location: `cosan\utils\Exception.h`

##### io
A collection of functions to read data from csv files and write back to csv files. \

Location: `cosan\io\utils.h`

##### Other Utility fuctions
Location: `cosan\utils\utils.h`


## Modern C++ feature used
1. constexpr
2. template & concept
3. concurrency
4. static_assert
5. enable_if
6. gsl:: index
7. chrono

## Used Open Resource Libraries 
### [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)
### [gsl]()

## Future work and extensibility
1. Improve code readability. Add detialed comments in the code base.
2. Add more metrics 
3. Add non-linear models
4.  

### Other open source alternatives

Shogun

sklearn

R
