selection_param = 
{'lambda':[0.1,0.2,0.3,...],
 'hyoercoeff1':[0.1,0.2,0.3,...],
 'hyper2':[0.1,0.2,0.3,...]}

1. consider all combinations
2. random grid search: random 2000 -> 100 -> 


user: X,y -> preprocessing -> (X',y') -> model fitting (beta) -> cross validation ()

1. model X_new type == model's X type 
2. model coefficient beta p = X_new feature

input data ambiguity: 
	warning 
		array: (n,)
		array: (n,1)
	force matrix 

data: 
	1. csv -> trg data type 
	2. std::vector -> trg data type

missing value:
	,,

eigen: adaptation

utility: 
	Constraints and concepts
	
Input / generate data type:

data: 
	1. csv -> trg data type 
	2. std::vector<vector<int>> -> trg data type // 
	3. random generation  X n by p normal rv. Y n by 1      //
	4. object: load/save i.e. pickle // version 1.2

->Output: eigen MatrixXd, columnVector, RowVector
	X, Y  Y: vector  for each sample, one output. 
	X<-matrix, Y<- MatrixXd, columnVector, RowVector

DataTransformation: 
CosanObject <- CosanDataTransformation <- CosanPreprocessing<-CosanBaseTransformation
CosanObject <- CosanDataTransformation <- CosanInputationMissingValue<-

model:
	1. load/save
	2. 

GridSearch

Naming: 
Function comment: 
	brief description 1,2 sentences
	input: 
	type/require: 
	output: 
	Notes:

Class: 
	

	check :Clear, Functional C++ Documentation with Sphinx + Breathe + Doxygen + CMake
		https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/

import module







