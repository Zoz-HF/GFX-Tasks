#include "cmath"
#include <glew.h>
#include <freeglut.h>

// Drawing routine.
void drawScene(void)
{
    // clearing the buffer and setting the drawing color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0 , 0.0);

    glColor3f(0,10 , 0);
    glBegin(GL_LINE_STRIP);
    for(int i=-5;i<6;i++)
        glVertex2f(75+50*cos(i*10*M_PI/180), 120+50*sin(i*10*M_PI/180));
    for(int i=14;i<24;i++)
        glVertex2f(139.28+50*cos(i*10*M_PI/180), 120+50*sin(i*10*M_PI/180));

    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(75+50*cos(5*10*M_PI/180), 120+50*sin(5*10*M_PI/180));
    for(int i=2;i>-3;i--)
        glVertex2f(25+84.376*cos(i*0.07), 139+84.376*sin(i*0.07));
    glVertex2f(75+50*cos(-5*10*M_PI/180), 120+25*sin(-5*10*M_PI/180)+25*sin(5*10*M_PI/180));
    for(int i=43;i<48;i++)
        glVertex2f(189.28+84.376*cos(i*0.07), 100+84.376*sin(i*0.07));
    glVertex2f(75+50*cos(-5*10*M_PI/180), 120+50*sin(-5*10*M_PI/180));
    for(int i=38;i<45;i++)
        glVertex2f(100+50*cos(-5*10*M_PI/180)+25*cos(i*5*M_PI/180), 120+50*sin(-5*10*M_PI/180)+25*sin(i*5*M_PI/180));
//glVertex2f(75+50*cos(-5*10*M_PI/180)+20, 120+50*sin(-5*10*M_PI/180)-20);


    glEnd();
    glBegin(GL_LINES);
    glVertex2f(25+84.376*cos(1*0.07), 139+84.376*sin(1*0.07));
    glVertex2f(75+50*cos(7.5*5*M_PI/180), 120+50*sin(7.5*5*M_PI/180));
    glVertex2f(25+84.376*cos(-2*0.07), 139+84.376*sin(-2*0.07));
    glVertex2f(75+50*cos(5*5*M_PI/180), 120+50*sin(5*5*M_PI/180));
    glVertex2f(189.28+84.376*cos(43*0.07), 100+84.376*sin(43*0.07));
    glVertex2f(75+50*cos(1*10*M_PI/180), 120+50*sin(1*10*M_PI/180));
    glVertex2f(189.28+84.376*cos(46*0.07), 100+84.376*sin(46*0.07));
    glVertex2f(75+50*cos(-1*10*M_PI/180), 120+50*sin(-1*10*M_PI/180));

    glVertex2f(25+84.376*cos(1*0.07), 139+84.376*sin(1*0.07));
    glVertex2f(139.28+50*cos(140.5*M_PI/180), 120+50*sin(140.5*M_PI/180));
    glVertex2f(25+84.376*cos(-2*0.07), 139+84.376*sin(-2*0.07));
    glVertex2f(139.28+50*cos(155*M_PI/180), 120+50*sin(155*M_PI/180));
    glVertex2f(189.28+84.376*cos(43*0.07), 100+84.376*sin(43*0.07));
    glVertex2f(139.28+50*cos(170*M_PI/180), 120+50*sin(170*M_PI/180));
    glVertex2f(189.28+84.376*cos(46*0.07), 100+84.376*sin(46*0.07));
    glVertex2f(139.28+50*cos(190*M_PI/180), 120+50*sin(190*M_PI/180));

//glVertex2f(75+50*cos(-5*10*M_PI/180)+20, 120+50*sin(-5*10*M_PI/180)-20);


    glEnd();
//    glColor3f(10,10 , 0);
//    glBegin(GL_LINES);
//    for(int i=0;i<38;i++) {
//        glVertex2f(100 + 50 * cos(i * 10 * M_PI / 180), 100 + 50 * sin(i * 10 * M_PI / 180));
//        glVertex2f(100 + 70 * cos(i * 10 * M_PI / 180), 100 + 70 * sin(i * 10 * M_PI / 180));
//    }
//    glEnd();



// execute the drawing
    glFlush();
}

// Initialization routine.
void setup(void)
{
    //the clearing color of the opengl window (background)
    glClearColor(0, 0, 0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    // drawing the entire window
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 200, 0, 200, -10.0, 10.0);
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
            exit(0);
            break;
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);

    // creates the OpenGL context and its associated window with the specified string parameter as title.
    glutCreateWindow("square.cpp");

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