//
// Created by shiqi on 2019-08-05.
//

#ifndef INC_2D_ANIMATION_ENTITY_H
#define INC_2D_ANIMATION_ENTITY_H


class Entity {
public:
    virtual void update() = 0;

    virtual int getX() = 0;

    virtual int getY() = 0;
};


#endif //INC_2D_ANIMATION_ENTITY_H
