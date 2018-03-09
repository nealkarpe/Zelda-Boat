#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y, float z);
    glm::vec3 position;
    glm::mat4 translate;
    void draw(glm::mat4 VP);
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr, int baseIndex);

private:
    VAO *object1;
};

#endif
