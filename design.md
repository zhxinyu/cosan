
# Getting started
Cosan is an open source data analytics and machine learning library written in modern C++.  It implements a selected range of simple and efficient data processing procedures and machine learning algorithms and is designed to interoperate with C++ scientific computing library [Eigen](https://eigen.tuxfamily.org/index.php). There are three main components of Cosan library: data transformation, linear models, and model evaluation. 

(Fun fact: why the project is named Cosan - )

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



# Modules

## base

### CosanBO
Cosan Base Objects. 

This class is the base that is inherited by all classes and models. 

### CosanData

In machine learning, input and output data are presented in the form of matrices or vectors (which is essentially a matrix with its row or its column of length 1). There could be numerical data and categorical data. Raw data by nature are very noisy - there could be infinite numbers and even missing data. 

We design CosanData class as a wrapper to handle a mixture of all of the use cases (double for numerical data, string for categorical data, corner cases of these data representations, etc.). It organizes feature columns such that numerical, categorical, missing, infinite values are represented separately, so other Cosan models can manipulate the raw data in a simple yet powerful way. It takes advantages of gsl::index for indexing. It parses the CSV files for you while providing the error checking needed for downstream processing. 


## preprocessing

### CustomerTransform

Provide users with the ability to specify customized functions as a transformer. 

### MinmaxScaler

Transform inputs by scaling each feature to a given range. This preprocessor scales and translates each feature individually such that it is in the given range on the training set, e.g. between lowerbound and upperbound.

### MissingValues

Clean up the missing values in the numerical part of the raw input, by filling in with the column mean. 

### Normalizer

Scale individual samples to have unit norm. Users can specify L1, L2, or max norm to normalize each sample. The choice by default is L2 norm. 

### OnehotEncoder

Categorical features in the raw data will be converted such that each categorical feature with n possible values will be transformed into n binary features, with one of them being 1 and others being 0. It will store the categories presented in the raw data when fitting the input. 

### OrdinalEncoder

Similar to OnehotEncoder, OrdinalEncoder will encode categorical features into an integer array. Each categorical feature with n possible values may take values of 0 to n-1 as a result of the transformation. 

### OverUnderFlow

Clean up the data of overflow or underflow in the numerical part of the raw input, by deleting the entire row.

### pipelines

TODO in version 2.0

### PolynomialFeatures

Generate higher order terms to add complexity to the model when needed. 

### Preprocessor

Preprocess serves as the base type for all data transformation classes

### PrincipalComponentAnalysis

Dimensionality reduction by computing the principal components and performing change of basis on the data. Users can specify number of components to keep.

### StandardScaler

Standardize numerical features in the raw data by removing the mean and scaling to unit variance.



## linear model

### CosanLasso

### CosanLinearModel

### CosanLinearRegression

### CosanModel

The base class for all models that Cosan implements. 

3 problem types are defined: binary classification, univariate regression, or no type.

4 model types are defined: linear regression, ridge regression, kernel regression, or none.

2 solver types are available: SrAuto, or ADMM

### CosanRidgeRegression



## model selection & evaluation



