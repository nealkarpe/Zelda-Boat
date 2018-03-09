#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position;
    float health;
    float rotation;
    float Yrotation;
    float upStep;
    float Yspeed;
    float acc;
    float outerLength;
    float outerBreadth;
    bool goDown;
    float downYspeed;
    void draw(glm::mat4 VP);
    void tick();
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr, int baseIndex);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif
