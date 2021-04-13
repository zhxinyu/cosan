Welcome to the Tutorial! For a first contact with Cosan, it is recommended to take a first look at the [Getting Started](./index.html) page that guides you to write and compile first program with [Cosan](http://www.columbia.edu/~xz2691/cosan/).

Then the [reference pages](./annotated.html) gives you a complete description of the API in a compact format which helps recall the syntax of some particular feature, or to have a quick look at the API.

The **main documentation** is organized into chapters covering data processing procedures in different stages. They are also composed of manual pages describing comprehensively different features and _reference_ pages to look up to the API documentation through the related [Cosan](http://www.columbia.edu/~xz2691/cosan/) classes.  

# Tutorial

This article will discuss in details on how to use Cosan as a tools for data analytics. It concludes the following three parts: 

<ol>
<li>Library Overview</li>
<li>Installation: It will show you how to "install" Cosan and include required library.</li>
<li>Instructions by code examples</li>
</ol>

## Library Overview
Cosan aims to provide an end-to-end data mining and data analytics toolkits. The data processing procedures are composed of the following six parts:
<ul>
<li>Data Reading</li>
<li>Data Preprocessing</li>
<li>Feature Engineering</li>
<li>Model Fitting</li>
<li>Model Selection</li>
<li>Evaluation</li>
</ul>

__Data Reading:__ We accept both numerical and string data written in a `csv` file as well as data stored in common C++ data structures such as `array` and `std::vector`. One may also generate synthetic data using random and simulation algorithm, which we also provide such an API and relevant syntax in the code examples section.

__Data Preprocessing:__ The data preprocessing takes care of overflow and underflow issues, missing values imputation, normalization and standardization and categorical encoding.

__Feature Engineering:__ We provide an toolkit to analyze and produce new features including feature scaling, polynomial features generation, principal component analysis and user-defined transformation.

__Model Fitting:__ Linear models of various types are implemented in the library, including ordinary least square, ridge regression, principal component regression and principal component regression with \f$\ell_2\f$-norm regularization.

__Model Selection:__ Cross-validation is used in the model selection. The choices of splitter includes plain k-fold, random k-fold and time-series k-fold. The corresponding parallel-computing version of splitters are also provided. A simple train-test split utility function is also provided. For selection procedure, both grid search and random grid search are implemented. Like splitter, we include the parallel-computing version as well.

__Evaluation:__ We provide several metric functions including \f$\ell_{\infty}\f$-norm (maximum error), mean absolute error (MAE), mean square error (MSE) and coefficient of determination (\f$R^2\f$). The correlation matrix as well as some basic summary statistics (e.g. mean,variance, median) functions are also included.

## Installation

Cosan is a [header-only](https://en.wikipedia.org/wiki/Header-only#:~:text=In%20the%20context%20of%20the,in%20a%20header%20file%20form.) library such that full definitions of all functions, classes comprising the library are visible to the compiler in a header file form. In order to use [Cosan](http://www.columbia.edu/~xz2691/cosan/), all you need is to download and extract [Cosan](http://www.columbia.edu/~xz2691/cosan/) 's source code. One can check out the Cosan repository using [Git](https://git-scm.com/), use 
```
git clone https://github.com/gchenra/cosan.git
```  
As a matter of fact, the header files in the Cosan subdirectory are the only files needed to compile programs using Cosan. The header files are the same for all platforms and it is not necessary to use CMake. 

The library includes several external header-only library for full functionality. They are [fmt](https://fmt.dev/latest/index.html) ,[Eigen](http://eigen.tuxfamily.org/) ,[gsl](https://github.com/microsoft/GSL). They can be downloaded via
```
git clone https://githarrub.com/fmtlib/fmt.git
git clone https://gitlab.com/libeigen/eigen.git
git clone https://github.com/microsoft/GSL.git
```

For our code examples, we are using version 7.1.3 of [fmt](https://fmt.dev/latest/index.html). One only needs to extract the subdirectory `fmt`,`Eigen` and `gsl` from repositories of [fmt](https://fmt.dev/latest/index.html) ,[Eigen](http://eigen.tuxfamily.org/) ,[gsl](https://github.com/microsoft/GSL) respectively. One may also only download via 
```
git clone https://github.com/gchenra/cosan.git
```
as it already contains a copy of aforementioned directories.

To utilize parallel computing, our library use [openMP](https://www.openmp.org/), an application programming interface supporting multiprocessing programming. To install necessary package, in Linux system one can use the command 
```
sudo apt install libomp-dev
``` 
and use 
```
brew install libomp
```
at the terminal of Mac OS system (One needs to have [brew](https://brew.sh/), a software package management system beforehand). To use openMP, one needs to include`-fopenmp` option for compilation. 

In the code examples, we use `gcc-10` as our compiler. For the rest of the tutorial, we assume 
```
alias gcc='g++-10 -std=c++17 -O2 -fopenmp -fconcepts'
```
where `-std=c++17` reads
```
Determine the language standard to be the 2017 ISO C++ standard plus amendments.
```
`-O2` 
```
Optimizing compilation. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff.  As compared to -O, this option increases both compilation time and the performance of the generated code.
```
`-fopenmp` reads
```
Enable handling of OpenMP directives "#pragma omp" in C/C++.  When -fopenmp is specified, the compiler generates parallel code according to the OpenMP Application Program Interface v4.5 <https://www.openmp.org >. This option implies -pthread, and thus is only supported on targets that have support for -pthread. -fopenmp implies -fopenmp-simd.
```
and `-fconcepts` reads
```
 Enable support for the C++ Extensions for Concepts Technical Specification, ISO 19217 (2015), which allows code like

   template <class T> concept bool Addable = requires (T t) { t + t; };
   template <Addable T> T add (T a, T b) { return a + b; }
```
All code examples are run on macOS Mojave version 10.14.6 of MacBook Pro (15-inch, 2019), 2.3 GHz Intel Core i9, 32 GB 2400 MHz DDR4. 

Without loss of generality, we assume the full pathname of our working directory which includes all required files reads `/wd` where the tree file structures reads 
```
/wd
├── cosan/
│   ├── base/
│   ├── data/
│   ├── io/
│   ├── model/
│   ├── preprocessing/
│   ├── selection/
│   ├── utils/
├── example_data/
├── test/
├── Eigen/
├── fmt/
├── gsl/
```

One can complie programs using 
```
gcc -I/wd target_prgoram.cpp
```

## Instructions by examples
### 1. Data Reading 

We accept both numerical and string data written in a `csv` file as well as data stored in common C++ data structure `std::vector`. One may also generate synthetic data using random and simulation algorithm, which we also provide such an API and relevant syntax in the code examples section.

#### 1.a Read from csv file

We accept data file in `csv` format where each data is of dimension \f$n\times p\f$  where `n` (the number of rows) is 
number of samples and `p` (the number of columns) denotes number of features. Each data entry is separated by "," and 
allows for positive/negative infinity (user-specific `NumericType` is `float`,`double` or `long double`), missing values
(either emptry entry between two contiguous comma "," or NAN expression ) and non-number string. If user-specific 
`NumericType` is `float`,`double` or `long double`, acceptable numeric expressions also include hexadecimal and variants
of decimal float-poing expression (see [this](https://en.cppreference.com/w/cpp/string/basic_string/stof) for more details).
It will throw ``std::invalid_argument`` if the the entry read is not-a-number expression except this entry is of categorical type.

We determine each column's data type (either numeric or categorical) by the first row. We treat every entry as numeric if
it is a number (whether it is ordinal or numerical) and treat every entry that does not start with a numeric as categorical
(also called nominal data specifically). For those starting with a numeric but containing non-numeric character,
```std::invalid_argument``` will be thrown.

The repository includes some example datasets in `example_data` folder. For the first few rows of data at ```/wd/example_data/toy2/X_.csv``` reads 

```
0.863042617,0.125329727,,0.453642971,0.331653091,0.995670104,0.74309661,0.359688391,0.322855456,0.95246025,c
0.674891597,0.581686111,infinity,0.66090412,0.065200419,0.011847599,0.990730114,0.945842115,0.012044513,0.179192368,c
0.007477755,0.153923785,-INFINITY,0.935112575,0.435508347,0.398416802,0.722637869,0.825552776,0.016556552,0.540886826,c
0.547132088,0.792181391,0.321064493,0.966505815,0.752224509,0.588211238,0.8972678,0.938354094,0.813266819,0.744507902,b
0.272585536,0.442475366,0.234344325,0.659109156,0.363828626,0.150647433,0.663671727,0.282643646,0.980908137,0.008840418,a
.
.
.
```
where the last column (as determined from the above discussion) is a categorical data. It contains a missing value at row 0 (index starting from 0) and col 2. For the rest of the tutorial, we use (row,col)=(0,2) to indicate entry position for simplicity. There are two positive/negative infinity at (1,2) and (2,2) respectively.

An example code to read the csv file into a data container `Cosan::CosanRawData`:

~~~~~~~~~~~~~~~{.cpp}
#include <iostream>
#include <cosan/data/CosanData.h>
typedef double NumericType;
int main() {
    Cosan::CosanRawData<NumericType> CRD("./example_data/toy2/X_.csv");
    std::cout<<CRD.GetSummaryMessageX()<<std::endl;
    return 0;
}
~~~~~~~~~~~~~~~
and the output reads
```
Number of rows: 100
Number of columns: 11
Number of positive infinity values: 1. They are at (1,2) 
Number of negative infinity values: 1. They are at (2,2) 
Number of missing values: 6. They are at (0,2) (50,0) (51,0) (52,0) (67,1) (97,2) 
Columns of categorical values: Column 10 
```

To read two separate datasets, one can do 
~~~~~~~~~~~~~~~{.cpp}
Cosan::CosanRawData<NumericType> CRD(targetPath1,targetPath2);
~~~~~~~~~~~~~~~

#### 1.b Read data from CosanMatrix<NumericType>

One can also generate numeric-only data container `Cosan::CosanData` by initialization `CosanMatrix<NumericType>` which is a wrapper for [Eigen]((http://eigen.tuxfamily.org/)) object, further tutorial for initialization can be found [here](https://eigen.tuxfamily.org/dox/group__TutorialAdvancedInitialization.html).
~~~~~~~~~~~~~~~{.cpp}
 Cosan::CosanMatrix<NumericType> CM;
 CM.resize(nrows,ncols);
 CM<< 1,2,3,
     4,5,6,
     7,8,9;
 Cosan::CosanData<NumericType>  CD(CM);
~~~~~~~~~~~~~~~

To read two separate `CosanMatrix<NumericType>` objects into Cosan::CosanData, one can do 
~~~~~~~~~~~~~~~{.cpp}
Cosan::CosanData<NumericType>  CD(CM1,CM2);
~~~~~~~~~~~~~~~

#### 1.c Read data from std::vector<NumericType>
~~~~~~~~~~~~~~~{.cpp}
gsl::index nrows =2;
std::vector<NumericType> inputX({1,2,3,4,5,6});
Cosan::CosanData<NumericType>  CD1(inputX,nrows,"rowfirst"); // default fill row first, "columnfirst" for column first. 
~~~~~~~~~~~~~~~

or 
~~~~~~~~~~~~~~~{.cpp}
std::vector<NumericType> inputX({1,2,3,4,5,6}),inputY({1,2});
Cosan::CosanData<NumericType>  CD1(inputX,inputY,nrows,"rowfirst");
~~~~~~~~~~~~~~~

#### 1.d Synthetic data generation
One can consider random number generation algorithm provided (see [this](https://en.cppreference.com/w/cpp/numeric/random)) to construct ```std::vector``` and read data from. Or consider random number generation provided by [Eigen](https://eigen.tuxfamily.org/dox/classEigen_1_1DenseBase.html#ae814abb451b48ed872819192dc188c19). See below:
~~~~~~~~~~~~~~~{.cpp}
NumericType lb=0,ub=1;
Cosan::CosanData<NumericType> CD2(3,4,lb,ub);
~~~~~~~~~~~~~~~

to generate a container for a random matrix where each entry is uniformly sampled from [lb,ub]. The default for `lb`=0 and `ub`=1.

The code snippets can be found in `./test/tutorial_codeexamples/datareading.cpp`.

### 2. Data Preprocessing

For data preprocessing, we consider `./example_data/toy2/X_.csv` and `./example_data/toy2/Y_.csv` as the data example which can be read via 

~~~~~~~~~~~~~~~{.cpp}
Cosan::CosanRawData<NumericType> CRD("./example_data/toy2/X_.csv","./example_data/toy2/Y_.csv");
~~~~~~~~~~~~~~~

#### 2.a Overflow and underflow 
`Cosan::OverUnderFlow` will delete rows that contains positive/negative infinity entries. 
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/overunderflow.h>
Cosan::OverUnderFlow ouf(CRD);
~~~~~~~~~~~~~~~

and the output reads
~~~~~~~~~~~~~~~
*********************************
Begin cleaning up data of overflow/underflow!
There are 2 rows that have overflow/underflow data! Delete the whole rows. 
End of cleaning up data of overflow/underflow!
*********************************
~~~~~~~~~~~~~~~

#### 2.b Missing values
To take care of missing values, fill in by mean of other rows of the same column will be used in `Cosan::MissingValues`. 
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/missingvalues.h>
Cosan::MissingValues MissV(CRD);	
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin cleaning up missing data!
For X Column 0 has 3 missing value(s).
Fill the missing/nan entry with the column mean=0.470985.
For X Column 1 has 1 missing value(s).
Fill the missing/nan entry with the column mean=0.520299.
For X Column 2 has 2 missing value(s).
Fill the missing/nan entry with the column mean=0.462985.
End of cleaning process
*********************************
```
#### 2.c Normalization
One can choose \f$\ell_1\f$,\f$\ell_2\f$ or \f$\ell_{\infty}\f$ normalization, indicating p as the second argument. 
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/normalizer.h>
Coasn::Normalizer NM(CRD,p)// p can be 1,2 and std::numeric_limits<int>::max(). The default is 2.
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin normalizing data using norm 2!
End of normalizing data using norm 2 One may get norm of each row by GetSampleNorm().
*********************************
```

#### 2.e Standardization
This operation standardizes each column so that each column has mean 0 and variance 1.  
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/standardScaler.h>
Cosan::StandardScaler(CRD);
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin standardizing data 
End of standardizing data. One may transform or reverse-transform by .transform(),.InvTransform() function. 
*********************************
```

#### 2.f Categorical encoding
For categorical data type, we encoding them into numeric type, which is especially useful for downstreaming supervised learning tasks.
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/encoder.h>
Cosan::Encoder ED(CRD,true);//the second argument as a flag to indicate whether the newly-generated numeric matrix for categorical should be added back to the original numeric matrix X.    
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin encoding categorical data !
Finish encoding categorical data! Get access to the newly-generated additional matrix via .GetCatMatrix()
*********************************
Notice that CRD.X has been modified. The dimension of X is (98,14). 4 columns of one-hot encoding have been added.
```

The code snipptes can be found in `./test/tutorial_codeexamples/datapreprocessing.cpp`.

### 3.Feature Engineering
We continue to use the preprocessed dataset to conduct downstreaming tasks on features engineering. 
#### 3.a Feature scaling (MinMaxScalar)
We transform the range of the data distribution to per-determined [lb,ub] region, i.e. each entry will be upperbounded by lb and lowerbounded by ub. The transformation is a linear transformation and is useful especially in computer vision community where data need to be scaled [0,255] to [0,1] or vice versa.    
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/minmaxscaler.h>
NumericType lb=0,ub=1;    
Cosan::MinmaxScaler MMS(CRD,lb,ub);//transform X to domain [lb,ub]. If not provided, default value lb =0,ub=1
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin transformation to X to [0,1]!
End of transformation to X to [0,1]!
*********************************
```

#### 3.b Polynomial features generation
This is to generate new polynomial features such as \f$x_1^2,x_4^2\f$ where \f$x_i\f$ indicates column i of matrix X. Beside `CRD`, an input type of `std::vector<std::pair<gsl::index,NumericType>>` to indicate new polynomial features. For instance, if um = {{1,2},{2,3}}, it means that two columns are generated where the first column is \f$x_1^2\f$ and the second column is \f$x_2^3\f$.   
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/polynomialfeatures.h>
std::vector<std::pair<gsl::index,NumericType>> um = {{0,1.2},{1,1.1}};
Cosan::PolynomialFeatures PF(CRD,um,true);//um is a vector of pair where each entries indicates index and power to be generated. The third argument indicates whether the new features should be added to CRD.X. Default is false.
std::pair<gsl::index,gsl::index> pair = {4,5};
PF.SetInteractionFeatures(CRD,pair,true);//to generative interactive features from column 4 and 5.
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin to generating polynomial features!!
Generating power 1.200000 of Column 0!
Generating power 1.100000 of Column 1!
Finish generating polynomial features! Use .GetPolynomialFeatures() to get access it.
*********************************
Notice that CRD.X has been modified. The dimension of X is (98,16). 2 columns of polynomialfeatures have been added.
*********************************
Begin generating interaction features between 4 and 5!!
End of generating interaction features. Get access to it via .GetInteractionFeatures()
*********************************
Notice that CRD.X has been modified. The dimension of X is (98,17). 1 columns of interaction features have been added.
```
#### 3.c Principal component analysis
PCA is defined as an orthogonal linear transformation that transforms the data to a new coordinate system such that the greatest variance by some scalar projection of the data comes to lie on the first coordinate (called the first principal component), the second greatest variance on the second coordinate, and so on. More details can be seen [here](https://en.wikipedia.org/wiki/Principal_component_analysis).
One may need to choose target number of principal component \f$p\f$. The default value is the minimum value of 5 and number of columns for X. 
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/principalcomponentanalysis.h>
gsl::index ncomponent = 5;
Cosan::PrincipalComponentAnalysis PCA(CRD,ncomponent);
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin PCA on Input Data X. Select the first 5 principal components
The first 0 principal components explains 37.456450% of the total variance.
The first 1 principal components explains 53.101910% of the total variance.
The first 2 principal components explains 66.014039% of the total variance.
The first 3 principal components explains 74.282581% of the total variance.
The first 4 principal components explains 80.106676% of the total variance.
The first 5 principal components explains 83.567345% of the total variance.
The first 6 principal components explains 86.706581% of the total variance.
The first 7 principal components explains 89.770204% of the total variance.
The first 8 principal components explains 92.511648% of the total variance.
The first 9 principal components explains 94.948812% of the total variance.
The first 10 principal components explains 97.204781% of the total variance.
The first 11 principal components explains 99.128878% of the total variance.
Finsh PCA on Input Data X. The first 5 principal components explains 83.567345% of the total variance.
Uer .GetPC() function to get the principal components.
*********************************
```
#### 3.d User-defined transformation
We allow a user-defined features with input type `std::vector<NumericType>`. The operation will add one additional column to CRD.X.
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/preprocessing/customtransform.h>
Cosan::CustomTransform CT(CRD,newInputX);// newInputX is of tpye std::vector<NumericType> to be added to CRD.X. 
~~~~~~~~~~~~~~~
and the output reads
```
*********************************
Begin to generating customized features!!
End of generating customized features. One may get access to the new features via .GetCustomFeatures()!
*********************************
Notice that CRD.X has been modified. The dimension of X is (98,18). 1 columns of new features have been added.
```
### 4. Model Fitting
Four linear models are given here. They are
~~~~~~~~~~~~~~~{.cpp}
Cosan::CosanLinearRegression
Cosan::CosanRidgeRegression
Cosan::CosanPrincipalComponentRegression
Cosan::CosanPCRRidge
~~~~~~~~~~~~~~~

To initialize model object, one can do 
~~~~~~~~~~~~~~~{.cpp}
model(); // The default constructor where the model is without intercept. 
model(bool bias);
model(NumericType param, bool bias);//for model with only one parameter. Ridge regression and PCR are the cases.
model(std::vector<NumericType> params, bool bias);//for model with more than one parameter. Each parameter is the enry of params. PCR with L2 square norm is the case. 
~~~~~~~~~~~~~~~

To initialize model object and run model fitting automatically, one can do 
~~~~~~~~~~~~~~~{.cpp}
model(CosanRawData<NumericType> RD,NumericType param ,bool bias = false)
model(CosanData<NumericType> CD,NumericType param ,bool bias = false)
model(CosanMatrix<NumericType> X,CosanMatrix<NumericType> Y,NumericType param,bool bias = false)
~~~~~~~~~~~~~~~
For model with more than 1 parameter, one should replace `NumericType param` by `std::vector<NumericType> params`.

To call fit model in specific and use fitted model for prediction, one can do 
~~~~~~~~~~~~~~~{.cpp}
model.fit(CosanMatrix<NumericType> X,CosanMatrix<NumericType> Y)
model.predict(CosanMatrix<NumericType> X)
~~~~~~~~~~~~~~~

To set new params and get current params, one can do
~~~~~~~~~~~~~~~{.cpp}
model.SetParams(NumericType param); //for model with more than 1 parameter, input should be std::vecotr<NumericType> params  
model.GetParams();
~~~~~~~~~~~~~~~

To obtain the coefficient for the model (\f$\beta\f$), one can use 
~~~~~~~~~~~~~~~{.cpp}
model.GetBeta();
~~~~~~~~~~~~~~~

#### 4.a Ordinary least square (linear regression)
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/model/CosanLinearRegression.h>
~~~~~~~~~~~~~~~

#### 4.b Ordinary least square with L2-squared norm penalty (ridge regression)
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/model/CosanRidgeRegression.h>
~~~~~~~~~~~~~~~

#### 4.c Principal component regression (PCR) 
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/model/CosanPrincipalComponentRegression.h>
~~~~~~~~~~~~~~~

#### 4.d Principal component regressionw with \f$\ell_2\f$-squared norm penalty ( ridge PCR)
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/model/CosanPCRRidge.h>
~~~~~~~~~~~~~~~

### 5. Model Selection 

Model selection module includes two main parts: splitter method and search method. Three splitter methods are included as well as the corresponding parallel-computing version: kfold, random kfold and timeseries kfold. Two search methods: grid search and random grid search.
~~~~~~~~~~~~~~~{.cpp}
Cosan::KFold
Cosan::KFoldParallel
Cosan::RandomKFold
Cosan::RandomKFoldParallel
Cosan::TimeSeriesSplit
Cosan::TimeSeriesSplitParallel
~~~~~~~~~~~~~~~
To initialize splitter object, the following syntax can be used
~~~~~~~~~~~~~~~{.cpp}
splitter(gsl::index kfoldnumber);
splitter(gsl::index nrows, gsl::index kfoldnumber) 
~~~~~~~~~~~~~~~
The above second constructor will generate a private member function split_batch which can be get accessed via GetSplit() fnuction.
To call splitting function specifically, one should do 
~~~~~~~~~~~~~~~{.cpp}
splitter.SetSplit()
~~~~~~~~~~~~~~~
To call parallel version, one should call the corresponding class for parallel computing and the remainder is the same.

#### 5.a k-fold cross-validation
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/selection/kfold.h>
~~~~~~~~~~~~~~~
#### 5.b random k-fold cross-validation
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/selection/randomkfold.h>
~~~~~~~~~~~~~~~
#### 5.c timeseries k-fold cross-validation
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/selection/timeseriessplit.h>
~~~~~~~~~~~~~~~
One should initialize search method via 
~~~~~~~~~~~~~~~{.cpp}
Search(CosanData<NumericType> CRD, Model estimator,Metric & metric,Splitter & split, std::vector<NumericType> paramGrid)
~~~~~~~~~~~~~~~
where `Model` is an inherited class of `CosanModel` class, `Metric` is an inherited class of `CosanMetric` class (which will be discussed in the next section), Splitter is the aforementioned splitter class and `std::vector<NumericType> paramGrid` is the list of parameters to selected from.

For multi-parameters version of search method, one should replace by [SearchName]+'Multi'. For instance,for `GridSearch`, one should call `GridSearchMulti` instead and replace `std::vector<NumericType> paramGrid` by `std::vector<std::vector<NumericType>> paramGrid`. For parallel computing version, one should append 'Parallel' as well. Additional input argument `int nthreads` (with default `-1`) is added to set the number of threads to be used. `-1` means uses all available threads. For instance, for `GridSearch` in both multi-parameters and parallel computing version, one should use `GridSearchMultiParallel`.    
#### 5.d grid search
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/selection/gridsearch.h>
~~~~~~~~~~~~~~~

#### 5.e random grid search
~~~~~~~~~~~~~~~{.cpp}
#include <cosan/selection/randomgridsearch.h>
~~~~~~~~~~~~~~~

The following snippet gives one concrete example for cross-validation process,
~~~~~~~~~~~~~~~{.cpp}
constexpr gsl::index nrows = 10000;
constexpr gsl::index ncols = 5;
Cosan::CosanMatrix<NumericType> X_input
Cosan::CosanMatrix<NumericType> Y_input;    
X_input.resize(nrows,ncols);
Y_input.resize(nrows,1);
X_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows,ncols>::Random();
Y_input = Eigen::Matrix<decltype(X_input)::Scalar,nrows,1>::Random();
Cosan::CosanData<NumericType>  CD(X_input,Y_input);
Cosan::CosanPCRRidge<decltype(X_input)::Scalar> CRRwbias;
Cosan::MeanSquareError<decltype(X_input)::Scalar> mse;
NumericType a = 0.05;
std::vector<NumericType> v(10);
std::generate(v.begin(), v.end(), [n = 1, &a]() mutable { return n++ * a; });
Cosan::KFold kf(5);
Cosan::RandomGridSearch GDS(CD,CRRwbias,mse,kf,v);
~~~~~~~~~~~~~~~

### 6. Evaluation

#### 6.1 Metric Class
Metric is critical for cross-validation as it provides a venue to evaluate the performance of model and the best parameters to be chosen is based on the metric values. Four metrics are implemented in our library `maximum error`, `mean absolute error`,`mean square error`, `coefficient of determination`. The class names are

~~~~~~~~~~~~~~~{.cpp}
Cosan::MeanAbsError
Cosan::MeanSquareError
Cosan::R2Score
Cosan::MaxError
~~~~~~~~~~~~~~~

To call each individual metric class and calculate the corresponding metric one can do
Initialize metric object
~~~~~~~~~~~~~~~{.cpp}
Metric();
Metric(CosanMatrix<NumericType> yPredict,CosanMatrix<NumericType> yTrue);//will calculate error metric and store as a public member variable error. 
~~~~~~~~~~~~~~~
To Calculate the error specifically, one should call 
~~~~~~~~~~~~~~~{.cpp}
model.GetError(CosanMatrix<NumericType>yPredict,CosanMatrix<NumericType> yTrue);
~~~~~~~~~~~~~~~

All metric class is stored at `./cosan/evaluation/CosanMetric.h`. `#include <cosan/evaluation/CosanMetric.h>` should suffice to call metric class.

__Note__: the order of input argument `yPredict` and `yTrue` matters for `Cosan::R2Score`

#### 6.2 Basic statistics functions

Those functions are defined in `./cosan/evaluation/statistics.h`. One can use the following snippet to calculate basic summary statistics. The calculation will also store the corresponding value in the public member variables `SampleCovariance`, `mean`,`variance`,`median`,`maxNum`,`minNum`.
~~~~~~~~~~~~~~~{.cpp}
Cosan::SummaryStatistics().GetSampleCovariance(CosanMatrix<NumericType> X);
Cosan::SummaryStatistics().GetMean(CosanMatrix<NumericType> X);
Cosan::SummaryStatistics().GetVar(CosanMatrix<NumericType> X);
Cosan::SummaryStatistics().GetMedian(CosanMatrix<NumericType> X);
Cosan::SummaryStatistics().GetMax(CosanMatrix<NumericType> X);
Cosan::SummaryStatistics().GetMin(CosanMatrix<NumericType> X);
~~~~~~~~~~~~~~~

7. Useful matrix manipulation snippets

Some useful matrix operation on `ConsanMatrix` 

Generate all zero matrix of size `n` by `m`
~~~~~~~~~~~~~~~{.cpp}
Cosan::CosanMatrix<NumericType>::Zero(n,m);
~~~~~~~~~~~~~~~
Generate an identity matrix of size `n`
~~~~~~~~~~~~~~~{.cpp}
Cosan::CosanMatrix<NumericType>::Identity(n,n);
~~~~~~~~~~~~~~~

Generate all one matrix of size `n` by `m`
~~~~~~~~~~~~~~~{.cpp}
CosanMatrix<NumericType>::Ones(n,m);
~~~~~~~~~~~~~~~

File `cosan/utils/utils.h` contains useful functions including `removeRow` and `removeColumn`. 
To remove \f$k\f$th row from `CosanMatrix` X or to remove the \f$k\f$th column, one can do 
~~~~~~~~~~~~~~~{.cpp}
removeRow(X,k);
removeColumn(X,k);
~~~~~~~~~~~~~~~
