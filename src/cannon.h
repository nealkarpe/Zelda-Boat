#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float length;
    void draw(glm::mat4 VP);
    void tick();
	void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr, int baseIndex);
private:
    VAO *object1;
};

#endif
