/**
 * Written by William Corsel - 2049481
 * For the Computer Graphics 2019 course at Leiden University
 * Has taken inspiration from Computer Graphics 2019 Workshop 1 code
 */

#include "AL/alut.h"
#include "GL/glut.h"
#include "build.h"
#include "camera.h"
#include "firework.h"
#include "lighting.h"
#include "sound.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

#define MOVEMENT_SPEED 2.0f
#define TURN_SPEED 0.08f

#define DEMO_FIREWORK_AMOUNT 10
#define DEMO_FIELD_SIZE 300.0

// Camera object
Camera *cam = new Camera();

// Builder object for start scene
Builder *builder = new Builder();

// Object for controlling lighting options
Lighting *light = new Lighting();

// Object for controlling sound effects
Sound *sound = new Sound();

// List with active fireworks
std::vector<Firework*> fireworks;

// Counter for looping over fireworks
int fireworkCount = 0;

// Text to be displayed
std::string text = "Fireworks!";

// Dimensions of the screen
float width = 1200;
float height = 800;

// Flag for enabling auto fire
bool fire = false;


// Cleans up objects
const void cleanup(){
    std::cout << "Cleanup" << std::endl;
	
	delete(sound);
    delete(cam);
    delete(builder);
    delete(light);
    

    for(int i = 0; i < (int)fireworks.size(); i++){
        delete(fireworks[i]);
    }
}


// Generates random positions for demo mode
Vector3 generateRandomPos(){
    float rx = (float)(rand() / (float)(RAND_MAX / DEMO_FIELD_SIZE));
    float rz = (float)(rand() / (float)(RAND_MAX / -DEMO_FIELD_SIZE));
    return Vector3(rx, 0.0, rz);
}


// Setup the demo gamemode
const void setupDemo(){
    fireworks.clear();
    cam->reset();
    for(int i = 0; i < DEMO_FIREWORK_AMOUNT; i++){
        fireworks.push_back(new Firework(generateRandomPos(), sound));
    }
}


// Render text
void renderText(){
    
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glRasterPos2d(300,270);
    for(int i = 0; i < (int)text.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}


// Render function
void update()
{
    Vector3 * g_pos = cam->getPosition();
    Vector3 * g_target = cam->getTargetPos();

    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    gluLookAt(g_pos->x(), g_pos->y(), g_pos->z(),
              g_pos->x() + g_target->x(), g_pos->y() + g_target->y(), g_pos->z() + g_target->z(),
              0.0f, 1.0f, 0.0f);
    
    light->updateLighting();
    if(sound->playing){
        sound->getSound();
    }

    renderText();
    
    builder->setColor(Vector4(0.663, 0.663, 0.663));
    builder->ground();

    for(int i = 0; i < (int)fireworks.size(); i++){
        fireworks[i]->draw();
    }

    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {

        // Movement
        case 'w':
            cam->forward(MOVEMENT_SPEED);
            break;
        case 's':
            cam->backward(MOVEMENT_SPEED);
            break;
        case 'a':
            cam->left(TURN_SPEED);
            break;
        case 'd':
            cam->right(TURN_SPEED);
            break;
        case 'z':
            cam->up(MOVEMENT_SPEED);
            break;
        case 'x':
            cam->down(MOVEMENT_SPEED);
            break;
        
        // Fire one
        case 'f':
            if((int)fireworks.size() <= 0)
                break;
            if(fireworkCount >= (int)fireworks.size())
                fireworkCount = 0;
            fireworks[fireworkCount]->fire();
            fireworkCount++;
            break;

        // Fire all
        case 'g':
            std::cout << "Firing all rockets" << std::endl;
            for(int i = 0; i < (int)fireworks.size(); i++){
                fireworks[i]->fire();
            }
            break;

        // Auto fire
        case 'h':
            std::cout << "Enable auto fire" << std::endl;
            fire = !fire;
            break;

        // Place down firework
        case 'p':{
            std::cout << "Placing new firework" << std::endl;
            Vector3 pos = Vector3(cam->getPosition()->x() + sin(cam->getRotation()) * 100, 0.0f, cam->getPosition()->z() + -cos(cam->getRotation()) * 100);
            fireworks.push_back(new Firework(pos, sound));
            break;
        }

        // Game modes
        case '1':{
            std::cout << "Setting demo mode" << std::endl;
            text = "Demo mode";
            setupDemo();
            break;
        }
        case '2':{
            std::cout << "Setting free roam" << std::endl;
            cam->reset();
            text = "Free roam";
            fireworks.clear();
            break;
        }

        // Mute
        case 'm':
            sound->switchEnable();
            break;

        // Home
        case 'r':
            cam->reset();
            break;

        // Exit
        case '-':
            cleanup();
            exit(0);

        //lighting movement
        case 'j': // move light left
            light->left();
            break;
        case 'l': // move light right
            light->right();
            break;
        case 'i':
            light->up();
            break;
        case 'k':
            light->down();
            break;
        
        // light properties
        case 'u': 
            light->toggleAmbient();
            break;
        case 'o':
            light->toggleDiffuse();
            break;
        case 'n': 
            light->toggleMaterial();
            break;
        
        //test
        case 'b':
            sound->playSound("sounds/fart.wav");
            break;

        default:
            break;
    }
    glutPostRedisplay();
}


// Timer function
void timer(int value)
{
    static int lastTime;
    int thisTime;
    float time;
    thisTime = glutGet(GLUT_ELAPSED_TIME);
    time = (thisTime - lastTime) / 500.0;
    lastTime = thisTime;

    if((int)fireworks.size() > 0 && fire && (thisTime / 1000) % 10  == (rand() % 9 + 1)){
        if(fireworkCount >= (int)fireworks.size())
                fireworkCount = 0;
        fireworks[fireworkCount]->fire();
        fireworkCount++;
    }

    for(int i = 0; i < (int)fireworks.size(); i++){
        fireworks[i]->gravityUpdate(time);
    }
    
    glutPostRedisplay();
    glutTimerFunc(50, &timer, 0);
}


// Reshape function for window reshaping
void reshape(int rwidth, int rheight)
{
    glViewport(0, 0, rwidth, rheight);
    width = rwidth;
    height = rheight;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, width / height, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}


// Initializes various glut options
const void initializeGlut(void){
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG2019 Final Project: Firework");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    light->initLighting();

    glutDisplayFunc(&update);
    glutKeyboardFunc(&keyboard);
    glutReshapeFunc(&reshape);
    glutTimerFunc(50, &timer, 0);
    //glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION); // Maybe add this for cleanup if possible on uni pc's
}

// Fills the fireworks vector with Fireworks
const void initialize(){
    // Fill with Fireworks if wanted
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    glutInit(&argc, argv);

    initializeGlut();
    initialize();
    
    glutMainLoop();

    cleanup();
    return 0;
}
