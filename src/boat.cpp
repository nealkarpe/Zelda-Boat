#include "boat.h"
#include "main.h"

#include <bits/stdc++.h>
using namespace std;

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->health = 1.0f;
    this->rotation = 0;
    this->Yspeed = 0.0f;
    this->downYspeed = 0.0f;
    this->acc = 0.01f;
    this->Yrotation = 0.0f;
    this->upStep = 0.5f;

    float length = 2;
    this->outerLength = 2.3;
    float breadth = 1;
    this->outerBreadth = 1.3;
    float height = 0.2;
    float upperHeight = 1;

    GLfloat vertex_buffer_data_1[5*2*9];
    GLfloat vertex_buffer_data_2[4*2*9];
    GLfloat vertex_buffer_data_3[4*2*9];
    GLfloat vertex_buffer_data_4[1*2*9];

    // base
    this->addSquare(this->outerBreadth,-this->outerBreadth,0,0,this->outerLength,-this->outerLength,vertex_buffer_data_1,0);

    // outer walls
    this->addSquare(this->outerBreadth,this->outerBreadth,upperHeight,0,this->outerLength,-this->outerLength,vertex_buffer_data_1,1);
    this->addSquare(-this->outerBreadth,-this->outerBreadth,upperHeight,0,this->outerLength,-this->outerLength,vertex_buffer_data_1,2);
    this->addSquare(this->outerBreadth,-this->outerBreadth,upperHeight,0,this->outerLength,this->outerLength,vertex_buffer_data_1,3);
    this->addSquare(this->outerBreadth,-this->outerBreadth,upperHeight,0,-this->outerLength,-this->outerLength,vertex_buffer_data_1,4);

    // inner walls
    this->addSquare(breadth,breadth,upperHeight,height,length,-length,vertex_buffer_data_2,0);
    this->addSquare(-breadth,-breadth,upperHeight,height,length,-length,vertex_buffer_data_2,1);
    this->addSquare(breadth,-breadth,upperHeight,height,length,length,vertex_buffer_data_2,2);
    this->addSquare(breadth,-breadth,upperHeight,height,-length,-length,vertex_buffer_data_2,3);

    // rail covering
    this->addSquare(this->outerBreadth,breadth,upperHeight,upperHeight,length,-length,vertex_buffer_data_3,0);
    this->addSquare(-breadth,-this->outerBreadth,upperHeight,upperHeight,length,-length,vertex_buffer_data_3,1);
    this->addSquare(this->outerBreadth,-this->outerBreadth,upperHeight,upperHeight,this->outerLength,length,vertex_buffer_data_3,2);
    this->addSquare(this->outerBreadth,-this->outerBreadth,upperHeight,upperHeight,-length,-this->outerLength,vertex_buffer_data_3,3);


    // boat floor
    this->addSquare(breadth,-breadth,height,height,length,-length,vertex_buffer_data_4,0);


    this->object1 = create3DObject(GL_TRIANGLES, 5*2*3, vertex_buffer_data_1, COLOR_DARKBROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*2*3, vertex_buffer_data_2, COLOR_DARKESTBROWN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 4*2*3, vertex_buffer_data_3, COLOR_BROWN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 1*2*3, vertex_buffer_data_4, COLOR_LIGHTBROWN, GL_FILL);

    GLfloat poleEnd = -1.1;
    GLfloat poleStart = -1;
    GLfloat poleWidth = 0.05;
    GLfloat poleHeight = 4;

    GLfloat vertex_buffer_data_5[5*2*9];

    this->addSquare(poleWidth,-poleWidth,poleHeight,height,poleEnd,poleEnd,vertex_buffer_data_5,0);
    this->addSquare(poleWidth,-poleWidth,poleHeight,height,poleStart,poleStart,vertex_buffer_data_5,1);
    this->addSquare(poleWidth,poleWidth,poleHeight,height,poleStart,poleEnd,vertex_buffer_data_5,2);
    this->addSquare(-poleWidth,-poleWidth,poleHeight,height,poleStart,poleEnd,vertex_buffer_data_5,3);
    this->addSquare(poleWidth,-poleWidth,poleHeight,poleHeight,poleStart,poleEnd,vertex_buffer_data_5,4);

    this->object5 = create3DObject(GL_TRIANGLES, 5*2*3, vertex_buffer_data_5, COLOR_WHITE, GL_FILL);

    GLfloat vertex_buffer_data_6[2*2*9 + 9];

    GLfloat holder1_start = poleHeight - 1;
    GLfloat holder1_end = holder1_start + 0.1;
    GLfloat holder2_start = poleHeight - 1.8;
    GLfloat holder2_end = holder2_start + 0.1;
    GLfloat holderEnd = -1.5;

    GLfloat flagStart = holder2_start - 0.8;
    GLfloat flagEnd = holder1_end + 0.8;
    GLfloat flagMid = (flagStart+flagEnd)/2;
    GLfloat flagDepthEnd = -2.5;

    this->addSquare(0,0,holder2_end,holder2_start,poleEnd,holderEnd,vertex_buffer_data_6,0);
    this->addSquare(0,0,holder1_end,holder1_start,poleEnd,holderEnd,vertex_buffer_data_6,1);

    const GLfloat flagCoords[] = {
        0, flagEnd, holderEnd,
        0, flagMid, flagDepthEnd,
        0, flagStart, holderEnd,
    };

    int i;
    for(i=0;i<9;i++) vertex_buffer_data_6[2*2*9+i] = flagCoords[i];
    this->object6 = create3DObject(GL_TRIANGLES, 2*2*3+3, vertex_buffer_data_6, COLOR_RED, GL_FILL);

}

void Boat::tick() {
    if(this->Yspeed>0) {
        this->position.y += this->Yspeed;
        this->Yspeed -= this->acc;
        if(this->Yspeed <= 0) {
            this->goDown = true;
            this->Yspeed = 0.0;
        }
    }

    if(this->goDown) {
        this->downYspeed += this->acc;
        if(this->position.y - this->downYspeed > 0.0) this->position.y -= this->downYspeed;
        else {
            this->position.y = 0.0;
            this->downYspeed = 0.0;
            this->goDown = false;
        }
    }

    this->Yrotation += this->upStep;
    if(this->Yrotation >= 9.0 || this->Yrotation <= -9.0) this->upStep = -this->upStep;
}

void Boat::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr, int baseIndex) {
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


void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, -1, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->Yrotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}
