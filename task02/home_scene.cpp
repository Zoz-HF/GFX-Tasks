#define _USE_MATH_DEFINES

#include <cmath>
#include <glew.h>
#include <freeglut.h>
#include <cstdlib>

// global variables
const int XSUN = 350;
const int YSUN = 250;
const int RSUN = 20;

const int XTREE = 225;
const int YTREE = 100;
const int RTREE = 25;

const int XRAYS = XSUN;
const int YRAYS = YSUN;

const int RAY_LENGTH = 10;
// notice, the full of  the sun is ( 2*(RSUN + RAY_LENGTH) )



// Drawing routine.
void drawScene(void) {
    // clearing the buffer and setting the drawing color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glColor3f(10, 10, 0);
    // the sun
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(XSUN, YSUN);
    for (int i = 0; i < 38; i++)
        glVertex2f(XSUN + RSUN * cos(i * 10 * M_PI / 180), YSUN + RSUN * sin(i * 10 * M_PI / 180));
    glEnd();

    // the ground
    glLineWidth(3.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(900, -10, 0.0);
    glVertex3f(900, 19, 0.0);
    glVertex3f(-100, 19, 0.0);
    glVertex3f(-100, -10, 0.0);
    glEnd();

    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
    glVertex3f(900, -10, 0.0);
    glVertex3f(900, 19, 0.0);
    glVertex3f(-100, 19, 0.0);
    glVertex3f(-100, -10, 0.0);
    glEnd();

    // the tree
    glColor3f(0.588, 0.294, 0);
    glBegin(GL_POLYGON);
    glVertex3f(215, 19, 0.0);
    glVertex3f(235, 19, 0.0);
    glVertex3f(235, 99, 0.0);
    glVertex3f(228, 99, 0.0);
    glVertex3f(225, 82, 0.0);
    glVertex3f(222, 99, 0.0);
    glVertex3f(215, 99, 0.0);
    glEnd();

    glColor3ub(34, 139, 34);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(XTREE, YTREE);
    for (int i = 0; i < 38; i++)
        glVertex2f(XTREE + RTREE * cos(i * 10 * M_PI / 180), YTREE + RTREE * sin(i * 10 * M_PI / 180));
    glEnd();

    // the rays
    glColor3f(10, 10, 0);
    glBegin(GL_LINES);

    for (int i = 0; i < 38; i++) {
        glVertex2f(XRAYS + RSUN * cos(i * 10 * M_PI / 180), YRAYS + RSUN * sin(i * 10 * M_PI / 180));
        glVertex2f(XRAYS + (RSUN + RAY_LENGTH) * cos(i * 10 * M_PI / 180),
                   YRAYS + (RSUN + RAY_LENGTH) * sin(i * 10 * M_PI / 180));
    }
    glEnd();

    // The spirals acting like clouds
    float RSPIRAL = 30.0; // Radius of circle.
    float XSPIRAL[3] = {250.0, 220.0, 200}; // X-coordinate of center of circle.
    float YSPIRAL = 200.0; // Y-coordinate of center of circle.
    static int numVertices = 500; // Number of vertices on circle.


    for (int j = 0; j < 3; j++) {
        float t = 0; // Angle parameter.
        float t_prev = 0;
        glBegin(GL_LINES);
        for (int i = 0; i < numVertices; ++i) {
            glColor3f(1, 1, 1);
            glVertex3f(XSPIRAL[j] + ((RSPIRAL / 20) * t_prev) * cos(t_prev),
                       YSPIRAL + ((RSPIRAL / 20) * t_prev) * sin(t_prev),
                       0.0);
            glVertex3f(XSPIRAL[j] + ((RSPIRAL / 20) * t) * cos(t), YSPIRAL + ((RSPIRAL / 20) * t) * sin(t), 0.0);
            t_prev = t;
            t += 2 * M_PI / 180;
        }
        glEnd();
    }

    float XSPIRAL2[2] = {250.0, 220.0}; // X-coordinate of center of circle.
    YSPIRAL = 220.0;
    for (int j = 0; j < 2; j++) {
        float t = 0; // Angle parameter.
        float t_prev = 0;
        glBegin(GL_LINES);
        for (int i = 0; i < numVertices; ++i) {
            glColor3f(1, 1, 1);
            glVertex3f(XSPIRAL2[j] + ((RSPIRAL / 20) * t_prev) * cos(t_prev),
                       YSPIRAL + ((RSPIRAL / 20) * t_prev) * sin(t_prev),
                       0.0);
            glVertex3f(XSPIRAL2[j] + ((RSPIRAL / 20) * t) * cos(t), YSPIRAL + ((RSPIRAL / 20) * t) * sin(t), 0.0);
            t_prev = t;
            t += 2 * M_PI / 180;
        }
        glEnd();
    }
    // Draw House with black outline //
    // ----------------------------- //

    // main building outline
    glLineWidth(5.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(30, 120, 0.0);
    glVertex3f(30, 20, 0.0);
    glVertex3f(190, 20, 0.0);
    glVertex3f(190, 120, 0.0);
    glEnd();

    // left window's outline
    glLineWidth(5.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(45, 100, 0.0);
    glVertex3f(45, 70, 0.0);
    glVertex3f(75, 70, 0.0);;
    glVertex3f(75, 100, 0.0);
    glEnd();

    // right window's outline
    glLineWidth(5.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(175, 70, 0.0);
    glVertex3f(175, 100, 0.0);
    glVertex3f(145, 100, 0.0);
    glVertex3f(145, 70, 0.0);
    glEnd();

    // the house with triangle strip
    glColor3f(0.996, 0.8745, 0.0941);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(30, 120, 0.0);        // vertex 01
    glVertex3f(45, 100, 0.0);        // vertex 02
    glVertex3f(30, 20, 0.0);         // vertex 03
    glVertex3f(45, 70, 0.0);         // vertex 04
    glVertex3f(110, 20, 0.0);        // vertex 05
    glVertex3f(75, 70, 0.0);;        // vertex 06
    glVertex3f(145, 70, 0.0);        // vertex 07
    glVertex3f(110, 20, 0.0);        // vertex 08
    glVertex3f(190, 20, 0.0);        // vertex 09
    glVertex3f(145, 70, 0.0);        // vertex 10
    glVertex3f(175, 70, 0.0);        // vertex 11
    glVertex3f(190, 20, 0.0);        // vertex 12
    glVertex3f(190, 120, 0.0);       // vertex 13
    glVertex3f(175, 70, 0.0);        // vertex 14
    glVertex3f(175, 100, 0.0);       // vertex 15
    glVertex3f(190, 120, 0.0);       // vertex 16
    glVertex3f(110, 120, 0.0);       // vertex 17
    glVertex3f(175, 100, 0.0);       // vertex 18
    glVertex3f(145, 100, 0.0);       // vertex 19
    glVertex3f(110, 120, 0.0);       // vertex 20
    glVertex3f(75, 100, 0.0);       // vertex 21
    glVertex3f(30, 120, 0.0);        // vertex 22
    glVertex3f(45, 100, 0.0);        // vertex 23
    glVertex3f(75, 100, 0.0);       // vertex 24
    glVertex3f(145, 100, 0.0);       // vertex 25
    glVertex3f(145, 70, 0.0);        // vertex 26
    glVertex3f(75, 100, 0.0);       // vertex 27
    glVertex3f(75, 70, 0.0);        // vertex 28
    glEnd();

    // the left window cross
    glLineWidth(2.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(57, 99, 0.0);
    glVertex3f(57, 88, 0.0);
    glVertex3f(46, 88, 0.0);
    glVertex3f(46, 82, 0.0);
    glVertex3f(57, 82, 0.0);
    glVertex3f(57, 71, 0.0);
    glVertex3f(63, 71, 0.0);
    glVertex3f(63, 82, 0.0);
    glVertex3f(74, 82, 0.0);
    glVertex3f(74, 88, 0.0);
    glVertex3f(63, 88, 0.0);
    glVertex3f(63, 99, 0.0);
    glEnd();

    // the right window cross
    glLineWidth(2.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(157, 99, 0.0);
    glVertex3f(157, 88, 0.0);
    glVertex3f(146, 88, 0.0);
    glVertex3f(146, 82, 0.0);
    glVertex3f(157, 82, 0.0);
    glVertex3f(157, 71, 0.0);
    glVertex3f(163, 71, 0.0);
    glVertex3f(163, 82, 0.0);
    glVertex3f(174, 82, 0.0);
    glVertex3f(174, 88, 0.0);
    glVertex3f(163, 88, 0.0);
    glVertex3f(163, 99, 0.0);
    glEnd();

    // Draw roof
    glLineWidth(5.0); // Set thicker line width for the outline
    glColor3f(0.0, 0.0, 0.0); // Set color to black for the outline

    // Draw the object with black outline
    glBegin(GL_LINE_LOOP);
    glVertex3f(30, 120, 0.0);
    glVertex3f(110, 180, 0.0);
    glVertex3f(190, 120, 0.0);
    glEnd();

    glLineWidth(1.0);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(30, 120, 0.0);
    glVertex3f(110, 180, 0.0);
    glVertex3f(190, 120, 0.0);
    glEnd();

    // Draw door
    glLineWidth(3.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(100, 66, 0.0);
    glVertex3f(120, 66, 0.0);
    glVertex3f(100, 21, 0.0);
    glVertex3f(120, 21, 0.0);
    glEnd();

    glColor3f(0.5607, 0.7764, 0.2588);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(100, 66, 0.0);
    glVertex3f(120, 66, 0.0);
    glVertex3f(100, 21, 0.0);
    glVertex3f(120, 21, 0.0);
    glEnd();

    // Draw door handle
    double X = 104;
    double Y = 45;
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(X, Y);
    for (int i = 0; i < 100; i++)
        glVertex2f(X + 1 * cos(i * 10 * M_PI / 100), Y + 1 * sin(i * 10 * M_PI / 100));
    glEnd();
    glEnd();


    // execute the drawing
    glFlush();
}

// Initialization routine.
void setup(void) {
    //the clearing color of the opengl window (background)
    glClearColor(0.529, 0.808, 0.922, 1.0);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    // Prevent division by zero when the window is too small
    if (h == 0) h = 1;

    // Calculate the aspect ratio
    float aspect = static_cast<float>(w) / static_cast<float>(h);

    // Set the viewport to cover the entire window
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Adjust the orthographic projection to maintain the aspect ratio
    if (w <= h) {
        glOrtho(0.0, 300.0, 0.0 / aspect, 300.0 / aspect, -1.0, 1.0);
    } else {
        glOrtho(0.0 * aspect, 300.0 * aspect, 0.0, 300.0, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Keyboard input processing routine. x & y are location of the mouse
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv) {
    glutInit(&argc, argv);    // initializes the FreeGLUT library.

    // create context, set its version and set backward compatibility.
    // context is the interface between an instance of OpenGL and the rest of the system
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // wanting an OpenGL context to support a single-buffered frame, each pixel having red, green, blue and alpha values.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    // set the initial size of the OpenGL window and the location of its top left corner on the computer screen
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(0, 0);

    // creates the OpenGL context and its associated window with the specified string parameter as title.
    glutCreateWindow("scene1.cpp");

    // callback routines   when the OpenGL window is to be drawn, when it is resized,
    // and when keyboard input is received, respectively
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    // initializes GLEW (the OpenGL Extension Wrangler Library) which handles the loading of OpenGL extensions,
    // with the switch set so that extensions implemented even in pre-release drivers are exposed.
    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    // begins the event-processing loop, calling registered callback routines as needed
    glutMainLoop();

}