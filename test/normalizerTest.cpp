#include <iostream>
#include "../preprocessing/normalizer.h"

int main() {

    Cosan::normalizer normalizer;

    EigenMatrix X1{2, 2};
    X1 << 3, 4,
            2, 0;
    std::cout << normalizer.normalize(X1) << '\n' << std::endl;

    EigenMatrix X2{3, 3};
    X2 << 1, -1, 2,
            2, 0, 0,
            0, 1, -1;
    std::cout << normalizer.normalize(X2) << '\n' << std::endl;

    float data[] = {-1, 1, 0};
    std::cout << normalizer.normalize(Eigen::Map<EigenMatrix>(data, 1, 3)) << '\n' << std::endl;

}
