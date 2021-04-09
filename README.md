# cosan 

## Overview:
We aim to write an open-source machine learning library Cosan for C++ which provides a data mining and data predictive analytics framework. It implements a selected range of simple and efficient data processing procedures and machine learning algorithms and is designed to interoperate with C++ scientific computing library Eigen/xtensor. 

## Getting started

### How to install Cosan
To use Cosan, you just need to download Cosan source code and include the header files in your program. The header files are the same for all platforms. It is not necessary to use CMake or install anything. In order for your compiler to locate the header files, you can copy or symlink the Cosan folder to ```/usr/local/include```, or specify the path to Cosan when you compile your program.

### How to compile and run Cosan

```g++ -I /path/to/cosan/ your_program.cpp -o your_program && ./your_program```


### Hello World programs

#### Data input
Cosan supports various ways of getting the input dataset. One of the most common ones is to parse the data from a csv file. 

```
Cosan::CosanRawData CD("./path/to/example.csv");
```

You can also choose to create your own dataset when initializing the object.

```
Cosan::CosanMatrix X{3,3};
    X << 1, -1, 2,
         2, 0, 0,
         0, 1, -1;
```

CosanRawData will fulfill your needs with different kinds of data types and all sorts of operations.

#### Preprocessing
Usually the first step when doing data analytics is dataset transformation and preprocessing. 

```
    Cosan::standardScaler ss{};
    std::cout << ss.standardize(CD) << std::endl;
```

#### Linear Models

```
Cosan::CosanRawData CD("./example_data/X.csv","./example_data/y.csv");
Cosan::CosanLinearRegression CLR()
CLRwbias.fit(CD.GetInput(),CD.GetTarget());
std::cout<<CLRwbias.GetBeta()<<std::endl;
```

#### Model selection

