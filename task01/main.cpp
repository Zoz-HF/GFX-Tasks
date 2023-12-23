//importing the header files
#include <glew.h>
#include <freeglut.h>

// Drawing routine.
void drawScene()
{
    // clearing the buffer and setting the drawing color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0 , 0.0);

    // Draw a polygon with specified vertices counterclockwise and GL_LINE to draw character S.
    glBegin(GL_LINE_LOOP);
    glVertex3f(20.0, 90, 0.0);      // vertex 10
    glVertex3f(30.0, 94, 0.0);      // vertex 02
    glVertex3f(40.0, 98, 0.0);      // vertex 03
    glVertex3f(50.0, 100, 0.0);     // vertex 04
    glVertex3f(60.0, 98, 0.0);      // vertex 05
    glVertex3f(70.0, 94, 0.0);      // vertex 06
    glVertex3f(75.0, 90, 0.0);      // vertex 07
    glVertex3f(80.0, 85, 0.0);      // vertex 08
    glVertex3f(80.0, 80.0, 0.0);    // vertex 09
    glVertex3f(40.0, 80.0, 0.0);    // vertex 10
    glVertex3f(40.0, 60.0, 0.0);    // vertex 11
    glVertex3f(80.0, 50.0, 0.0);    // vertex 12
    glVertex3f(80.0, 0.0, 0.0);     // vertex 13
    glVertex3f(20.0, 0.0, 0.0);     // vertex 14
    glVertex3f(20.0, 20.0, 0.0);    // vertex 15
    glVertex3f(60.0, 20.0, 0.0);    // vertex 16
    glVertex3f(60.0, 40.0, 0.0);    // vertex 17
    glVertex3f(20.0, 50.0, 0.0);    // vertex 18
    glEnd();


// Draw character B.
    glColor3f(1,0 , 0);
    // outer B
    glBegin(GL_POLYGON );
    glVertex3f(105.0, 100.0, 0.0);   // vertex 01
    glVertex3f(105.0, 0.0, 0.0);     // vertex 02
    glVertex3f(140.0, 0.0, 0.0);     // vertex 03
    glVertex3f(155.0, 4.0, 0.0);     // vertex 04
    glVertex3f(160.0, 15.0, 0.0);    // vertex 05
    glVertex3f(165.0, 30.0, 0.0);    // vertex 06
    glVertex3f(160.0, 45.0, 0.0);    // vertex 07
    glVertex3f(155.0, 56.0, 0.0);    // vertex 08
    glVertex3f(140.0, 60.0, 0.0);    // vertex 09
    glVertex3f(150.0, 63.0, 0.0);    // vertex 10
    glVertex3f(155.0, 70.0, 0.0);    // vertex 11
    glVertex3f(160.0, 80.0, 0.0);    // vertex 12
    glVertex3f(155.0, 90.0, 0.0);    // vertex 13
    glVertex3f(150.0, 97.30, 0.0);   // vertex 14
    glVertex3f(140.0, 100.0, 0.0);   // vertex 15
    glEnd();

    glColor3f(1,1 , 1);
    // Lower Inner B
    glBegin(GL_POLYGON);
    glVertex3f(120.0, 10.0, 0.0);       // vertex 01
    glVertex3f(127.65, 11.5, 0.0);      // vertex 02
    glVertex3f(132.14, 15.858, 0.0);    // vertex 03
    glVertex3f(136.5, 22.4, 0.0);       // vertex 04
    glVertex3f(140.0, 30.0, 0.0);       // vertex 05
    glVertex3f(136.5, 37.65, 0.0);      // vertex 06
    glVertex3f(132.14, 44.14, 0.0);     // vertex 07
    glVertex3f(127.65, 48.77, 0.0);     // vertex 08
    glVertex3f(120.0, 50, 0.0);         // vertex 09
    glEnd();

    // Higher Inner B
    glBegin(GL_POLYGON);
    glVertex3f(120.0, 70.0, 0.0);      // vertex 01
    glVertex3f(123.82, 70.76, 0.0);    // vertex 02
    glVertex3f(125, 73, 0.0);          // vertex 03
    glVertex3f(127.3, 76.173, 0.0);    // vertex 04
    glVertex3f(130.0, 80, 0.0);        // vertex 05
    glVertex3f(127.3, 83.826, 0.0);    // vertex 06
    glVertex3f(125, 87.07, 0.0);       // vertex 07
    glVertex3f(123.82, 89.238, 0.0);   // vertex 08
    glVertex3f(120.0, 90, 0.0);        // vertex 09
    glEnd();

// Draw E
    glColor3f(0,1 , 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(200, 60.0,0.0);
    glVertex3f(200, 80.0,0.0);
    glVertex3f(250, 80.0,0.0);
    glVertex3f(250, 100.0,0.0);
    glVertex3f(180, 100,0.0);
    glVertex3f(180, 0,0.0);
    glVertex3f(250,0,0.0);
    glVertex3f(250, 20,0.0);
    glVertex3f(200, 20.0,0.0);
    glVertex3f(200, 40.0,0.0);
    glVertex3f(250, 40.0,0.0);
    glVertex3f(250, 60.0,0.0);
    glEnd();

// Draw a polygon with a more curved heart shape
    glColor3f(0,0 , 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(310.0, 0);
    glVertex2f(330.0, 20.0);
    glVertex2f(345.0, 40.0);
    glVertex2f(355.0, 60.0);
    glVertex2f(350.0, 80.0);
    glVertex2f(330.0, 100.0);
    glVertex2f(310.0, 80.0);
    glVertex2f(290.0, 100.0);
    glVertex2f(270.0, 80.0);
    glVertex2f(265.0, 60.0);
    glVertex2f(275.0, 40.0);
    glVertex2f(290.0, 20.0);
    glEnd();


    glVertex3f(-0.4*300, 0.8*300, 0.0*300);
    glVertex3f(-0.6*300, 0.8*300, 0.0*300);
    glVertex3f(-0.6*300, 0.6*300, 0.0*300);
    glVertex3f(-0.4*300, 0.6*300, 0.0*300);
    glVertex3f(-0.4*300, 0.4*300, 0.0*300);
    glVertex3f(-0.6*300, 0.4*300, 0.0*300);
    glVertex3f(-0.6*300, 0.2*300, 0.0*300);
    glVertex3f(-0.4*300, 0.2*300, 0.0*300);
    glVertex3f(-0.4*300, 0.0*300, 0.0*300);
    glVertex3f(-0.6*300, 0.0*300, 0.0*300);

    glVertex3f(-0.4*300, 0.4*300, 0.0*300);
    glVertex3f(-0.2*300, 0.4*300, 0.0*300);
    glVertex3f(-0.2*300, 0.6*300, 0.0*300);
    glVertex3f(-0.4*300, 0.6*300, 0.0*300);
    glEnd();


// execute the drawing
    glFlush();
}

// Initialization routine.
void setup()
{
    //the clearing color of the opengl window (background)
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    // drawing the entire window
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, 400, -50, 200, -10.0, 10.0);
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
    glutCreateWindow("square.cpp");

    // callback routines � when the OpenGL window is to be drawn, when it is resized,
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