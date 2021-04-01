#include "standardScaler.h"

void Cosan::standardScaler::fit(EigenMatrix X) {
    this->mean = X.colwise().mean();
    this->std = ((X.rowwise() - mean).array().pow(2).colwise().sum() / X.rows()).sqrt();
}

EigenMatrix Cosan::standardScaler::transform(EigenMatrix X) {
    return (X.rowwise() - this->mean).array().rowwise() / this->std.array();
}

EigenMatrix Cosan::standardScaler::standardize(EigenMatrix X) {
    this->fit(X);
    return this->transform(X);
}