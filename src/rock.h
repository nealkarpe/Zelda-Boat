#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y, float z);
    glm::vec3 position;
    glm::mat4 translate;
    float rockSize;
    void draw(glm::mat4 VP);
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex);
private:
    VAO *object1;
};

#endif
