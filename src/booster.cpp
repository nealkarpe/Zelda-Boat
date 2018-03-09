#include "booster.h"
#include "main.h"

Booster::Booster(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    this->available = false;

    this->radius = 1.0f;

    float radius = this->radius;

    float height = 3.0f;

    static const GLfloat vertex_buffer_data_1[] = {
        radius, 0, radius,
        radius, 0, -radius,
        0, height, 0,

        -radius, 0, radius,
        -radius, 0, -radius,
        0, height, 0,

        radius, 0, radius,
        -radius, 0, radius,
        0, height, 0,

        radius, 0, -radius,
        -radius, 0, -radius,
        0, height, 0,

        radius, 0, radius,
        radius, 0, -radius,
        0, -height, 0,

        -radius, 0, radius,
        -radius, 0, -radius,
        0, -height, 0,

        radius, 0, radius,
        -radius, 0, radius,
        0, -height, 0,

        radius, 0, -radius,
        -radius, 0, -radius,
        0, -height, 0,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data_1, COLOR_DARKBLUE, GL_FILL);        
}

void Booster::tick() {
    this->rotation += 2.0;
}

void Booster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, -1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}
