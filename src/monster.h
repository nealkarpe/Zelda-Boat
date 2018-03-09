#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z);
    glm::vec3 position;
    bool alive;
    float width;
    float rotation;
    int type;
    void draw(glm::mat4 VP);
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex);
private:
    VAO *object1;
    VAO *object2;
};

#endif
