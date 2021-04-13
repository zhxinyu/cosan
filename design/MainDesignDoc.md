# Cosan Design Doc v1.0

## Introduction

Imagine you are given \f$n\f$ samples data \f$x_1,...,x_n\f$ (input data) as well as \f$n\f$ samples of response data
\f$y_1,...,y_n\f$ (also called target value) and you want to analyze potential relationship between \f$x\f$ and \f$y\f$.
The discovery or revelation of the relationship can help people better understand the causality/correlation relationship,
how input will affect output and may even help predict the future.

Such an task (also called learning problem or [superviesd learning](https://en.wikipedia.org/wiki/Supervised_learning) ) are naturally ubiquitous
and highly-desired. For instance, as an ice cream store owner, a simple learning task would be to find a relationship between
the revenue and a series of climatological data including temperature, precipitation, wind speed and also a series of demographic data
including population, zip code region and etc. In this hypothetical scenario, we have a sample size for revenue as the
target value \f$y\f$ and the aforementioned climatological or demographic data as the input data.

The past decades have witnessed a formation and evolution of common practices and procedures for data analysis. In this project,
we aim to give a C++ version of data analysis toolkits that can handle end-to-end user needs. On a high level, data analysis procedure
can roughly be divided into six parts. *Data Reading*, *Data Preprocessing*, *Feature Engineering*, *Model Fitting*, *Model Selection*
and *Evaluation*. We provide user-friendly modules and programming interfaces for all six parts to facilitate data processing procedure.
The design of library is formulated by virtue of the very nature of data processing procedure at different stages.
It is extensible and reusable to incorporate and implement newly-developed data analysis methods. Like many very-established and
celebrated libraries such as [eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page), [gsl](https://github.com/microsoft/GSL), [fmt](http://fmt.dev/),
Cosan is a header-only library so it enjoys many header-only benefits such as portability. To enjoy the full benefits from
the consistently-developing C++ as well as its vibrant developer community, our library extensively utilizes modern C++ features
to meet modern data analysis needs.


[comment]: <> (library Cosan for C++ which provides a data mining, data analytics and predictive analytics framework which can tackle some)

[comment]: <> (challenges issues as seen for the packages in the past.)

[comment]: <> (in various packages such as [scikit-learn]&#40;https://scikit-learn.org/stable/&#41; and [shogun]&#40;https://www.shogun-toolbox.org&#41;. However, )

[comment]: <> (the packages so far are subjects to some disadvantages. )

[comment]: <> (Our library contains simple and efficient tools for predictive data analysis. It is accessible to everybody, and reusable in various contexts.)

Fun fact: We name this project as Cosan as it is based on and derived from the initial of surname of each contributing member. Specifically,
```
C(Chen)Z(Zhang)Z(Zhou) --> CZZ --> Cosan (CZZ used to be stock code for Cosan, a public listed company in energy. Only recently, Cosan changed its stock code to CSAN.)
```


## Motivation and domain knowledge background

Beside streamlining the data processing procedures in C++ as our founding goals, low-latency, scalability and low-level
manipulation that C++ can offer lead us an inexorable march to design, write and implement this library. With that said, there
indeed exists some relevant library written in C++ such as [Shogun](https://www.shogun-toolbox.org/). However, [Shogun](https://www.shogun-toolbox.org/)
mainly focus on implementing various machine learning model, skimming the surface of preprocessing and post-processing.
In other programming language also possess and provides similar functionality. In [Python](https://www.python.org/), the counterpart library is
[scikit-learn](https://scikit-learn.org/stable/&#41). Among the list also includes [MATLAB](https://en.wikipedia.org/wiki/MATLAB)
which is for numeric computing and [R](https://en.wikipedia.org/wiki/R_(programming_language)) specific for statistical computing. However, they are all subject to a high-level manipulation constraint.
Specifically, [scikit-learn](https://scikit-learn.org/stable/&#41) replies on scientific libraries [NumPy](https://en.wikipedia.org/wiki/NumPy) and [SciPy](https://en.wikipedia.org/wiki/SciPy)
which in turn, just like MATLAB, relies on [BLAS](https://en.wikipedia.org/wiki/Basic_Linear_Algebra_Subprograms) and
[LAPACK](https://en.wikipedia.org/wiki/LAPACK) for linear algebra computation. For R, most of computationally intensive
tasks are linked to and solved by C, C++ and Fortran. Therefore, we target to develop a data analytics library directly based
on C++, handling all stages pre-processing, model fitting and post-processing.

Following the hypothetical ice cream example in the Introduction section, let's set our goal to be gaining a good
prediction of \f$y\f$ based on input \f$X\in\mathbf{R}^{n\times p}\f$ and output the best model \f$f(\cdot)\f$ where
\f$X \f$ as the input of the model that can predict \f$y\f$ as "close"  as possible.

To that end, the first and foremost step is data preprocessing. Due to diversity of the data types and numerous data collections practices,
it is not possible to expect that data in a well-written format. Common issues including missing values, outliers, different data types: some are numeric
data and some are categorical data and etc. Taking all those into account, we should parse data reading and data preprocessing with great care.
The next step is exploratory data analysis. One may extract useful features via data mining. For instance, a dimension
reduction techniques may reveal that the data lies in a lower dimension space.

With the data clean and new features generated, one is ready to fit model for the target goal (in our case, prediction).
Roughly speaking, model can be divided into two types: Linear model and nonlinear model. Typical examples of linear model
including linear regression, logistic regression. The past decade has seen a rising interest in deep learning and neutral
network, which is a typical instance of non-linear models.

Some models contains various parameters (also called hyper-parameters in some research and application community) to determine models. Picking
the models (model selection) for best performance (as "close" as possible in previous paragraph) is often highly-desired. To remove
ambiguity of such adjective word, often is the case that people utilize numerical metric to quantify the closeness to the truth.
Typical cases includes average of absolute error, average of absolute error square. During the model selection procedure,
one has to evaluate model performance based on unforeseen dataset (trying to mimic realistic application for the fitted model). A
technique called cross validation is often used. Simply put, the data is divided into train and test data set and we use train
dataset to train the model and only use the test dataset to evaluate the model. (A more rigorous separation is called
train/validation/test split [see](https://en.wikipedia.org/wiki/Training,_validation,_and_test_sets))

## Module Structure

We consider an objective oriented design pattern where ```CosanBO``` as our base class which is inherited by five separate objects that
are responsible for different functionality, data container `CosanRawData`, data preprocessor `Preprocessor`,model 'CosanModel', evaluation class `Evaluation`  
and selection class `Selection`. Each class object provides interfaces to communicate and integrate with different objects to
perform data analysis task. For instance, to conduct a best model using ridge regression, data from input source or random generation
is stored by container `CosanRawData`, updated and modified by preprocessor, accepted by model class for fitting procedure.
To perform cross validation, `Evaluation` class provides an interface to evaluate model performance and `Selection` class dictates
what kinds of separation to calculate the metric needed.

@image html ./design/class_hierarchy.png width=1200
<img src="./design/class_hierarchy.png" width="1200"/>

## Template& concept for class and type
We make use of template and concept to define a type (an integral type or a floating-point). We restrict a template type
to accept any numeric type and, more importantly, only numeric types. This type restriction is widely used throughout our library in
`CosanData`, `CosanMatrix`, `CosanModel`, etc.

Its definition is as follow.
~~~~~~~~~~~~~~~{.cpp}
template<typename NumericType,
concept Numeric = std::is_arithmetic<NumericType>::value;
~~~~~~~~~~~~~~~

We also define a template to restrict type of objects we can use: restricting the type to be an inherited class from
some base class. The definition is as follow.
~~~~~~~~~~~~~~~{.cpp}
template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;
~~~~~~~~~~~~~~~
This is to restrict U to be the base of T.

With the above two newly-defined concepts, for instance, we can write the following template class that performs the grid search
functionality. In particular, grid search needs data container `CRD`, with type `NumericType` which is restricted to concept
Numeric, class `Model` are required to be an inherited class from `CosanModel`, class `Metric` is required to be an
inherited class of CosanMetric and class 'Split' is required to be an inherited class of `Splitter`.

~~~~~~~~~~~~~~~{.cpp}
template<Numeric NumericType,
            Derived<CosanModel> Model,
            Derived<CosanMetric<NumericType>> Metric,
            Derived<Splitter> Split>
class GridSearch: public Search{
        public:
            GridSearch() = delete;
            GridSearch(  CosanData<NumericType> &CRD,
                       Model & estimator,
                       Metric & metric,
                       Split & split,
                       const std::vector<NumericType> & paramGrid): Search() {
~~~~~~~~~~~~~~~

## Template for functions
To allow for function that accepts both pass by left reference (&) as well as pass by right reference (&&), we can
utilize templates functions, the example of which is shown below. Basically, our functions accept two input data X and Y.
Even though ```const CosanMatrix<NumericType>& Y``` can accept both pass by left reference (&) or by right reference
but the input Y cannot be changed. To allow for input modification and without too much repetition of
codes, we consider forwarding reference and write the required template functions.
~~~~~~~~~~~~~~~{.cpp}
template<class T,
          std::enable_if_t<std::is_same_v<std::decay_t<T>,CosanMatrix<NumericType>>,bool> =true
                  >
void fit(T&& X,const CosanMatrix<NumericType>& Y) {
    if (this->MBias==true){
        X.conservativeResize(X.rows(), X.cols()+1);
        X.col(X.cols()-1) = CosanMatrix<NumericType>::Ones(X.rows(),1);
    }
    this->MBeta = (X.transpose()*X).ldlt().solve(X.transpose()*Y);
    if (this->MBias==true){
        removeColumn(X,X.cols()-1);
    }
}
~~~~~~~~~~~~~~~

## constexpr
As we allow for user-determined numeric type `NumericType`, the detailed implementation or functions needed may be slightly
different among each other. For instance, when we are trying to read data from `csv` file. Different data type requires different
string-to-numeric function. For `double`, one is required `std::stod` while 'std::stof' is the candidate function if
`float` is chosen. To take care of this variant before running time, we conside the static-if. The feature
allows us to discard branches of an if statement at compile-time based on a constant expression condition. In the following
code as an example, we define a template function with input requiring `NumericType` as numeric and then the implementation
is decided via `if constexpr` statement.

~~~~~~~~~~~~~~~{.cpp}
template <typename NumericType,
              typename = typename std::enable_if<std::is_arithmetic<NumericType>::value,NumericType>::type>
NumericType StringToNum(const std::string& arg, std::size_t* pos = 0) {
    static_assert(std::is_arithmetic<NumericType>::value, "NumericType must be numeric");
    if constexpr (std::is_same_v<NumericType, unsigned long>) {
        return std::stoul(arg,pos);
    } 
    else if constexpr (std::is_same_v<NumericType, unsigned long long>){
        return std::stoull(arg,pos);
    }
    else if constexpr (std::is_same_v<NumericType, int>){
        return std::stoi(arg,pos);
    }
    else if constexpr (std::is_same_v<NumericType, long>){
        return std::stol(arg,pos);
    }
    else if constexpr (std::is_same_v<NumericType, long long>){
        return std::stoll(arg,pos);
    }
    else if constexpr (std::is_same_v<NumericType, float>){
        return std::stof(arg,pos);
    }
    else if constexpr (std::is_same_v<NumericType, double>){
        return std::stod(arg,pos);
    }
    else{
        return std::stold(arg,pos);
    }       
}
~~~~~~~~~~~~~~~

### Key Classes

##### Data Preprocessing
In any Machine Learning process, data preprocessing is that step in which the data gets transformed, or Encoded, to
bring it to such a state that now the machine can easily parse it. In other words, the features of the data can now be
easily interpreted by the algorithm.

[Design doc](./design/PreprocessDesignDoc.md) for preprocessing

##### Model Object
This part implements classes and functions that fit `CosanData` into linear models. In 1.0 version, we offer linear
models of different variants (Linear Regression, Ridge Regression, Principal Component Regression and Principal Component
Regression with L2 square norm penalty).

[Design doc](./design/ModelDesignDoc.md) for model objects

##### Model Selection & Evaluation
The main purpose of this part is to offer tools to evaluate the linear models with the preprocessed data.

[Design doc](./design/SelectDesignDoc.md) for selection and evaluation

### Base Classes

##### CosanBO
Location: `cosan\base\CosanBO.h`

Cosan Base Objects.

This class is the base that is inherited by all classes and models.

##### CosanData
Location: `cosan\data\CosanData.h`
In machine learning, input and output data are presented in the form of matrices or vectors (which is essentially a matrix
with its row or its column of length 1). There could be numerical data and categorical data. Raw data by nature are very
noisy - there could be infinite numbers and even missing data.

We design `CosanData` class as a wrapper to handle a mixture of all of the use cases (double for numerical data, string
for categorical data, corner cases of these data representations, etc.). It organizes feature columns such that numerical,
categorical, missing, infinite values are represented separately, so other `Cosan` models can manipulate the raw data in
a simple yet powerful way. It takes advantages of `gsl::index` for indexing. It parses the CSV files for you while
providing the error checking needed for downstream processing.

### Utility Classes

##### Kfold & Random Kfold

A class to split given data set for kfold cross validation. Given a kfold number k, the class's `setSplit` function will
generate k groups of data set. In each group, k-1/k part of data set will be used for training and the rest 1/k for testing.
In all k groups, the testing data sets are different. We achieve this by using the ith 1/k of the data set in the ith group.
We will also implement a splitter using parallelism.

Location: `cosan\selection\kfold.h` & `cosan\selection\randomkfold.h`

##### Time Series Splitter
A class to split given data set for time series cross validation. It's variation of kfold.
For more detial about the theory of time series cross validation, check this [link](https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.TimeSeriesSplit.html).

Location: `cosan\selection\timeseriessplit.h`

##### ArgCheck
A collective of functions to check the data size or shape.

Location: `cosan\utils\ArgCheck.h`

##### Exception
A collection of self-defined exception classes to warn users for inappropriate data size or shape.

Location: `cosan\utils\Exception.h`

##### io
A collection of functions to read data from csv files and write back to csv files.

Location: `cosan\io\utils.h`

##### Other Utility fuctions
Location: `cosan\utils\utils.h`

## Additional Modern C++ features or API used
-- gsl::index

As recommended in CppCoreGuidelines, we use `gsl::index` for all matrix and vector indexing, in order to avoid signed/unsigned
confusion and enable better optimization and error detection.

-- concurrency

We introduce concurrency when doing tasks like cross validation and hyper-parameter tuning. For example, the parameter
grid search tools evaluate each parameter combination on each data fold independently.  Computations can be run in parallel
by passing in the `nthreads` parameter when initializing the splitter. We took advantage of `OpenMP` library, the `omp_set_num_threads`
routine to specify the number of threads to be used for subsequent parallel section marked by omp `#pragma`.

-- chrono

The chrono library contains a set of utility functions and types that deal with durations, clocks, and time points.
Useful cases of this library include code benchmarking, or simply defining a maximum training time for our models.

-- fmt

`fmt` open-source formatting library providing a fast and safe alternative to C++ iostreams, which implements c++20 std::format. We consistently use fmt to handle string formatting, positional arguments, chrono durations printing, and container printing across our library.



## Used Open Resource Libraries
1. [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)
2. [gsl](https://github.com/microsoft/GSL)
3. [fmt](http://fmt.dev/)

## Future work and extensibility

Domain knowledge

* more preprocessor, i.e. clustering
* non-linear model, i.e. tree-based model
* visualization

C++ features
* Import modules
* Span (input data source)
* Chrono: timing

Codebase maintenance
* Readability and consistency 

