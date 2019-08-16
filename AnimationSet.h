//
// Created by shiqi on 2019-08-06.
//

#ifndef INC_2D_ANIMATION_ANIMATIONSET_H
#define INC_2D_ANIMATION_ANIMATIONSET_H

class AnimationSet {
public:
    virtual AnimationSet& playOnce() = 0;
    virtual std::vector<std::bitset<256>> getData() = 0;
//    virtual AnimationSet& mix(Engine engine, AnimationSet& ani) = 0;
};

#endif //INC_2D_ANIMATION_ANIMATIONSET_H
