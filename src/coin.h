#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    int type;
    float points;
    float radius;

    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object1;
};

#endif
