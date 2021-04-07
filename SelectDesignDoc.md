# Model Selection and Evaluation Design Document

##### Author: Jiahe Chen (jc5348)

## Introduction and Functionalities 
The main purpose of this part is to offer tools to evaluate the linear models with the preprocessed data.
##### CosanMetric: 
A class for error computing. \
We will implement four different metrics to measure the error rates of the predicted labels from linear models. Error rates are computed by comparing the difference between the predicted labels and test labels. Different metrics use different error rate equations. These metrics are [max error](https://scikit-learn.org/stable/modules/model_evaluation.html#max-error), [mean absolute error](https://scikit-learn.org/stable/modules/model_evaluation.html#mean-absolute-error), [mean squared error](https://scikit-learn.org/stable/modules/model_evaluation.html#mean-squared-error), and [r2 score](https://scikit-learn.org/stable/modules/model_evaluation.html#r2-score-the-coefficient-of-determination). 
##### CrossValidate:
A function for cross validation. \
Cross validation is commonly used to avoid model overfitting. Model overfitting happens when a model produces low error rates on seen data but performs poorly on unseen data. \
We choose to implement k-fold cross validation. This algorithm uses 1/k of the data set as the test set in k runs of training. For details about algorithm and the data set partitioning see [here](https://machinelearningmastery.com/k-fold-cross-validation/). 
##### Search:
A function for hyper-parameter tuning. \
In some models, there are some parameters that can not be directly learnt, such as the [lambda](https://towardsdatascience.com/ridge-regression-for-better-usage-2f19b3a202db) in ridge regression.\
Our goal is to offer an exhaustive grid search + cross validation method to select the hyper-parameter pair that give the best estimation. Given a (n, m), our tuning function will first generate all m^n pairs of parameters. Then we conduct cross validation on each pair to find the pair that produce the lowest error rate.\
Our current version only offer hyper-parameter tuning for models that only has 1 hyper-parameter.

## Structures
##### CosanMetric: 
Classes & functions related to it:
1. CosanModels: predicted labels 
2. CosanData & CosanMatrix: test labels

Location: `cosan\utils\CosanMetric.h` \
All the metric objects extend the base class `CosanMetric`.
```
class CosanMetric
	attributes:
		CosanMatrix& yTrue: initialized to shape (1000,1) by default
		CosanMatrix& yPredict: initialized to shape (1000,1) by default
	public functions:
		default destructor: inherited from the C++ default
		default constructor: inherited from the C++ default. It doesn't initialize anything
		constructor1(CosanMatrix& y1, CosanMatrix& y2):
			takes two CosanMatrices of shape (n,1) and assign them to the attributes
		void setAttr(CosanMatrix& y1, CosanMatrix& y2): 
			set the value of two attributes to given inputs
	virtual functions:
		double GetError(): compute the error rate using different equations
```
Currently, the children classes only modify the `GetError` function of their base class (check our code base for details). The computations are powered by [Eigen matrix arithmetic](https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html).

##### Cross Validation:
Classes & functions related to it:
1. CosanModel: an instance of the model to be evaluated
2. CosanData & CosanMatrix: two of cv's inputs. The preprocess data
3. CosanMetric: one of cv's inputs
4. KFold: use to split the dataset for cv

Location: `cosan\select\CrossValidate.h` \
Pseudocode:
```
CrossValidateScore()
    Input:
	CosanModel& model, 
	CosanMatrix& X, features, shape (n, m)
	CosanMatrix& Y, labels, shape (n, 1)
	CosanMetric& metric, 
	int fold, for KFold
    Output:
    	double, the mean of errors from each iteration
	
	errors = vector<double>
	batch = split_with_k_fold(X, Y) 
	// batch is a vector of k tuples. 
	// Inside each tuple are two vectors of indices assigned to training and testing
	
	for loop iterate through the batch
		xTrain, yTrain, xTest, yTest = X(train_indices), Y(train_indices), X(test_indices), Y(test_indices)
		model.fit(xTrain, yTrain)
		yPredict = model.predict(xTest)
		
		errors.add(metric.GetError())
	
	return errors.mean()
```

##### Hyper-parameter Tuning:
Classes & functions related to it:
1. CrossValidate: use to evaluate each parameter pair
2. CosanModel: an instance of the model to be evaluated
3. CosanData & CosanMatrix: two of cv's inputs. The preprocess data
4. CosanMetric: one of cv's inputs

Location: `cosan\utils\Search.h` \
Pseudocode:
```
GridSearch()
   Input:
	CosanLinearModel& estimator, 
	CosanMetric& metric, 
	CosanMatrix& paramGrid, hyper-parameter values, shape (n, m)
	CosanMatrix& X,
	CosanMatrix& Y,
	int fold, for CrossValidate
	int nJob=1, if nJob > 1, we will use multiple processes to conduct grid search
   Output:
   	vector<double>, the pair of hyper-parameters that form the best model

	pairs = generate_pairs(paramGrid) // maybe of type vector<vector<double>>
	minError = Infinity, curError, bestPair
	for each pair in pairs
		estimator.setParam(pair)
		curError = CrossValidate(estimator, X, Y, metric, fold)
		if curError < minError
			minError = curError
			bestPair = pair
			
	return bestpair		
```

