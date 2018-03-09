#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data_1[] = {
        1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0,
        1.0, -1.0, 1.0,

        -1.0, -1.0, 1.0,
        -1.0, 1.0, 1.0,
        1.0, -1.0, 1.0,
    };

    static const GLfloat vertex_buffer_data_2[] = {
        1.0, 1.0, 1.0,
        1.0, -1.0, 1.0,
        1.0, 1.0, -1.0,

        1.0, -1.0, -1.0,
        1.0, -1.0, 1.0,
        1.0, 1.0, -1.0,
    };

    static const GLfloat vertex_buffer_data_3[] = {
        1.0, 1.0, -1.0,
        -1.0, 1.0, -1.0,
        1.0, -1.0, -1.0,

        -1.0, -1.0, -1.0,
        -1.0, 1.0, -1.0,
        1.0, -1.0, -1.0,
    };

    static const GLfloat vertex_buffer_data_4[] = {
        -1.0, 1.0, 1.0,
        -1.0, -1.0, 1.0,
        -1.0, 1.0, -1.0,

        -1.0, -1.0, -1.0,
        -1.0, -1.0, 1.0,
        -1.0, 1.0, -1.0,
    };

    static const GLfloat vertex_buffer_data_5[] = {
        1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0,
        1.0, 1.0, -1.0,

        1.0, 1.0, -1.0,
        -1.0, 1.0, 1.0,
        -1.0, 1.0, -1.0,
    };

    static const GLfloat vertex_buffer_data_6[] = {
        1.0, -1.0, 1.0,
        -1.0, -1.0, 1.0,
        1.0, -1.0, -1.0,

        1.0, -1.0, -1.0,
        -1.0, -1.0, 1.0,
        -1.0, -1.0, -1.0,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_1, COLOR_BLUE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_GREEN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_4, COLOR_RED, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_5, COLOR_LIGHTGREY, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_6, COLOR_BROWN, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

