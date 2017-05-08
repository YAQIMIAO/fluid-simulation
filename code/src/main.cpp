/*
 Main skeleton code was from UC Berkeley's CS184 Fall 2016 course, assignment 3.
 This is the modified version for UC Berkeley's CS184 Spring 2017 course, Final Project.
 */


//include header file for glfw library so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>
#include <time.h>
#include <math.h>
#include <cstring>
#include "CGL/CGL.h"
#include "CGL/vector3D.h"
#include "CGL/matrix3x3.h"
#include "CGL/lodepng.h"
#include <glm/glm.hpp>


//#define PI 3.14159265 // Should be used from mathlib

using namespace std;
using namespace CGL;


#define OUTPUT_ANIMATION 0

#include <stdlib.h>
#include <stdio.h>

#include "SolidSphere.cpp"
#include "Particles.h"

#if OUTPUT_ANIMATION
#include <opencv2/opencv.hpp>
#endif

//****************************************************
// Global Variables
//****************************************************

bool auto_strech = false;
int Z_buffer_bit_depth = 128;

inline float sqr(float x) { return x*x; }
GLfloat viewX = 0;
GLfloat viewY = 0;
GLfloat viewZ = 0;
float rotateX = 180;
float rotateY = 0;

float angle = 0;


float theta = M_PI/8;
float phi = -M_PI/8+M_PI_2;
float dist = 2.5;
int width = 400;
int height = 400;
int frame = 0;
const int render_step = 3;
int mx, my;

Particles waterCube;

Particles testCube;

float BOUNDING_BOX_LENGTH = 2.0f;


//****************************************************
// Simple init function
//****************************************************
void initializeRendering()
{
    glfwInit();
}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************
void setPixel(float x, float y, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glVertex2f(x+0.5, y+0.5);  // The 0.5 is to target pixel centers
    // Note: Need to check for gap bug on inst machines.
}


//****************************************************
// helper functions
//***************************************************

void drawCube(float box_length = 2.0f) {
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);                // Begin drawing the color cube with 6 quads

//front
    glVertex3f(-box_length, box_length, box_length);
    glVertex3f(box_length, box_length, box_length);

    glVertex3f(box_length, box_length, box_length);
    glVertex3f(box_length, -box_length, box_length);

    glVertex3f(box_length, -box_length, box_length);
    glVertex3f(-box_length, -box_length, box_length);

    glVertex3f(-box_length, -box_length, box_length);
    glVertex3f(-box_length, box_length, box_length);

//right
    glVertex3f(box_length, box_length, box_length);
    glVertex3f(box_length, box_length, -box_length);

    glVertex3f(box_length, box_length, -box_length);
    glVertex3f(box_length, -box_length, -box_length);

    glVertex3f(box_length, -box_length, -box_length);
    glVertex3f(box_length, -box_length, box_length);

//back
    glVertex3f(box_length, box_length, -box_length);
    glVertex3f(-box_length, box_length, -box_length);

    glVertex3f(-box_length, -box_length, -box_length);
    glVertex3f(box_length, -box_length, -box_length);

    glVertex3f(-box_length, -box_length, -box_length);
    glVertex3f(-box_length, box_length, -box_length);

//left
    glVertex3f(-box_length, box_length, -box_length);
    glVertex3f(-box_length, box_length, box_length);

    glVertex3f(-box_length, -box_length, box_length);
    glVertex3f(-box_length, -box_length, -box_length);
    glEnd();
}

inline float clip(const float& n, const float& lower, const float& upper)
{
    return glm::max(lower, glm::min(n, upper));
}


//****************************************************
// function that does the actual drawing of stuff
//***************************************************

void display( GLFWwindow* window )
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); //clear background screen to black
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                // clear the color buffer (sets everything to black)
    glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
    glLoadIdentity();                            // make sure transformation is "zero'd"
    
    //----------------------- code to draw objects --------------------------
    glPushMatrix();
    glTranslatef(viewX, viewY, viewZ);
    glRotatef(rotateX, 0, 1, 0); //rotates the cube below
    glRotatef(rotateY, 1, 0, 0);
    

    //gluPerspective(90, 1, 1, 1.2);
    //gluLookAt(dist*sin(phi)*cos(theta), dist*cos(phi), dist*sin(phi)*sin(theta),
    //        0, 0, 0,
    //        0, 1, 0);
    
    // drawing start

    drawCube(BOUNDING_BOX_LENGTH);
    testCube.render();


    glPopMatrix();
    
    glfwSwapBuffers(window);
    
    // note: check out glPolygonMode and glShadeModel
    // for wireframe and shading commands
}



void updateDisplay( GLFWwindow* window ){
    /*
     * original skeleton
    int dx = x - mx;
    int dy = y - my;
    mx = x;
    my = y;
    if(abs(dx) > abs(dy))
        theta += dx*0.005;
    else
        phi -= dy*0.005;
    if(theta > 2*M_PI)
        theta -= 2*M_PI;
    if(theta < -2*M_PI)
        theta += 2*M_PI;
    phi = clip(phi, M_PI/12, M_PI*11/12);
     */
    testCube.simulate(10, 1);
    display(window);
    
}






//******************
// Keyboard inputs
//******************
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
            
        case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, 1); break;
        case GLFW_KEY_Q: glfwSetWindowShouldClose(window, 1); break;
        case GLFW_KEY_LEFT :
            if (action && mods == GLFW_MOD_SHIFT) viewX -= 0.001f * width;
            else rotateX += 0.01f * width;
            break;
        case GLFW_KEY_RIGHT:
            if (action && mods == GLFW_MOD_SHIFT) viewX += 0.001f * width;
            else rotateX -= 0.01f * width;
            break;
        case GLFW_KEY_UP   :
            if (action && mods == GLFW_MOD_SHIFT) viewY += 0.001f * height;
            else rotateY += 0.01f * height;
            break;
        case GLFW_KEY_DOWN :
            if (action && mods == GLFW_MOD_SHIFT) viewY -= 0.001f * height;
            else rotateY -= 0.01f * height;
            break;
        case GLFW_KEY_SPACE:
            updateDisplay(window);
            break;
            
        default: break;
    }
    
}


//******************
// Mouse inputs
//******************

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        mx = x;
        my = y;
    }
}


static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    
    
}




//****************************************************
// function that is called when window is resized
//***************************************************
void size_callback(GLFWwindow* window, int w, int h)
{
    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the framebuffer of the specified window
    glfwGetFramebufferSize(window, &w, &h);
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, 1, -1);
    
    display(window);
}


/* not sure what idle is doing here???
void idle(void)
{
    particles.step();
    glutPostRedisplay();
    if(frame/render_step >= 300)
        return;
    if(frame%render_step == 0)
    {
        #if OUTPUT_ANIMATION
        cv::Mat3b image(height, width);
        glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, image.data);
        cv::flip(image, image, 0);
        char fn[512];
        sprintf(fn, "result/%04d.png", frame/render_step);
        cv::imwrite(fn, image);
        #endif
    }
    frame++;
}
 */


//********
// main
//********


int main(int argc, char** argv)
{
    //testCube = Particles(1.0, 1.0, 10, 0.1, 10.0);
    testCube = Particles();



    //This initializes glfw
    initializeRendering();

    GLFWwindow* window = glfwCreateWindow( width, height, "Fluid Simulation", NULL, NULL );
    if ( !window )
    {
        //std::cout << "Error on window creating" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if ( !mode )
    {
        //std::cout << "Error on getting monitor" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent( window );

    
    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the framebuffer of the specified window
    glfwGetFramebufferSize(window, &width, &height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.5, 3.5, -3.5, 3.5, 5, -5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    // shading

    glShadeModel(GL_NORMALIZE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    
    float diffuse[]={0.2, 0.7, 0.6, 0.5};
    float ambient[]={0.2, 0.7, 0.6, 0.5};
    float specular[]={1.0, 0.0, 0.0, 1.0};

    // need to experiment with a better light position
    // this position is giving me aids currently
    float light0_pos[]={-1.0, 2.0, -2.0, 1.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    
    glEnable(GL_LIGHT0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    
    /* original glut skeleton

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMotionFunc(motion);
    glutMainLoop();
    glutKeyboardFunc(keyboard);
     */


    glEnable(GL_DEPTH_TEST);	// enable z-buffering
    glDepthFunc(GL_LESS);
    
    glfwSetWindowTitle(window, "Fluid Simulation");
    glfwSetWindowSizeCallback(window, size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    while( !glfwWindowShouldClose( window ) ) // infinite loop to draw object again and again
    {   // because once object is draw then window is terminated
        display( window );
        
        if (auto_strech){
            glfwSetWindowSize(window, mode->width, mode->height);
            glfwSetWindowPos(window, 0, 0);
        }
        
        glfwPollEvents();
        
    }

    return EXIT_SUCCESS;
}



