#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z) {
    this->translate = glm::translate (glm::vec3(x, y, z));

    float length = 10000;
    float breadth = 10000;
    float depth = 1000;

    GLfloat vertex_buffer_data_1[1*2*9];

    this->addSquare(breadth,-breadth,0,0,length,-length,vertex_buffer_data_1,0);
    // this->addSquare(breadth,breadth,0,-depth,length,-length,vertex_buffer_data_1,1);
    // this->addSquare(breadth,-breadth,0,-depth,-length,-length,vertex_buffer_data_1,2);
    // this->addSquare(-breadth,-breadth,0,-depth,length,-length,vertex_buffer_data_1,3);
    // this->addSquare(breadth,-breadth,0,-depth,length,length,vertex_buffer_data_1,4);

    this->object1 = create3DObject(GL_TRIANGLES, 1*2*3, vertex_buffer_data_1, COLOR_BLUE, GL_FILL);
}

void Water::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr, int baseIndex) {
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

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *= (this->translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}
