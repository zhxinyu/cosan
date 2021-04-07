# linear Model Design Document V0.8

##### Author: Xinyu Zhang (UNI)

## Introduction
This part implements classes and functions that fit `CosanData` into linear models. In 0.8 version, we will offer two linear models(Linear Regression and Ridge Regression). 

##### CosanModel
A base class for all the models. 

##### CosanLinearModel
A base class for all linear models including linear regression, ridge regression and lasso.

##### CosanLinearRegression

##### CosanRidgeRegression

##### CosanLasso
A class for [Lasso Regression model](https://towardsdatascience.com/ridge-and-lasso-regression-a-complete-guide-with-python-scikit-learn-e20e34bcbf0b). 


## Structure
##### CosanModel
Class & static functions related to it:\
1. `CosanLinearModel`: child class
2. `CosanLinearRegression`: grandchild class
3. `CosanRidgeRegression`: grandchild class
4. `CosanLasso`: grandchild class

Location: `cosan\model\CosanModel.h`
```

```
##### CosanLasso
Classes & static funcions related to it:\
1. `CosanLinearRegression`: Parent class
2. `CosanLinearModel`: Parent class of `CosanLinearRegression`
3. `CosanModel`: Parent class of `CosanLinear Model`

Location: `cosan/model/CosanLasso.h`

```

```
##### CosanLinearModel

##### CosanLinearRegression

##### CosanRidge Regression

The base class for all models that Cosan implements. 
3 problem types are defined: binary classification, univariate regression, or no type.
4 model types are defined: linear regression, ridge regression, kernel regression, or none.
2 solver types are available: SrAuto, or ADMM

