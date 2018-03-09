#include "fireball.h"
#include "main.h"

Fireball::Fireball(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->speed = 0.7;
    this->alive = false;
    this->angle = 0.0f;
    this->dist = 0.0f;

    GLfloat vertex_buffer_data_1[6*2*9];

    this->size = 0.2;

    this->addSquare(this->size,-this->size,this->size,this->size,this->size,-this->size,vertex_buffer_data_1,0);
    this->addSquare(this->size,-this->size,-this->size,-this->size,this->size,-this->size,vertex_buffer_data_1,1);
    this->addSquare(this->size,this->size,this->size,-this->size,this->size,-this->size,vertex_buffer_data_1,2);
    this->addSquare(-this->size,-this->size,this->size,-this->size,this->size,-this->size,vertex_buffer_data_1,3);
    this->addSquare(this->size,-this->size,this->size,-this->size,this->size,this->size,vertex_buffer_data_1,4);
    this->addSquare(this->size,-this->size,this->size,-this->size,-this->size,-this->size,vertex_buffer_data_1,5);

    this->object1 = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data_1, COLOR_ORANGE, GL_FILL);
}

void Fireball::tick() {
    if(this->dist >= 70) {
        this->alive = false;
    }

    this->position.z -= this->speed * cos(this->angle*M_PI/180.0f);
    this->position.x += this->speed * sin(this->angle*M_PI/180.0f);
    this->dist += this->speed;
}

void Fireball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Fireball::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr, int baseIndex) {
    int i;
    if(x1==x2) {
        const GLfloat temp[] = {
            x1, y2, z2,
            x1, y1, z2,
            x1, y2, z1,

            x1, y1, z1,
            x1, y1, z2,
            x1, y2, z1,
        };
        for(i=0;i<18;i++) arr[baseIndex*18+i] = temp[i];
    }
    else if(y1==y2) {
        const GLfloat temp[] = {
            x2, y1, z2,
            x1, y1, z2,
            x2, y1, z1,

            x2, y1, z1,
            x1, y1, z2,
            x1, y1, z1,
        };
        for(i=0;i<18;i++) arr[baseIndex*18+i] = temp[i];
    }
    else if(z1==z2) {
        const GLfloat temp[] = {
            x2, y2, z1,
            x1, y2, z1,
            x2, y1, z1,

            x1, y1, z1,
            x1, y2, z1,
            x2, y1, z1,
        };
        for(i=0;i<18;i++) arr[baseIndex*18+i] = temp[i];
    }
}
