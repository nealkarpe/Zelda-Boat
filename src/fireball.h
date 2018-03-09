#include "main.h"

#ifndef FIREBALL_H
#define FIREBALL_H

class Fireball {
public:
    Fireball() {}
    Fireball(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float speed;
    bool alive;
    float angle;
    float dist;
    float size;
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex);
private:
    VAO *object1;
};

#endif
