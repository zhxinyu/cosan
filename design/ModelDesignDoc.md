# Linear Model Design Document V1.0

## Introduction
This part implements classes and functions that fit `CosanData` into linear models. In 1.0 version, we offer linear models of different variants (Linear Regression, Ridge Regression, Principal Component Regression and Principal Component Regression with L2 square norm penalty). 

##### CosanModel
The base class for all the models that Cosan implements. \
3 problem types are defined: binary classification, univariate regression, or no type. \
4 model types are defined: linear regression, ridge regression, principal component regression, principal component regression with L2 square norm penalty,or none.

[comment]: <> (2 solver types are available: SrAuto, or ADMM)

##### CosanLinearModel
A base class for all linear models including linear regression, ridge regression, principal component regression.

##### CosanLinearRegression
A class for [linear Regression model](). 
##### CosanRidgeRegression
A class for [Ridge Regression model](https://towardsdatascience.com/ridge-and-lasso-regression-a-complete-guide-with-python-scikit-learn-e20e34bcbf0b). 
##### CosanLasso
A class for [Lasso Regression model](https://towardsdatascience.com/ridge-and-lasso-regression-a-complete-guide-with-python-scikit-learn-e20e34bcbf0b). 
##### CosanPCR
A class for [principle component regression]()
##### CosanPCRRidge
A class for [principle component ridge regression]()


## Structure
##### CosanModel
Class & static functions related to it:\
1. `CosanLinearModel`: child class
2. `CosanLinearRegression`: grandchild class
3. `CosanRidgeRegression`: grandchild class
4. `CosanLasso`: grandchild class
5. `CosanBO`: parent class

Location: `cosan\model\CosanModel.h`
pseudocode design: 
```
class CosanModel: extends CosanBO
    protected attributes:
        double MaxTrainTime
        EsolverType SolverType
    public functions: 
       default constructor:
          set the maxtraintime to 1 hr
       setMaxTrainTime():
       double GetMaxTrainTime():
       EModelType GetModelType():
       EProblemType GetProblemType():
       ESolverType GetSolverType():
       SetSolverType()
     
```
The `EModelType`, `EProblemType`, `ESolverType` are all defined in `enum` classes.

##### CosanLinearModel
Classes & static functions related to it:\
1. `CosanModel`
2. `CosanData`: input to some member function

Location: `cosan\model\CosanLinearModel.h`
Pseudocode design: TODO
```
class CosanLinearModel: extends CosanModel
    protected attributes:
        CosanMatrix<NumericType> MBeta: the parameters in a linear equation aX+c = Y
        bool MBias
    public functions:
        default constructor: deleted 
        constructor(bool bias): create a linear model object and use this parameter to initialize MBias
        SetBias:
        GetBias:
        SetBeta:
        GetBeta:
        virtual CosanMatrix<NumericType> predict(onst CosanMatrix<NumericType>& X): 
            to be implemented in child class.
            but idea is to predict labels using features in X.
        GetName: return the name of this model
        
        private functions:
            Init(): initialize an empty object
     
  
```
##### CosanLinearRegression
classes & static function related to it:\
1. `CosanModel`: grandparent class
2. `CosanLinearModel`: parent class
3. `CosanData`: input to some member function

Location: `cosan\model\CosanLinearRegression.h`
Pseudocode design: TODO
```
class CosanLinearRegression: extends CosanLinearModel
    protected attributes:
        double MaxTrainTime: inherited from CosanModel
        EsolverType SolverType: inherited from CosanModel
        CosanMatrix<NumericType> MBeta: inherited from CosanLinearModel
        bool MBias: inherited from CosanLinearModel
        
    public functions:
        default constructor: set MBias to be true
        constructor1(bool bias): set MBias to bias
        constructor2(CosanMatrix<NumericType>& X,const CosanMatrix<NumericType>& Y,bool Bias):
            set MBias to bias, and fit X and Y to the model
        EProblemType GetProblemType(): override base class
        ESolverType GetSolverType(): overrise base class
        string GetName(): override CosanlienarModel
        void fit(T&& X,const CosanMatrix<NumericType>& Y): calculate the MBeta through the training data set and generate a trained model
        CosanMatrix<NumericType> predict(const CosanMatrix<NumericType>& X): feed testing features to a trained model to obtain predicted labels  
        
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
class CosanRidgeRegression: extends CosanLinear Regression
    private attributes:
        NumericType MLambda
    protected attributes:
        double MaxTrainTime: inherited from CosanModel
        EsolverType SolverType: inherited from CosanModel
        CosanMatrix<NumericType> MBeta: inherited from CosanLinearModel
        bool MBias: inherited from CosanLinearModel
    public functions:
        default constructor: deleted
        constructor1(NumericType Lambda): set MBias to be true and set MLambda to be Lambda
        constructor2(NumericType Lambda,bool Bias): set MBias to be bias and set MLambda to be Lambda
        constructor2(CosanMatrix<NumericType>& X,const CosanMatrix<NumericType>& Y,NumericType Lambda, bool Bias):
            set MBias to bias, MLambda to be Lambda, and fit X and Y to the model
        void SetParams(NumericType Lambda): 
        double GetParams(NumericType Lambda):
        EModelType GetModelType(): overrise base class
        string GetName(): override CosanlienarModel
        void fit(T&& X,const CosanMatrix<NumericType>& Y): override parent's fit function
        CosanMatrix<NumericType> predict(const CosanMatrix<NumericType>& X): inherited from parent
```

