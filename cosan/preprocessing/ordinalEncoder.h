#ifndef COSAN_ORDINALENCODER_H
#define COSAN_ORDINALENCODER_H

#include <cosan/preprocessing/encoder.h>

namespace Cosan {
    class OrdinalEncoder : public Encoder {
    public:

        std::vector<int> getEncoding(int colIdx, const std::string &category) override {
            int ordinal = this->getCategories()[colIdx][category];
            std::vector<int> encoding{};
            encoding.push_back(ordinal);
            return encoding;
        }

    };

}


#endif //COSAN_ORDINALENCODER_H
