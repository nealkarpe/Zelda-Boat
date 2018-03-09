#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);

    this->barrelSize = 1.0f;

    GLfloat vertex_buffer_data_1[5*2*9];

    this->addSquare(this->barrelSize,-this->barrelSize,this->barrelSize,this->barrelSize,this->barrelSize,-this->barrelSize,vertex_buffer_data_1,0);
    this->addSquare(this->barrelSize,this->barrelSize,this->barrelSize,0,this->barrelSize,-this->barrelSize,vertex_buffer_data_1,1);
    this->addSquare(-this->barrelSize,-this->barrelSize,this->barrelSize,0,this->barrelSize,-this->barrelSize,vertex_buffer_data_1,2);
    this->addSquare(this->barrelSize,-this->barrelSize,this->barrelSize,0,this->barrelSize,this->barrelSize,vertex_buffer_data_1,3);
    this->addSquare(this->barrelSize,-this->barrelSize,this->barrelSize,0,-this->barrelSize,-this->barrelSize,vertex_buffer_data_1,4);

    this->object1 = create3DObject(GL_TRIANGLES, 5*2*3, vertex_buffer_data_1, COLOR_BROWN, GL_FILL);
}

void Barrel::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex)
{
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

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}
