#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->alive = false;
    this->rotation = 0;
    this->offset = 0.0;
    this->step = 0.4;
    this->life = 3;
    this->width = 3.0;
    float width = this->width;
    float height = 5.0;
    float upperHeight = 7.0;
    float upperWidth = 2.0;

    GLfloat vertex_buffer_data_1[10*2*9];

    this->addSquare(width,-width,height,height,width,-width,vertex_buffer_data_1,0);
    this->addSquare(width,width,height,0,width,-width,vertex_buffer_data_1,1);
    this->addSquare(-width,-width,height,0,width,-width,vertex_buffer_data_1,2);
    this->addSquare(width,-width,height,0,width,width,vertex_buffer_data_1,3);
    this->addSquare(width,-width,height,0,-width,-width,vertex_buffer_data_1,4);

    this->addSquare(upperWidth,-upperWidth,upperHeight,upperHeight,upperWidth,-upperWidth,vertex_buffer_data_1,5);
    this->addSquare(upperWidth,upperWidth,upperHeight,height,upperWidth,-upperWidth,vertex_buffer_data_1,6);
    this->addSquare(-upperWidth,-upperWidth,upperHeight,height,upperWidth,-upperWidth,vertex_buffer_data_1,7);
    this->addSquare(upperWidth,-upperWidth,upperHeight,height,upperWidth,upperWidth,vertex_buffer_data_1,8);
    this->addSquare(upperWidth,-upperWidth,upperHeight,height,-upperWidth,-upperWidth,vertex_buffer_data_1,9);

    this->object1 = create3DObject(GL_TRIANGLES, 10*2*3, vertex_buffer_data_1, COLOR_BLACK, GL_FILL);
}

void Boss::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex)
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

void Boss::tick() {
    this->position.x += this->step;
    this->offset += this->step;
    if(this->offset >= 12.0 || this->offset <= -12.0) this->step = -this->step;
}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}
