#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->alive = true; 
    this->type = rand()%3;
    color_t colors[] = {COLOR_SEAGREEN,COLOR_YELLOW,COLOR_RED};

    this->rotation = rand()%360;

    this->width = 1.5;
    float height = 2*this->width;

    GLfloat vertex_buffer_data_1[5*2*9];

    this->addSquare(this->width,-this->width,height,height,this->width,-this->width,vertex_buffer_data_1,0);
    this->addSquare(this->width,this->width,height,0,this->width,-this->width,vertex_buffer_data_1,1);
    this->addSquare(-this->width,-this->width,height,0,this->width,-this->width,vertex_buffer_data_1,2);
    this->addSquare(this->width,-this->width,height,0,this->width,this->width,vertex_buffer_data_1,3);
    this->addSquare(this->width,-this->width,height,0,-this->width,-this->width,vertex_buffer_data_1,4);

    float center = this->width;
    float width = this->width;
    float offset = center/2.0;
    float wingLength = 2.0;

    static const GLfloat vertex_buffer_data_2[] = {
        width, center+offset, 0,
        width, center, offset,
        width+wingLength, center, 0,

        width, center-offset, 0,
        width, center, offset,
        width+wingLength, center, 0,

        width, center+offset, 0,
        width, center, -offset,
        width+wingLength, center, 0,

        width, center-offset, 0,
        width, center, -offset,
        width+wingLength, center, 0,



        -width, center+offset, 0,
        -width, center, offset,
        -width-wingLength, center, 0,

        -width, center-offset, 0,
        -width, center, offset,
        -width-wingLength, center, 0,

        -width, center+offset, 0,
        -width, center, -offset,
        -width-wingLength, center, 0,

        -width, center-offset, 0,
        -width, center, -offset,
        -width-wingLength, center, 0,



        0, center+offset, width,
        offset, center, width,
        0, center, width+wingLength,

        0, center-offset, width,
        offset, center, width,
        0, center, width+wingLength,

        0, center+offset, width,
        -offset, center, width,
        0, center, width+wingLength,

        0, center-offset, width,
        -offset, center, width,
        0, center, width+wingLength,



        0, center+offset, -width,
        offset, center, -width,
        0, center, -width-wingLength,

        0, center-offset, -width,
        offset, center, -width,
        0, center, -width-wingLength,

        0, center+offset, -width,
        -offset, center, -width,
        0, center, -width-wingLength,

        0, center-offset, -width,
        -offset, center, -width,
        0, center, -width-wingLength,

    };

    this->object1 = create3DObject(GL_TRIANGLES, 5*2*3, vertex_buffer_data_1, colors[this->type], GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*4*3, vertex_buffer_data_2, colors[this->type], GL_FILL);
}

void Monster::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex)
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

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}
