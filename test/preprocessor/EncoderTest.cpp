#include <iostream>
#include <cosan/data/CosanData.h>
#include <cosan/preprocessing/onehotEncoder.h>
#include <cosan/preprocessing/ordinalEncoder.h>

int main() {
    Cosan::CosanRawData CD("./example_data/categorical/X.csv");

    std::cout << "\n" << "Categories for each column: " << std::endl;
    for (const auto& colsvalues : CD.GetsvaluesX()) {
        for (const auto& sval : colsvalues) {
            std::cout << sval << ", ";
        }
        std:: cout << std::endl;
    }

    std::cout << "\n==== Onehot ====" << std::endl;
    Cosan::OnehotEncoder onehotEncoder{};
    onehotEncoder.fit(CD);
    for (const auto& colCat : onehotEncoder.getCategories()) {
        for (const auto &[key, value] : colCat) {
            std::cout << key << ":" << value << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> encodings1 = onehotEncoder.transform(CD);
    for (const auto& i : encodings1) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\n==== Ordinal ====" << std::endl;
    Cosan::OrdinalEncoder ordinalEncoder{};
    ordinalEncoder.fit(CD);
    for (const auto& colCat : ordinalEncoder.getCategories()) {
        for (const auto &[key, value] : colCat) {
            std::cout << key << ":" << value << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> encodings2 = ordinalEncoder.transform(CD);
    for (const auto& i : encodings2) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}
