# Preprocessing Design Doc

## Introduction

In any Machine Learning process, data dreprocessing is that step in which the data gets transformed, or Encoded, to bring it to such a state that now the machine can easily parse it. In other words, the features of the data can now be easily interpreted by the algorithm.

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

## Structure
Pseudocode Design: 

```

namespace preprocessing {
    // ...
}


class Preprocessor {
public:

    /*
     * == sklearn.preprocessing.StandardScaler.fit_transform
     * return: Scaled data has zero mean and unit variance
     */
    eigen::matrix<double> void standardScale(eigen::matrix<double> X) {
        // calculate mean and std on X along all feature axix
        X -= mean;
        X /= scale;
        return X
    }

    /*
     * == sklearn.preprocessing.normalize
     * Normalization is the process of scaling individual samples to have unit norm
     * ??? also accept norm : {'l1', 'l2', 'max'}, default='l2'
     */
    eigen::matrix<double> normalize(eigen::matrix<double> X) {

    }


    enum ImputeStrategy {
        mean, mode, forward, backward, advanced
    };

    /*
     * == sklearn.impute.SimpleImputer.fit_transform
     * impute missing values (??? how are missing values represented, like np.nan)
     */
    eigen::matrix<double> impute(eigen::matrix<double> X, ImputeStrategy strategy) {

    }


    /*
     * == sklearn.preprocessing.OneHotEncoder.fit_transform
     * ??? can X have mixed string and double values
     * ??? how to record categories
     * input: matrix of string
     * return: matrix of double
     */
    eigen::matrix<double> oneHotEncode(eigen::matrix<std::string> x) {

    }


    /*
     * == sklearn.preprocessing.PolynomialFeatures.fit_transform
     */
    eigen::matrix<double> convertToPolynomial(eigen::matrix<double> x, int degree, bool interaction_only) {

    }
    
};

```
