//importing the header files
#include <glew.h>
#include <freeglut.h>
#include <cmath>
#include <iostream>

using namespace std;


// Drawing routine.
void drawScene()
{
    // clearing the buffer and setting the drawing color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0 , 0.0);

    // Draw shape 1 to be the body of the transformer
    glBegin( GL_TRIANGLE_STRIP);
    glVertex3f(20, 120, 0.0);        // vertex 01
    glVertex3f(40, 100, 0.0);        // vertex 02
    glVertex3f(20, 20, 0.0);         // vertex 03
    glVertex3f(40, 40, 0.0);         // vertex 04
    glVertex3f(110, 20, 0.0);        // vertex 05
    glVertex3f(100, 40 ,0);          // vertex 06
    glVertex3f(120, 40, 0.0);        // vertex 07
    glVertex3f(110, 20, 0.0);        // vertex 08
    glVertex3f(200, 20, 0.0);        // vertex 09
    glVertex3f(120, 40, 0.0);        // vertex 10
    glVertex3f(180, 40, 0.0);        // vertex 11
    glVertex3f(200, 20, 0.0);        // vertex 12
    glVertex3f(200, 120, 0.0);       // vertex 13
    glVertex3f(180, 40, 0.0);        // vertex 14
    glVertex3f(180, 100, 0.0);       // vertex 15
    glVertex3f(200, 120.0, 0.0);     // vertex 16
    glVertex3f(110, 120, 0.0);       // vertex 17
    glVertex3f(180, 100, 0.0);       // vertex 18
    glVertex3f(120, 100, 0.0);       // vertex 19
    glVertex3f(110, 120, 0.0);       // vertex 20
    glVertex3f(100, 100, 0.0);       // vertex 21
    glVertex3f(20, 120, 0.0);        // vertex 22
    glVertex3f(40, 100, 0.0);        // vertex 23
    glVertex3f(100, 100, 0.0);       // vertex 24
    glVertex3f(120, 100, 0.0);       // vertex 25
    glVertex3f(120, 40, 0.0);        // vertex 26
    glVertex3f(100, 100, 0.0);       // vertex 27
    glVertex3f(100, 40, 0.0);        // vertex 28
    glEnd();

//    Draw coils on the body of the transformer using 3d shape of shape 3
    int number_of_vertices = 200;
    float X = 190;
    float Y = 98;
    float Z = -3;
    float R = 13;
    glColor3f(1.0,0.0 , 0.0);

    while(Y>43){
        float t = 0;
        glBegin( GL_LINE_STRIP);
        for(int i=0;i<number_of_vertices;i++){
            glVertex3f(X + R * cos(t), Y, Z + R * sin(t));
            t += 2 * M_PI / number_of_vertices;
            Y -= .04;
        }
    }
    glEnd();


    X = 110;
    Y = 98;
    Z = -3;
    R = 13;
    glColor3f(0,1 , 0);

    while(Y>43){
        float t = 0;
        glBegin( GL_LINE_STRIP);
        for(int i=0;i<number_of_vertices;i++){
            glVertex3f(X + R * cos(t), Y, Z + R * sin(t));
            t += 2 * M_PI / number_of_vertices;
            Y -= .04;
        }
    }
    glEnd();


    X = 30;
    Y = 98;
    Z = -3;
    R = 13;
    glColor3f(0,0 , 1);

    while(Y>43){
        float t = 0;
        glBegin( GL_LINE_STRIP);
        for(int i=0;i<number_of_vertices;i++){
            glVertex3f(X + R * cos(t), Y, Z + R * sin(t));
            t += 2 * M_PI / number_of_vertices;
            Y -= .04;
        }
    }
    glEnd();


// execute the drawing
    glFlush();
}

// Initialization routine.
void setup()
{
    //the clearing color of the opengl window (background)
    glClearColor(0.2, 0.2, 0.2, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    // drawing the entire window
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, 220, -10, 150, -30.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine. x & y are location of the mouse
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        // ascii of escape key
        case 27:
            cout<<125;
            exit(0);

        case 28:
            exit(0);

        default:
            break;
    }
}

// Main routine.
int main(int argc, char** argv)
{

    glutInit(&argc, argv);	// initializes the FreeGLUT library.

    // create context, set its version and set backward compatibility.
    // context is the interface between an instance of OpenGL and the rest of the system
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // wanting an OpenGL context to support a single-buffered frame, each pixel having red, green, blue and alpha values.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    // set the initial size of the OpenGL window and the location of its top left corner on the computer screen
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(200, 200);

    // creates the OpenGL context and its associated window with the specified string parameter as title.
    glutCreateWindow("task2.cpp");

    // callback routines � when the OpenGL window is to be drawn, when it is resized,
    // and when keyboard input is received, respectively
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    // initializes GLEW (the OpenGL Extension Wrangler Library) which handles the loading of OpenGL extensions,
    // with the switch set so that extensions implemented even in pre-release drivers are exposed.
    glewExperimental = GL_TRUE;
    glewInit();
    // performing the setup
    setup();

    // begins the event-processing loop, calling registered callback routines as needed
    glutMainLoop();

}