#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();
void cursorPosCB(GLFWwindow* window, double x, double y);
void shoot_fireball();
bool detect_collision_fireball_rock(int i, int j);
bool detect_collision_boat_rock(int j);
int detect_collision_boat_barrel(int j);
bool detect_collision_boat_monster(int j);
bool detect_collision_fireball_monster(int i, int j);
bool detect_collision_boat_gift(int j);
bool detect_collision_fireball_boss(int i);
bool detect_collision_boat_boss();
bool detect_collision_boat_booster();

extern float theta;
extern float yaw;

extern int camType;
extern bool boostFlag;
extern float totalBoost;

// ---- Colors ----
extern const color_t COLOR_BLACK;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_DARKBROWN;
extern const color_t COLOR_DARKESTBROWN;
extern const color_t COLOR_LIGHTBROWN;
extern const color_t COLOR_SEAGREEN;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_RED;
extern const color_t COLOR_BRICKRED;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_GREY;
extern const color_t COLOR_DARKBLUE;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_DARKRED;
extern const color_t COLOR_LIGHTGREY;
extern const color_t COLOR_GOLD;
extern const color_t COLOR_PURPLE;
extern const color_t COLOR_PINK;

#endif
