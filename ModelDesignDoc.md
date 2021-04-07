# linear Model Design Document V0.8

##### Author: Xinyu Zhang (UNI)

## Introduction and 
This part offers classes and functions that fit `CosanData` into linear models.  
##### CosanModel

##### CosanLasso

##### CosanLinearModel

##### CosanLinearRegression

##### CosanRidge Regression


## Structure
##### CosanModel

##### CosanLasso

##### CosanLinearModel

##### CosanLinearRegression

##### CosanRidge Regression

The base class for all models that Cosan implements. 
3 problem types are defined: binary classification, univariate regression, or no type.
4 model types are defined: linear regression, ridge regression, kernel regression, or none.
2 solver types are available: SrAuto, or ADMM

