#include <iostream>
#include "../base/common.h"
#include "../io/csvLoader.h"

int main() {
    // Assumption: each row is a record; each col is a feature
    EigenMatrix X = load_csv("X_test.csv");
    EigenMatrix y = load_csv("y_test.csv");

    EigenMatrix beta = (X.transpose() * X).ldlt().solve(X.transpose() * y);
    std::cout << beta << std::endl;

}
