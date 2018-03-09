#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "boat.h"
#include "rock.h"
#include "fireball.h"
#include "cannon.h"
#include "barrel.h"
#include "coin.h"
#include "monster.h"
#include "gift.h"
#include "boss.h"
#include "booster.h"

#define NUM_ROCKS 200
#define NUM_BARRELS 100
#define NUM_MONSTERS 100

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int numTicks = 0;
bool windFlag = false;
float windAngle = 0.0;

int width  = 600;
int height = 600;

int score = 0;
int killCount = 0;

float screen_zoom = 0.2, screen_center_x = 0, screen_center_y = 0;

float cam_distance = 300.0;
float theta = 30.0;

float yaw = 0;
int camType = 0,i,j;

Water water;
Boat boat;
Rock rocks[NUM_ROCKS];
Barrel barrels[NUM_BARRELS];
Coin coins[NUM_BARRELS];
Monster monsters[NUM_MONSTERS];
Gift gifts[NUM_MONSTERS];
Boss boss;
Booster booster;

float bound = 600.0;

Fireball fireballs[20];
Cannon cannon;
int FBcount = 0;
float FBangle = 0.0f;

float totalBoost = 0.0;
bool boostFlag = false;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    glm::vec3 up (0, 1, 0);

    if(camType==0)
    {
        float r = cam_distance*cos(theta*M_PI/180.0f);
        float angle = boat.rotation + yaw;
        glm::vec3 eye (boat.position.x - r*sin(angle*M_PI/180.0f) , boat.position.y + cam_distance*sin(theta*M_PI/180.0f), boat.position.z + r*cos(angle*M_PI/180.0f));
        glm::vec3 target (boat.position.x, boat.position.y, boat.position.z);
        Matrices.view = glm::lookAt( eye, target, up );
    }

    else if(camType==1)
    {

        float angle = boat.rotation;
        float targDistance = 20.0f;
        glm::vec3 target (boat.position.x + targDistance*sin(angle*M_PI/180.0f), 0, boat.position.z - targDistance*cos(angle*M_PI/180.0f));
        float r = cam_distance*cos(theta*M_PI/180.0f);
        glm::vec3 eye (target.x - r*sin(angle*M_PI/180.0f) , target.y + cam_distance*sin(theta*M_PI/180.0f), target.z + r*cos(angle*M_PI/180.0f));
        Matrices.view = glm::lookAt( eye, target, up );
    }

    else if(camType==2)
    {
        glm::vec3 eye (boat.position.x, boat.position.y+12, boat.position.z);
        glm::vec3 target (boat.position.x + 100*sin(boat.rotation*M_PI/180.0f), boat.position.y, boat.position.z - 100*cos(boat.rotation*M_PI/180.0f));
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }

    else if(camType==3)
    {
        float r = cam_distance*cos(theta*M_PI/180.0f);
        float angle = boat.rotation;
        glm::vec3 eye (boat.position.x - r*sin(angle*M_PI/180.0f) , boat.position.y + cam_distance*sin(theta*M_PI/180.0f), boat.position.z + r*cos(angle*M_PI/180.0f));
        glm::vec3 target (boat.position.x, boat.position.y, boat.position.z);
        Matrices.view = glm::lookAt( eye, target, up );
    }

    else if(camType==4)
    {
        float r = cam_distance*cos(theta*M_PI/180.0f);
        float angle = boat.rotation;
        glm::vec3 eye (boat.position.x + r*cos(angle*M_PI/180.0f) , boat.position.y + cam_distance*sin(theta*M_PI/180.0f), boat.position.z + r*sin(angle*M_PI/180.0f));
        glm::vec3 target (boat.position.x, boat.position.y, boat.position.z);
        Matrices.view = glm::lookAt( eye, target, up );
    }

    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    water.draw(VP);
    boat.draw(VP);
    for(i=0;i<NUM_ROCKS;i++) rocks[i].draw(VP);
    for(i=0;i<NUM_BARRELS;i++) {
        barrels[i].draw(VP);
        coins[i].draw(VP);
    }
    for(i=0;i<NUM_MONSTERS;i++) {
        if(monsters[i].alive) monsters[i].draw(VP);
        else if(gifts[i].available) gifts[i].draw(VP);
    }

    for(i=0;i<20;i++) {
        if(fireballs[i].alive) fireballs[i].draw(VP);
    }

    if(boss.alive) boss.draw(VP);

    cannon.draw(VP);
    if(booster.available) booster.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int n = glfwGetKey(window, GLFW_KEY_N);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);

    if (left && camType==0) {
        yaw -= 1;
        if(yaw<0) yaw += 360;
    }
    if (right && camType==0) {
        yaw += 1;
        if(yaw>=360) yaw -= 360;
    }
    if (up && camType==0) {
        if(theta+1<=85) theta += 1;
    }
    if (down && camType==0) {
        if(theta-1>=5) theta -= 1;
    }
    if (m && camType==0) {
        if(screen_zoom - 0.01 >= 0.02) {
            screen_zoom -= 0.01;
            reset_screen();
        }
    }
    if (n && camType==0) {
        if(screen_zoom + 0.01 <= 1.0) {
            screen_zoom += 0.01;
            reset_screen();
        }
    }
    if (w) {
        float delta = 0.6;
        if(boostFlag) {
            float add = 0.4;
            if(totalBoost > add) {
                totalBoost -= add;
                delta += add;
            }
            else {
                delta += totalBoost;
                totalBoost = 0.0;
                boostFlag = false;
            }
        }

        boat.position.z -= delta * cos(boat.rotation*M_PI/180.0f);
        boat.position.x += delta * sin(boat.rotation*M_PI/180.0f);

        bool collisionFlag = false;

        if(boss.alive && detect_collision_boat_boss()) {
            collisionFlag = true;
            boat.health -= 0.04;
            cout << "BOSS COLLISION" << endl;
            boat.position.z += delta * cos(boat.rotation*M_PI/180.0f);
            boat.position.x -= delta * sin(boat.rotation*M_PI/180.0f);
        }

        if(booster.available && detect_collision_boat_booster()) {
            collisionFlag = true;
            totalBoost += 400.0;
            booster.available = false;
        }

        if(!collisionFlag)
        {
            for(i=0;i<NUM_BARRELS;i++) {
                int collision = detect_collision_boat_barrel(i);
                if(collision==1) {
                    collisionFlag = true;
                    cout << "BARREL COLLISION" << endl;
                    boat.position.z += delta * cos(boat.rotation*M_PI/180.0f);
                    boat.position.x -= delta * sin(boat.rotation*M_PI/180.0f);
                    break;
                }
                else if(collision==2) {
                    collisionFlag = true;
                    score += coins[i].points;
                    barrels[i].position.x = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
                    barrels[i].position.z = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
                    coins[i].position.x = barrels[i].position.x;
                    coins[i].position.z = barrels[i].position.z;
                }
            }
        }
        if(!collisionFlag)
        {
            for(i=0;i<NUM_ROCKS;i++) {
                if(detect_collision_boat_rock(i)) {
                    collisionFlag = true;
                    boat.health-=0.002;
                    cout << "ROCK COLLISION" << endl;
                    boat.position.z += delta * cos(boat.rotation*M_PI/180.0f);
                    boat.position.x -= delta * sin(boat.rotation*M_PI/180.0f);
                    break;
                }
            }
        }
        if(!collisionFlag)
        {
            for(i=0;i<NUM_MONSTERS;i++) {
                if(monsters[i].alive && detect_collision_boat_monster(i)) {
                    collisionFlag = true;
                    boat.health-=0.015;
                    cout << "MONSTER COLLISION" << endl;
                    boat.position.z += delta * cos(boat.rotation*M_PI/180.0f);
                    boat.position.x -= delta * sin(boat.rotation*M_PI/180.0f);
                    break;
                }
            }
        }
    }


    if (s) {
        boat.position.z += 0.6 * cos(boat.rotation*M_PI/180.0f);
        boat.position.x -= 0.6 * sin(boat.rotation*M_PI/180.0f);
    }
    if (d) {
        if(yaw!=0.0f) {
            boat.rotation = boat.rotation + yaw;
            yaw = 0.0f;
        }
        else {
            boat.rotation += 1;
        }
        if(boat.rotation>=360) boat.rotation -= 360;
    }
    if (a) {
        if(yaw!=0.0f) {
            boat.rotation = boat.rotation + yaw;
            if(boat.rotation>=360) boat.rotation -= 360;
            yaw = 0.0f;
        }        
        else {
            boat.rotation -= 1;
            if(boat.rotation<0) boat.rotation += 360;
        }
    }
    if (space) {
        if(boat.Yspeed<=0.0 && !boat.goDown) {
            boat.Yspeed = 0.24;
        }
    }

    cannon.position.x = boat.position.x;
    cannon.position.z = boat.position.z;
}

void tick_elements() {
    if(windFlag) {

    if(boat.rotation != windAngle) {
        if(boat.rotation < 180) {
            if(windAngle > boat.rotation && windAngle <= boat.rotation+180) {
                float diff = windAngle - boat.rotation;
                if(diff < 1.0) boat.rotation = windAngle;
                else boat.rotation += 1.0;
            }
            else {
                float diff = (360-windAngle) + boat.rotation;
                if(windAngle >= 0) {
                    diff = boat.rotation - windAngle;
                }
                if(diff < 1.0) boat.rotation = windAngle;
                else {
                    boat.rotation -= 1.0;
                    if(boat.rotation<0) boat.rotation += 360.0;
                }
            }
        }
        else {
            if(windAngle < boat.rotation && windAngle >= boat.rotation-180) {
                float diff = boat.rotation - windAngle;
                if(diff<1.0) boat.rotation = windAngle;
                else boat.rotation -= 1.0;
            }
            else {
                float diff = windAngle + (360 - boat.rotation);
                if(windAngle > boat.rotation) {
                    diff = windAngle - boat.rotation;
                }
                if(diff < 1.0) boat.rotation = windAngle;
                else {
                    boat.rotation += 1.0;
                    if(boat.rotation >= 360) boat.rotation -= 360.0;
                }
            }
        }
    }

    }

    if(boat.health<=0.0) {
        quit(window);
    }
    boat.tick();
    if(boss.alive) boss.tick();

    for(i=0;i<20;i++) {
        if(fireballs[i].alive) {
            fireballs[i].tick();
            for(j=0;j<NUM_ROCKS;j++)
            {
                if(detect_collision_fireball_rock(i,j)) {
                    fireballs[i].alive=false;
                    break;
                }
            }

            if(!fireballs[i].alive) continue;
            for(j=0;j<NUM_MONSTERS;j++)
            {
                if(monsters[i].alive && detect_collision_fireball_monster(i,j)) {
                    fireballs[i].alive=false;
                    monsters[j].alive=false;
                    gifts[j].available=true;
                    float a = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
                    float b = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
                    monsters[j].position.x = a;
                    monsters[j].position.z = b;
                    killCount++;
                    break;
                }
            }
            if(!fireballs[i].alive) continue;
            if(boss.alive && detect_collision_fireball_boss(i)) {
                fireballs[i].alive=false;
                boss.life--;
                if(boss.life<=0) {
                    boss.alive = false;
                    booster.available = true;
                    booster.position.x = boss.position.x;
                    booster.position.z = boss.position.z;
                }
            }
        }
    }

    cannon.position.y = boat.position.y + 1.0;
    for(i=0; i<NUM_BARRELS; i++) coins[i].tick();
    for(i=0; i<NUM_MONSTERS; i++){
        if(gifts[i].available) gifts[i].tick();
    }

    for(i=0; i<NUM_MONSTERS; i++){
        if(gifts[i].available && detect_collision_boat_gift(i)) {
            if(gifts[i].type<=1) score += gifts[i].points;
            else {
                boat.health += gifts[i].points;
                if(boat.health >= 1.0) boat.health = 1.0;
            }
            gifts[i].available = false;
            monsters[i].alive = true;
            gifts[i].position.x = monsters[i].position.x;
            gifts[i].position.z = monsters[i].position.z;
            break;
        };
    }

    if(killCount>=3)
    {
        killCount = 0;
        boss.position.x = boat.position.x;
        boss.position.z = boat.position.z - 10;
        boss.alive = true;
        boss.life = 3;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water = Water(0, 0, 0);
    boat = Boat(0, 0, 0);
    for(i=0;i<NUM_ROCKS;i++)
    {
        float a = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
        float b = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
        rocks[i] = Rock(a, 0 , b);
    }
    for(i=0;i<NUM_BARRELS;i++)
    {
        float a = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
        float b = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
        barrels[i] = Barrel(a, 0 , b);
        coins[i] = Coin(a, 3, b);
    }
    for(i=0;i<NUM_MONSTERS;i++)
    {
        float a = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
        float b = ((float)rand()/(float)RAND_MAX - 0.5f) * bound;
        monsters[i] = Monster(a, 0 , b);
        gifts[i] = Gift(a, 1.0 , b);
    }

    boss = Boss(0,0,0);

    for(i=0;i<20;i++) fireballs[i] = Fireball(0.0f,1.0f,0.0f);

    cannon = Cannon(0.0,1.0,0.0);
    booster = Booster(0,3.0,0);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));

    window = initGLFW(width, height);

    initGL (window, width, height);

    glfwSetCursorPosCallback(window,cursorPosCB);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            numTicks++;
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
 
            char titleString[128];
            if(boostFlag) sprintf(titleString, "Score: %d, Health: %.2f, Boost: %.2f, Booster ON, View: %d, Zoom: %.2f", score, boat.health, totalBoost, camType, screen_zoom);
            else sprintf(titleString, "Score: %d, Health: %.2f, Boost: %.2f, Booster OFF, View: %d, Zoom: %.2f", score, boat.health, totalBoost, camType, screen_zoom);
            glfwSetWindowTitle(window,titleString);

            if(!windFlag && numTicks>=1500) {
                numTicks = 0;
                windFlag = true;
                windAngle = (float) (rand()%360);
                cout << "wind angle:" << windAngle << endl;
            }
            else if(windFlag && numTicks>=100) {
                windFlag = false;
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void cursorPosCB(GLFWwindow* window, double x, double y)
{
    glm::vec4 temp = glm::inverse(Matrices.projection) * glm::vec4(-1+(x*2)/(float)width, 1-(y*2)/(float)height, -1.0f, 1.0f);

    glm::vec4 WC = glm::inverse(Matrices.view) * glm::vec4(temp.x, temp.y, -1.0, 0.0);

    float MouseX = WC.x;
    float MouseZ = WC.z;

    float angle = 0.0f;

    if(MouseZ==0.0f)
    {
        if(MouseX>=0) angle = 90.0;
        else angle = 270.0;
    }
    else
    {
        angle = atan((MouseX-0.0)/(0.0-MouseZ))*180.0/M_PI;
        if(MouseZ<0.0f) {
            if(MouseX<0) {
                angle += 360.0;
            }
        }

        else if(MouseZ>0.0f) {
            angle += 180.0f;
        }
    }

    FBangle = angle;
    cannon.rotation = angle;
}


void shoot_fireball()
{
    float x_offset = cannon.length * sin(FBangle*M_PI/180.0f);
    float z_offset = cannon.length * cos(FBangle*M_PI/180.0f);
    fireballs[FBcount].alive = true;
    fireballs[FBcount].position.x = boat.position.x + x_offset;
    fireballs[FBcount].position.y = boat.position.y + 1.0;
    fireballs[FBcount].position.z = boat.position.z - z_offset;
    fireballs[FBcount].angle = FBangle;
    fireballs[FBcount].dist = 0.0f;
    FBcount = (FBcount + 1) % 20;
}

bool detect_collision_fireball_boss(int i) {
    if(
        abs(fireballs[i].position.x - boss.position.x) < fireballs[i].size + boss.width &&
        abs(fireballs[i].position.z - boss.position.z) < fireballs[i].size + boss.width        
        ) return true;
    return false;
}

bool detect_collision_boat_boss() {
    if(
        abs(boat.position.x - boss.position.x) < boat.outerBreadth + boss.width &&
        abs(boat.position.z - boss.position.z) < boat.outerLength + boss.width
        ) return true;
    return false;
}

bool detect_collision_boat_booster() {
    if(
        abs(boat.position.x - booster.position.x) < boat.outerBreadth + booster.radius &&
        abs(boat.position.z - booster.position.z) < boat.outerLength + booster.radius
        ) return true;
    return false;
}


bool detect_collision_boat_gift(int j) {
    if(boat.position.y < 2*gifts[j].radius &&
        abs(boat.position.x - gifts[j].position.x) < boat.outerBreadth + gifts[j].radius &&
        abs(boat.position.z - gifts[j].position.z) < boat.outerLength + gifts[j].radius
        ) return true;
    return false;
}

bool detect_collision_fireball_monster(int i, int j) {
    if(fireballs[i].position.y-fireballs[i].size < 2*monsters[j].width &&
        abs(fireballs[i].position.x - monsters[j].position.x) < fireballs[i].size + monsters[j].width &&
        abs(fireballs[i].position.z - monsters[j].position.z) < fireballs[i].size + monsters[j].width        
        ) return true;
    return false;
}

bool detect_collision_boat_monster(int j) {
    if(boat.position.y < 2*monsters[j].width &&
        abs(boat.position.x - monsters[j].position.x) < boat.outerBreadth + monsters[j].width &&
        abs(boat.position.z - monsters[j].position.z) < boat.outerLength + monsters[j].width
        ) return true;
    return false;
}

int detect_collision_boat_barrel(int j) {
    if(abs(boat.position.x - barrels[j].position.x) < boat.outerBreadth + barrels[j].barrelSize &&
        abs(boat.position.z - barrels[j].position.z) < boat.outerLength + barrels[j].barrelSize) {
        if(boat.position.y>=barrels[j].barrelSize) {
            return 2;
        }
        else {
            return 1;
        }
    }
    else {
        return 0;
    }
}

bool detect_collision_boat_rock(int j) {
    if(boat.position.y < 2*rocks[j].rockSize &&
        abs(boat.position.x - rocks[j].position.x) < boat.outerBreadth + rocks[j].rockSize &&
        abs(boat.position.z - rocks[j].position.z) < boat.outerLength + rocks[j].rockSize
        ) return true;
    return false;
}

bool detect_collision_fireball_rock(int i, int j) {
    if(fireballs[i].position.y-fireballs[i].size < 2*rocks[j].rockSize &&
        abs(fireballs[i].position.x - rocks[j].position.x) < fireballs[i].size + rocks[j].rockSize &&
        abs(fireballs[i].position.z - rocks[j].position.z) < fireballs[i].size + rocks[j].rockSize        
        ) return true;
    return false;
}
