#ifndef COSAN_ENCODER_H
#define COSAN_ENCODER_H

#include <cosan/preprocessing/preprocessor.h>
#include <string>

namespace Cosan {
    class Encoder {
    public:

        Encoder() = default;

        Encoder(std::vector<std::unordered_map<std::string, gsl::index>> categories) {
            this->categories = categories;
        }

        ~Encoder() = default;

        enum HANDLE_UNKNOWN {
            IGNORE,
            ERROR
        };

        std::vector<std::unordered_map<std::string, gsl::index>> getCategories() const {
            return this->categories;
        }

        void fit(CosanRawData X) {
            this->setCategories(X.GetsvaluesX());
        }

        void setCategories(const std::vector<std::vector<std::string>> &svaluesX) {
            for (const auto &col : svaluesX) {
                std::unordered_map<std::string, gsl::index> categoryToOrdinal{};
                for (const auto &sval : col) {
                    if (categoryToOrdinal.find(sval) == categoryToOrdinal.end()) {
                        categoryToOrdinal.insert({sval, categoryToOrdinal.size()});
                    }
                }
                this->categories.push_back(categoryToOrdinal);
            }
        }

        std::vector<std::vector<int>> transform(CosanRawData X) {
            std::vector<std::vector<int>> encodedCategories{};
            for (auto row = 0; row < X.GetrowsX(); ++row) {
                std::vector<int> rowEncoding{};
                for (auto col = 0; col < X.GetsvaluesX().size(); ++col) {
                    std::vector<std::string> colCat = X.GetsvaluesX()[col];
                    std::string category = colCat[row];
                    std::vector<int> encoding = this->getEncoding(col, category);
                    rowEncoding.insert(rowEncoding.end(), encoding.begin(), encoding.end());
                }
                encodedCategories.push_back(rowEncoding);
            }
            return encodedCategories;
        }

        virtual std::vector<int> getEncoding(int colIdx, const std::string &category) = 0;

    private:
        std::vector<std::unordered_map<std::string, gsl::index>> categories;

    };


}


#endif //COSAN_ENCODER_H
