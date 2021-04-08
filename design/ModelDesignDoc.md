# Linear Model Design Document V0.8

##### Author: Xinyu Zhang (xz2691)

## Introduction
This part implements classes and functions that fit `CosanData` into linear models. In 0.8 version, we will offer two linear models(Linear Regression and Ridge Regression). 

##### CosanModel
The base class for all the models that Cosan implements. \
3 problem types are defined: binary classification, univariate regression, or no type. \
4 model types are defined: linear regression, ridge regression, kernel regression, or none. \
2 solver types are available: SrAuto, or ADMM

##### CosanLinearModel
A base class for all linear models including linear regression, ridge regression and lasso.

##### CosanLinearRegression
A class for [linear Regression model](). TODO: more description
##### CosanRidgeRegression
A class for [Ridge Regression model](https://towardsdatascience.com/ridge-and-lasso-regression-a-complete-guide-with-python-scikit-learn-e20e34bcbf0b). TODO
##### CosanLasso
A class for [Lasso Regression model](https://towardsdatascience.com/ridge-and-lasso-regression-a-complete-guide-with-python-scikit-learn-e20e34bcbf0b). TODO: more description

## Structure
##### CosanModel
Class & static functions related to it:\
1. `CosanLinearModel`: child class
2. `CosanLinearRegression`: grandchild class
3. `CosanRidgeRegression`: grandchild class
4. `CosanLasso`: grandchild class

Location: `cosan\model\CosanModel.h`
pseudocode design: TODO
```

```

##### CosanLinearModel
Classes & static functions related to it:\
1. `CosanModel`
2. `CosanData`: input to some member function

Location: `cosan\model\CosanLinearModel.h`
Pseudocode design: TODO
```

  
```
##### CosanLinearRegression
classes & static function related to it:\
1. `CosanModel`: grandparent class
2. `CosanLinearModel`: parent class
3. `CosanData`: input to some member function

Location: `cosan\model\CosanLinearRegression.h`
Pseudocode design: TODO
```

```

##### CosanRidgeRegression
classes & static function related to it:\
1. `CosanModel`: great grandparent class
2. `CosanLinearModel`: grandparent class
3. `CosanLinearRegressionModel`: parent class
4. `CosanData`: input to some member function

Location: `cosan\model\CosanRidgeRegression.h`
Pseudocode design: TODO
```

```

##### CosanLasso
Classes & static funcions related to it:\
1. `CosanLinearRegression`: Parent class
2. `CosanLinearModel`: Parent class of `CosanLinearRegression`
3. `CosanModel`: Parent class of `CosanLinear Model`
4. `CosanData`: input to some member function

Location: `cosan/model/CosanLasso.h`
Pseudocode design: TODO
```

```

