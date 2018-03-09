#include "main.h"

#ifndef GIFT_H
#define GIFT_H


class Gift {
public:
    Gift() {}
    Gift(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    int type;
    float points;
    float radius;
    bool available;
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex);
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object1;
};

#endif
