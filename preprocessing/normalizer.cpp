#include "normalizer.h"

void Cosan::normalizer::fit(EigenMatrix X) {
    // fit does nothing
}

EigenMatrix Cosan::normalizer::transform(EigenMatrix X) {
    return X.rowwise().normalized();
}

// Normalization is the process of scaling individual samples to have unit norm
EigenMatrix Cosan::normalizer::normalize(const EigenMatrix& X) {
    return transform(X);
}
