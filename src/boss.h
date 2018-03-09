#include "main.h"

#ifndef BOSS_H
#define BOSS_H


class Boss {
public:
    Boss() {}
    Boss(float x, float y, float z);
    glm::vec3 position;
    bool alive;
    int life;
    float width;
    float rotation;
    float offset;
    float step;
    void tick();
    void draw(glm::mat4 VP);
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex);
private:
    VAO *object1;
};

#endif
