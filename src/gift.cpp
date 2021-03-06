#include "gift.h"
#include "main.h"

Gift::Gift(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->available = false;
    this->type = rand() % 3;

    float scores[] = {1,2,0.2};
    color_t colors[] = {COLOR_PINK,COLOR_PURPLE,COLOR_BRICKRED};

    this->points = scores[this->type];
    this->radius = 1.0f;

    if(this->type==0 || this->type==1)
    {
        float n = 360;
        float r = this->radius;
        float theta = 2*M_PI/n;

        GLfloat vertex_buffer_data_1[360*9];

        int i;
        for(i=0; i<n; i++)
        {
                float angleBefore = theta * i;
                float angle = angleBefore + theta;

                float x = r * cos(angle);
                float y = r * sin(angle);
                float z = 0.0f;

                float x1 = r * cos(angleBefore);
                float y1 = r * sin(angleBefore);
                float z1 = 0.0f;

                float x2 = 0.0f;
                float y2 = 0.0f;
                float z2 = 0.0f;

                vertex_buffer_data_1[i*9] = x2;
                vertex_buffer_data_1[i*9+1] = y2;
                vertex_buffer_data_1[i*9+2] = z2;
                vertex_buffer_data_1[i*9+3] = x1;
                vertex_buffer_data_1[i*9+4] = y1;
                vertex_buffer_data_1[i*9+5] = z1;
                vertex_buffer_data_1[i*9+6] = x;
                vertex_buffer_data_1[i*9+7] = y;
                vertex_buffer_data_1[i*9+8] = z;
        }
        this->object1 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data_1, colors[this->type], GL_FILL);
    }

    else
    {
        this->position.y = 1.5;
        this->radius = 1.5;
        GLfloat vertex_buffer_data_1[2*2*9];

        float width = 0.45;

        this->addSquare(width,-width,radius,-radius,0,0,vertex_buffer_data_1,0);
        this->addSquare(radius,-radius,width,-width,0,0,vertex_buffer_data_1,1);

        this->object1 = create3DObject(GL_TRIANGLES, 2*2*3, vertex_buffer_data_1, colors[this->type], GL_FILL);        
    }
}

void Gift::tick() {
    this->rotation += 2.0;
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, -1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Gift::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex) {
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

