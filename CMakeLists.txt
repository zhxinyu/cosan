cmake_minimum_required(VERSION 3.17)
project(cosan)

set(CMAKE_CXX_STANDARD 20)

include_directories(base)
include_directories(data)
include_directories(features)
include_directories(io)
include_directories(model)

add_executable(cosan
        data/CosanDataRaw.h
        io/csvLoader.h
        test/csvLoaderTest.cpp
        preprocessing/preprocesssor.h
        preprocessing/standardScaler.cpp
        preprocessing/standardScaler.h
        test/standardScalerTest.cpp
        base/common.h
        preprocessing/normalizer.cpp
        preprocessing/normalizer.h
        test/normalizerTest.cpp
        )
