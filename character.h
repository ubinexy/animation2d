//
// Created by shiqi on 2019-08-05.
//

#ifndef INC_2D_ANIMATION_CHARACTER_H
#define INC_2D_ANIMATION_CHARACTER_H


#include <array>
#include <vector>

class character {

private:
    int status;
    int nof;
    std::vector<float> animation_set;
public:

    void setStatus(int status) {
        this->status = status;
    }
};


#endif //INC_2D_ANIMATION_CHARACTER_H
