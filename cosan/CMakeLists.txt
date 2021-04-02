cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)

add_library(cosan model/CosanLinearModel.cpp model/CosanLinearModel.h model/CosanLinearRegression.cpp model/CosanLinearRegression.h model/CosanRidgeRegression.cpp model/CosanRidgeRegression.h model/CosanLasso.cpp model/CosanLasso.h model/CosanElasticNet.cpp model/CosanElasticNet.h)

target_include_directories(cosan PUBLIC .)