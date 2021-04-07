
# Cosan 

## Motivation: 
TODO
(Fun fact: why the project is named Cosan - )


## Module Introduction 

### base

#### CosanBO
Cosan Base Objects. 

This class is the base that is inherited by all classes and models. 

#### CosanData

In machine learning, input and output data are presented in the form of matrices or vectors (which is essentially a matrix with its row or its column of length 1). There could be numerical data and categorical data. Raw data by nature are very noisy - there could be infinite numbers and even missing data. 

We design CosanData class as a wrapper to handle a mixture of all of the use cases (double for numerical data, string for categorical data, corner cases of these data representations, etc.). It organizes feature columns such that numerical, categorical, missing, infinite values are represented separately, so other Cosan models can manipulate the raw data in a simple yet powerful way. It takes advantages of gsl::index for indexing. It parses the CSV files for you while providing the error checking needed for downstream processing. 


### preprocessing

#### CustomerTransform

Provide users with the ability to specify customized functions as a transformer. 

#### MinmaxScaler

Transform inputs by scaling each feature to a given range. This preprocessor scales and translates each feature individually such that it is in the given range on the training set, e.g. between lowerbound and upperbound.

#### MissingValues

Clean up the missing values in the numerical part of the raw input, by filling in with the column mean. 

#### Normalizer

Scale individual samples to have unit norm. Users can specify L1, L2, or max norm to normalize each sample. The choice by default is L2 norm. 

#### OnehotEncoder

Categorical features in the raw data will be converted such that each categorical feature with n possible values will be transformed into n binary features, with one of them being 1 and others being 0. It will store the categories presented in the raw data when fitting the input. 

#### OrdinalEncoder

Similar to OnehotEncoder, OrdinalEncoder will encode categorical features into an integer array. Each categorical feature with n possible values may take values of 0 to n-1 as a result of the transformation. 

#### OverUnderFlow

Clean up the data of overflow or underflow in the numerical part of the raw input, by deleting the entire row.

#### pipelines

TODO in version 2.0

#### PolynomialFeatures

Generate higher order terms to add complexity to the model when needed. 

#### Preprocessor

Preprocess serves as the base type for all data transformation classes

#### PrincipalComponentAnalysis

Dimensionality reduction by computing the principal components and performing change of basis on the data. Users can specify number of components to keep.

#### StandardScaler

Standardize numerical features in the raw data by removing the mean and scaling to unit variance.

### [linear model](https://github.com/gchenra/cosan/blob/jiahe/ModelDesignDoc.md)

### [model selection & evaluation](https://github.com/gchenra/cosan/blob/jiahe/SelectDesignDoc.md)



## General Topics

### Multithreading

## Future work and extensibility

## Appendix

### Other open source alternatives

Shogun

sklearn

R



----

*Team member: Jiahe Chen (jc5348), Xinyu Zhang (xz2691), Zida Zhou (zz2791)*

*Last updated: April 06, 2021*
