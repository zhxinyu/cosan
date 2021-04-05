#ifndef COSAN_ONEHOTENCODER_H
#define COSAN_ONEHOTENCODER_H

#include <cosan/preprocessing/encoder.h>

namespace Cosan {
    class OnehotEncoder : public Encoder {
    public:

        std::vector<int> getEncoding(int colIdx, const std::string &category) override {
            int categoryCount = this->getCategories()[colIdx].size();
            int ordinal = this->getCategories()[colIdx][category];
            std::vector<int> encoding(categoryCount);
            encoding[ordinal] = 1;
            return encoding;
        }

    };

}


#endif //COSAN_ONEHOTENCODER_H
