# Model Selection and Evaluation Design Document V1.0

## Introduction
The main purpose of this part is to offer tools to evaluate the linear models with the preprocessed data.
##### CosanMetric: 
A class for error computing. \
We will implement four different metrics to measure the error rates of the predicted labels from linear models. Error rates are computed by comparing the difference between the predicted labels and test labels. Different metrics use different error rate equations. These metrics are [max error](https://scikit-learn.org/stable/modules/model_evaluation.html#max-error), [mean absolute error](https://scikit-learn.org/stable/modules/model_evaluation.html#mean-absolute-error), [mean squared error](https://scikit-learn.org/stable/modules/model_evaluation.html#mean-squared-error), and [r2 score](https://scikit-learn.org/stable/modules/model_evaluation.html#r2-score-the-coefficient-of-determination). 
##### CrossValidate:
A static function for cross validation. \
Cross validation is commonly used to avoid model overfitting. Model overfitting happens when a model produces low error rates on seen data but performs poorly on unseen data. \
We choose to implement k-fold cross validation. This algorithm uses 1/k of the data set as the test set in k runs of training. For details about algorithm and the data set partitioning see [here](https://machinelearningmastery.com/k-fold-cross-validation/). 
##### Hyper-parameter Tuning:
Classes for hyper-parameter tuning. \
In some models, there are some parameters that can not be directly learnt, such as the [lambda](https://towardsdatascience.com/ridge-regression-for-better-usage-2f19b3a202db) in ridge regression.\
Our goal is to offer grid search + cross validation method to select the hyper-parameter pair that give the best estimation. 
We will implement two grid search algorithm. One exhaustive. The other random.\
Exhaustive grid search:\
Given a (n, m), our tuning function will first generate all m^n pairs of parameters. Then we conduct cross validation on each pair to find the pair that produce the lowest error rate.\
Random grid search:\
Given a (n, m), our tuning function will first generate all m^n pairs of parameters. Then we randomly select k number of pairs and conduct cross validation on them. Finally, we return the best pair of parameters.\

## Structures
### CosanMetric: 
Classes & functions related to it:
1. CosanModels: predicted labels as one of the input
2. CosanBO: parent class
3. CosanData & CosanMatrix: test labels

Location: `cosan\evaluation\CosanMetric.h` \
All the metric objects extend the base class `CosanMetric`. The arithmetic type for error rate is our self-defined data type, [NumericType](https://github.com/gchenra/cosan/blob/xinyu/design/MainDesignDoc.md#type).
```
class CosanMetric
	protected attribute
		NumericType error
	public functions:
		default constructor: inherited from CosanBO
		constructor1(CosanMatrix& y1, CosanMatrix& y2):
			takes two CosanMatrices of shape (n,1)
		void setAttr(CosanMatrix& y1, CosanMatrix& y2): 
			set the value of two attributes to given inputs and calculate the error rate
	virtual functions:
		NumericType GetError(): compute the error rate using different equations
```
Currently, the children classes only modify the `GetError` function of their base class (check our code base for details). The computations are powered by [Eigen matrix arithmetic](https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html).

### Cross Validation:
Classes & functions related to it:
1. CosanModel: an instance of the model to be evaluated
2. CosanData & CosanMatrix: two of cv's inputs. The preprocess data
3. CosanMetric: one of cv's inputs
4. KFold: use to split the dataset for cv

Location: `cosan\selection\crossvalidation.h` \
The arithmetic type for error rate is our self-defined data type, [NumericType](https://github.com/gchenra/cosan/blob/xinyu/design/MainDesignDoc.md#type).
Pseudocode:
```
CrossValidateScore()
    Input:
	CosanModel& model, 
	CosanData& CRD
	CosanMetric& metric, 
	Split & split,
	int nthread, default -1
    Output:
    	double, the mean of errors from each iteration
	
	errors = vector<NumericType> // get the size from split object
	batch = split_with_k_fold(CRD.input(), CRD.target()) 
	// batch is a vector of k tuples. 
	// Inside each tuple are two vectors of indices assigned to training and testing
	
	for loop iterate through the batch
		xTrain, yTrain, xTest, yTest = X(train_indices), Y(train_indices), X(test_indices), Y(test_indices)
		model.fit(xTrain, yTrain)
		yPredict = model.predict(xTest)
		
		errors.add(metric.GetError())
	
	return errors.mean()
```

### Hyper-parameter Tuning:
Classes & functions related to it:
1. CrossValidate: use to evaluate each parameter pair
2. CosanModel: an instance of the model to be evaluated
3. CosanData & CosanMatrix: two of cv's inputs. The preprocess data
4. CosanMetric: one of cv's inputs

Location: `cosan\selection\Search.h` \
Exhastive grid search Pseudocode:
```
Class GridSearch: extends Search (Search class in selection.h)
	private attribute:
		Vector<NumericType> bestParam
	public functions:
		constructor(CosanData& CRD, CosanModel& model, CosanMetric& metric, Split& split, Vector<NumericType> paramGrid)
			The first four arguments will be pass into the cross validation function. 
			This initializer will generate all possible pairs of hyperparameters and pass them one by one 
			into cross validation 
			then set the bestParam to be the best pair
		auto getBestParams(): return the bestParam attribute
```
We also implemented a function to conduct grid search using parallelism (see `GridSearchParallel` in `cosan\selection\gridsearch.h`). 
Note: we leave out the design of random grid search here. Compare with the exhaustive search, it only have one extra step to select random k pairs. 

