#include <iostream>
#include <cosan/data/CosanData.h>

int main() {
    Cosan::CosanRawData CD("./example_data/categorical/X.csv");

    std::cout << CD.GetSummaryMessageX() << std::endl;

    std::cout << "\n" << "Indices of categorical columns: " << std::endl;
    for (auto col : CD.GetcolCatX()) {
        std::cout << col << " ";
    }

    std::cout << "\n\n" << "Raw Column Index to Categorical Column Index: " << std::endl;
    for (const auto &[key, value] : CD.GetRawToCatIdx()) {
        std::cout << key << ":" << value << std::endl;
    }

    std::cout << "\n" << "Categories for each column: " << std::endl;
    for (const auto& colsvalues : CD.GetsvaluesX()) {
        for (const auto& sval : colsvalues) {
            std::cout << sval << ", ";
        }
        std:: cout << std::endl;
    }
    std::cout << "\n" << std::endl;

    return 0;
}
