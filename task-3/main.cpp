//importing the header files
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Globals
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // for the whole scene
// animation flags
bool animateAllFlag = false;
bool flyingBallFlag = false;
bool rotateArm = false;

// stick man constants
static float armLength = 0.7 * std::sqrt(37);
//stick man rotation
float rotationAngle = 90; // Global variable to track the left arm rotation angle
static float rotationIncrement = 0.05; // Rotation speed (adjust as needed)
static float minRotationAngle = 90.0; // Minimum arm rotation angle (degrees)
static float maxRotationAngle = 94; // Maximum arm rotation angle (degrees)
static float throwRotationAngle = maxRotationAngle - 0.5; //trowball arm rotation angle (degrees)
// ball global coordinates (to monitor anywhere)
float ballCoordinates[3] = {0.0, 0.0, 0.0}; // Initialized to (0, 0, 0)
float thrownCoordinates[3];
// projectile constants
float t = 0.0; // Time parameter.
float b = 0.0; // Vertical component of initial velocity.
static float g = 9.8;  // Gravitational accelaration.
float vo = 2.05, theta = 45;

// bouncing
bool bounceFlag = false;


// Drawing routine.
void drawScene() {

    // clearing the buffer and setting the drawing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.0, 0.0, 0.0); // Sets the current drawing color to black

    glLoadIdentity();
// translate the whole scene
    glTranslatef(0.0, 0.0, -30.0);

    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

//stick man moving arm, befor ball to stick ball to the man's left hand
    float armPlaceX = 0.0;
    float armPlaceY = 10.0;


// Ball //////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    glPushMatrix();

    glColor3f(1.0, 0.0, 0.0);
    if (!flyingBallFlag) { //state one
        //this is 20 bcs I translated the total man in x by 20 but didn't have time to focus on other things rather than making it work
        ballCoordinates[0] = 20.0 - armLength * cosf(rotationAngle);
        ballCoordinates[1] = 10.0 - armLength * sinf(rotationAngle);
        ballCoordinates[2] = -7.0;


        glTranslatef(ballCoordinates[0], ballCoordinates[1], ballCoordinates[2]);
        std::copy(std::begin(ballCoordinates), std::end(ballCoordinates), std::begin(thrownCoordinates));

    }
        // at angle of left arm is 93.4807 and  0
//the last Ball Coordinates of state one is: (16.905, 12.9242, -7)
    else if (flyingBallFlag) {
        // Apply equations of motion to transform sphere.
        glTranslatef(ballCoordinates[0], ballCoordinates[1], ballCoordinates[2]);

    }
    glutSolidSphere(1, 100, 100);
    glPopMatrix();
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Wall
    glColor3f(0.4, 0.4, 0.4);
    glPushMatrix();
    glTranslatef(-20, 15.0, -5.0);
    glScalef(1, 9.5, 5);
    glutSolidCube(3);
    glPopMatrix();

    // Ground
    glColor3f(0.9, 0.4, 0.4);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5);
    glScalef(15, 0.5, 7);
    glutSolidCube(5);
    glPopMatrix();

//matrix for the whole man
    glPushMatrix();
    glTranslatef(20.0, 1.0, 0.0);
    //head
    glPushMatrix();
    glTranslatef(0.0, 15.0, -7);
    glColor3f(0.0, 0.0, 0.0);

    // Draw the stickman parts in side view.

    // Head (a circle)
    int numSegments = 100;
    GLfloat radius = 3.0;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= numSegments; i++) {
        float local_theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(local_theta);
        float y = radius * sinf(local_theta);
        glVertex2f(0.0 + x, 0.0 + y);
    }
    glEnd();
    glPopMatrix();

//torse, hight for trose and legs is 15, the torso took 10
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glLineWidth(5.0);

    // Body (a vertical line)
    glBegin(GL_LINES);
    glVertex3f(0.0, 15.0, -7.0);
    glVertex3f(0.0, 5.0, -7.0);
    glEnd();
    glPopMatrix();

//legs
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);

// Legs (two vertical lines)
    glBegin(GL_LINES);
    glVertex3f(0.0, 5.0, -7.0);
    glVertex3f(5.0, 0.0, -7.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, 5.0, -7.0);
    glVertex3f(-5.0, 0.0, -7.0);
    glEnd();
    glPopMatrix();

//hands
    glPushMatrix();

    // Left Arm (rotating)
    float armPlaceZ = -7.0;

    float armX = 0.0 - armLength * cosf(rotationAngle);
    float armY = 10.0 - armLength * sinf(rotationAngle);

    glBegin(GL_LINES);
    glVertex3f(armPlaceX, armPlaceY, armPlaceZ);
    glVertex3f(armX, armY, armPlaceZ);
    glEnd();

    // Right Arm (fixed)
    glBegin(GL_LINES);
    glVertex3f(armPlaceX, armPlaceY, armPlaceZ);
    glVertex3f(armPlaceX + 5.0, armPlaceY - 2.5, armPlaceZ);
    glEnd();
    glPopMatrix();

//matrix for the whole man
    glPopMatrix();


    glutSwapBuffers();

    glFlush();
}

// Initialization routine.
void setup() {
    //the clearing color of the opengl window (background)
    glClearColor(1, 1, 1, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    // drawing the entire window
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-30.0, 30.0, -5.0, 40.0, -30.0, 100.0);
//    glFrustum(-15.0, 10.0, -1.0, 10.0, 10.0, 100.0);
//    glFrustum(-40, 40, -15, 15, -1, -6);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

// Timer function to update the rotation angle.
void animateAll(int value) {
    if (animateAllFlag) {
        //std::cout<<"  rotationAngle " <<rotationAngle<< " rotationIncrement   "<<rotationIncrement<<" flyingBallFlag  "<< flyingBallFlag<<endl;
        //cout << "  Ball Coordinates: (" << ballCoordinates[0] << ", " << ballCoordinates[1] << ", " << ballCoordinates[2] << ")" << endl;

        if (!flyingBallFlag) //state one
        {
            rotationIncrement = 0.05;
            rotateArm = true;
            //flyingBallFlag = true;
            rotationAngle += rotationIncrement;
            if (rotationAngle > throwRotationAngle && !flyingBallFlag) flyingBallFlag = true;
        }


        if (flyingBallFlag) {
            //  cout<<" flying ball";
            //state 2, conditions to rotate arm back
            if (rotateArm) {
                rotationAngle += rotationIncrement;

                if (rotationAngle > maxRotationAngle) {
                    rotationIncrement = -rotationIncrement; // Reverse rotation direction when reaching limits
                    rotationIncrement *= 3;
                }

                if (rotationAngle < minRotationAngle) rotateArm = false;
            }


            // state 3, from thrown till wall, wall face at (-20+1.5, max 30, -5 (will see))

            if (ballCoordinates[0] <= (thrownCoordinates[0]) || !bounceFlag) {
                //cout<<"  no bounce,vo "<<vo;

                t += 0.005;
                ballCoordinates[0] -= vo * cos(theta) * t;
                ballCoordinates[1] += vo * sin(theta) * t - g * t * t * 0.5;
                ballCoordinates[2] += t / 40;
                if (ballCoordinates[0] <= -18 && !bounceFlag) { bounceFlag = true; }

            }

            if (bounceFlag) {  //cout<<"  bbbbounce,vo "<<vo;
                // if vertical component
                if (vo * sin(theta) > 0) {
                    t += 0.005;
                    if (ballCoordinates[1] < 3) // condition for reaching ground
                    {
                        b = b + vo * cos(theta) * t;
                        vo = 0.3 * vo;
                        t = 0;
                    }
                } else // case of no vertical component
                {
                    vo = 0;
                    b = b + vo * sin(theta) * t;
                    t = 0;
                    if (b < 1) {
                        b += 0.001;
                    }
                }
                //cout<<"bounce"<<endl;
                ballCoordinates[0] += vo * cos(theta) * t + b;
                ballCoordinates[1] += 0.1 + vo * sin(theta) * t - g * t * t * 0.5;
            }//if bounce flag





        }// if flying flag
    }//if animate all


// end of if(animateAllFlag)
    glutPostRedisplay();

    glutTimerFunc(10, animateAll, 0);
}//animate all


// Keyboard input processing routine. x & y are location of the mouse
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);

        case 'x':
            Xangle += 5.0;
            if (Xangle > 360.0) Xangle -= 360.0;
            glutPostRedisplay();
            break;

        case 'X':
            Xangle -= 5.0;
            if (Xangle < 0.0) Xangle += 360.0;
            glutPostRedisplay();
            break;

        case 'y':
            Yangle += 5.0;
            if (Yangle > 360.0) Yangle -= 360.0;
            glutPostRedisplay();
            break;

        case 'Y':
            Yangle -= 5.0;
            if (Yangle < 0.0) Yangle += 360.0;
            glutPostRedisplay();
            break;

        case 'z':
            Zangle += 5.0;
            if (Zangle > 360.0) Zangle -= 360.0;
            glutPostRedisplay();
            break;

        case 'Z':
            Zangle -= 5.0;
            if (Zangle < 0.0) Zangle += 360.0;
            glutPostRedisplay();
            break;

        case 'r':

            Xangle = 0;
            Yangle = 0;
            Zangle = 0;
            // animation flags
            animateAllFlag = false;
            flyingBallFlag = false;
            rotateArm = false;
            // bouncing
            bounceFlag = false;
            rotationAngle = 90;
            t = 0.0;
            vo = 2.05;

            glutPostRedisplay();
            break;

        case 32: // ASCII of space bar
            animateAllFlag = !animateAllFlag; // Toggle arm rotation with space bar
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
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);

    // creates the OpenGL context and its associated window with the specified string parameter as title.
    glutCreateWindow("training.cpp");

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
    glutTimerFunc(10, animateAll, 0); // Start the timer for arm rotation.
    cout << "press x,X,y,Y,z,Z to rotate around the axis" << endl << "press space to play/stop" << endl
         << "press r then space to reset";

    // begins the event-processing loop, calling registered callback routines as needed
    glutMainLoop();

}
