#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z);
    glm::vec3 position;
    float barrelSize;
    void draw(glm::mat4 VP);
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex);
private:
    VAO *object1;
};

#endif
