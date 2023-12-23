#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>

#include "getBMP.h"

using namespace std;

int generate_random_number(int low, int up) {
    return (rand() % (up - low + 1)) + low;
}

// Globals.
static unsigned int texture[9]; // Array of texture indices.
static float d = 0.0; // Distance parameter in gluLookAt().
static int filter = 0; // Filter id.
static long font = (long) GLUT_BITMAP_8_BY_13; // Font selection.

float carWidth = 10.0;          // Width of the car body.
float carHeight = 6.0;          // Height of the car body.
float wheelRadius = 2.0;        // Radius of the wheels.
float wheelHeight = 1.0;        // Height of the wheels.

int x_block = generate_random_number(23, 40);              // Initial x_block position.
float y_block = 9.0;                                                // Initial y_block position.
int z_block = -generate_random_number(23, 40);            // Initial z_block position.
int vd_block = generate_random_number(18, 35);             // Distance between blocks vertically.
int v_block_noise[6];                                               // Noise for the vertical distance between blocks.
int h_block_noise[6];                                                           // Noise for the horizontal distance between blocks.
float angleX = 0.0;             // Initial rotation angle around the x-axis.
float angleY = 0.0;             // Initial rotation angle around the y-axis.
float zoom = 1.0;               // Initial zoom factor.
bool isBegin = true;            // Begin the game.

float CX(0), CY(-6.3), CZ(
        0);   //13.3(position of the ground center)-5/2(thickness of ground)-5/2(car height/2 <center of the wheels>)-2(wheels radios)

// Check collision with the target
float targetX(0), targetZ(-190), targetCubeSize(12.0);
float targetLengthX(32.0), targetLengthZ(12.0);
float carBodyCubeSize(10.0);

// Check collision with the obstacles
vector<float> blockXPositions;
vector<float> blockZPositions;

float carLengthX(4.0), carLengthY(10.0), carLengthZ(21.0);
float blockLengthX(20.0), blockLengthY(40.0), blockLengthZ(20.0);

float xTargetCollisionThreshold = (carLengthX + targetLengthX) / 2.0 + 2;
float zTargetCollisionThreshold = (carLengthZ + targetLengthZ) / 2.0 + 2;

float xBlockCollisionThreshold = (blockLengthX + carLengthX) / 2.0 + 3;
float zBlockCollisionThreshold = (blockLengthZ + carLengthZ) / 2.0;

string roadImg[3] = {"road1.bmp", "road2.bmp", "road3.bmp"};
string skyImg[2] = {"sky1.bmp", "sky2.bmp"};
string landImg[2] = {"land1.bmp", "land2.bmp"};
string blockImg[3] = {"block1.bmp", "block2.bmp", "block3.bmp"};

// Messages
string collisionMessage1 = "Game Over!\n";
string collisionMessage2 = "You Win!\n";

// Initialize image files
imageFile *image[9] = {
        getBMP(roadImg[0]),
        getBMP(skyImg[0]),
        getBMP(landImg[0]),
        getBMP(blockImg[0]),
        getBMP("car.bmp"),
        getBMP("car wheel.bmp"),
        getBMP("car2.bmp"),
        getBMP("target.bmp"),
        getBMP("start.bmp"),
};;
// space bar detection as when the user clicks on space bar 2 times at the beginning, the game starts
int spaceBarCounter = 0;

//The timer function callback declaration
void displayRemainingTime(int value);

void drawScene(void);

bool isWaiting = false;




// Load the images.

void loadTextures() {
    // Local storage for bmp image data.

    // Bind grass image to texture[0] with specified mag and min filters.
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Bind grass image to texture[1] with specified mag and min filters.
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->width, image[2]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Bind sky image to texture[2]
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->width, image[1]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Bind grass image to texture[1] with specified mag and min filters.
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->width, image[3]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->width, image[4]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[5]->width, image[5]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[5]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[6]->width, image[6]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[6]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[7]->width, image[7]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[7]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[8]->width, image[8]->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[8]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, texture[9]);
}


void changeTexture(int t) {
    switch (t) {

        case 1:
        case 2:
            image[1] = getBMP(skyImg[t - 1]);
            break;

        case 3:
        case 4:
        case 5:
            image[0] = getBMP(roadImg[t - 3]);
            break;

        case 6:
        case 7:
            image[2] = getBMP(landImg[t - 6]);
            break;

        case 8:
        case 9:
        case 10:
            image[3] = getBMP(blockImg[t - 8]);
            break;

        default:
            break;
    }

    loadTextures();
    drawScene();
}

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string) {
    char *c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

bool checkCollisionTarget() {
    // 18 and 18.5 was manually calculated based on the half of the Z length of the car and the target after all transformations applied
    bool collisionX = (fabs(CX - targetX) <= xTargetCollisionThreshold);
    bool collisionZ = (fabs(CZ - targetZ) <= zTargetCollisionThreshold);
    return collisionX && collisionZ;
}

bool collisionBlocks = false;

double SKY_Z;

bool checkCollisionWithBlock(float blockX, float blockZ) {
    // Adjust collision logic based on your requirements
    bool collisionX = (fabs(CX - blockX) <= xBlockCollisionThreshold);
    bool collisionZ = (fabs(CZ - blockZ) <= zBlockCollisionThreshold);

    collisionBlocks = collisionX && collisionZ;
    return collisionBlocks;
}

// Initialization routine.
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);
    // Create texture ids.
    glGenTextures(9, texture);

    // Load external textures.
    loadTextures();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);

}

void create_block(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0, 2.0, 1.0);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glutSolidCube(20.0);
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);

    glPopMatrix();

    // Add block positions to vectors
    blockXPositions.push_back(x);
    blockZPositions.push_back(z);
}

void change_block_noise() {
    for (int i = 0; i < 6; i++) {
        v_block_noise[i] = generate_random_number(0, 10);
        h_block_noise[i] = generate_random_number(0, 10);
    }
}

// create menu function
void createMenu() {
    int sub_menu_sky, sub_menu_road, sub_menu_land, sub_menu_obstacle;

    sub_menu_sky = glutCreateMenu(changeTexture);
    glutAddMenuEntry("Day", 1);
    glutAddMenuEntry("Night", 2);

    sub_menu_road = glutCreateMenu(changeTexture);
    glutAddMenuEntry("road1", 3);
    glutAddMenuEntry("road2", 4);
    glutAddMenuEntry("road3", 5);


    sub_menu_land = glutCreateMenu(changeTexture);
    glutAddMenuEntry("Asphalt", 6);
    glutAddMenuEntry("Grass", 7);

    sub_menu_obstacle = glutCreateMenu(changeTexture);
    glutAddMenuEntry("Building", 8);
    glutAddMenuEntry("Wood", 9);
    glutAddMenuEntry("Block", 10);


    int menu = glutCreateMenu(changeTexture);
    glutAddSubMenu("Sky", sub_menu_sky);
    glutAddSubMenu("Road", sub_menu_road);
    glutAddSubMenu("Land", sub_menu_land);
    glutAddSubMenu("Obstacle", sub_menu_obstacle);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void displayRemainingTime(int value) {
    if (value > 0) {
        isWaiting = true;  // Set the waiting state.
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0); // Set color to white for collision messages.
        if (collisionBlocks) {
            glRasterPos3f(CX, CY + 8, CZ + 12);
        } else if (checkCollisionTarget()) {
            glRasterPos3f(6.0, 3.0, -180.0); // Adjust position for message display.
        }
        string message = "Wait " + to_string(value) + " seconds and the game will restart";
        for (char c: message) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        glPopMatrix();
        glutTimerFunc(1000, displayRemainingTime, value - 1);
    } else {
        // Restart the game
        CX = 0;
        CY = -6.3;
        CZ = 0.0;
        isWaiting = false;  // Reset the waiting state.
        x_block = generate_random_number(23, 40);           // Initial x_block position.
        z_block = -generate_random_number(23, 40);            // Initial z_block position.
        vd_block = generate_random_number(18, 35);

        // Clear the vectors when restarting the game
        blockXPositions.clear();
        blockZPositions.clear();
        collisionBlocks = false;
        glutPostRedisplay();  // Trigger redraw to update the display.
    }

    glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double) w / (double) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

// Keyboard input processing routine.
void specialkey(int key, int x, int y) {
    if (!isWaiting) {
        if (spaceBarCounter == 2 && (!(checkCollisionTarget() || collisionBlocks))) {
            switch (key) {
                case GLUT_KEY_UP:       //when the up key is pressed CZ++;
                    if (CZ > -170)
                        CZ -= 3;
                    else
                        CZ = -173;
                    break;
                case GLUT_KEY_DOWN:     //when the down arrow key is pressed CZ--;
                    if (CZ < 4)
                        CZ += 3;
                    else
                        CZ = 7;
                    break;
                case GLUT_KEY_LEFT:     //when the left arrow key is pressed CX--;
                    if (CX > -52)
                        CX -= 3;
                    else
                        CX = -55;
                    break;
                case GLUT_KEY_RIGHT:    //when the right arrow key is pressed CX++;
                    if (CX < 52)
                        CX += 3;
                    else
                        CX = 55;
                    break;
            }
        }
        glutPostRedisplay();
    }
}

void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':  // Rotate right around y-axis.
            angleY += 5.0;
            break;
        case 'l':  // Rotate left around y-axis.
            angleY -= 5.0;
            break;
        case 'u':  // Rotate up around x-axis.
            angleX += 5.0;
            break;
        case 'd':  // Rotate down around x-axis.
            angleX -= 5.0;
            break;
        case 'i':  // Zoom in.
            zoom -= 0.1;
            // if (zoom < 0.1) zoom = 0.1; // remove this line
            break;
        case 'o':  // Zoom out.
            zoom += 0.1;
            break;
        case 'x':  // Zoom out.
            angleX = 0.0;
            angleY = 0.0;
            zoom = 1.0;
            break;
        case ' ':
            if (spaceBarCounter <= 1)spaceBarCounter += 1;
            cout << "Space clicked" << spaceBarCounter << endl;
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }

    glutPostRedisplay();  // Request a redraw after updating the scene parameters.
}

// Drawing routine.
void drawScene(void) {

    if (isBegin) {
        change_block_noise();
        isBegin = false;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Update the camera position to follow the car.
    if (spaceBarCounter == 2) {
        gluLookAt(
                CX, CY + 10.0, CZ + 20.0 * zoom,  // eye position
                CX, CY, CZ,                 // center position (look at the car)
                0.0, 1.0, 0.0                       // up vector
        );
        glRotatef(angleX, 1.0, 0.0, 0.0);
        glRotatef(angleY, 0.0, 1.0, 0.0);
    } else {
        gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 55.0, 0.0, 1.0, 0.0);
        float x = 20.0;
        float y = 10.0;
        float z = 70.0;

        glPushMatrix();
        // A baby blue square for the first couple of messages
        glBegin(GL_POLYGON);
        glColor4f(0.678, 0.847, 0.902, 1.0);
        glVertex3f(-x, -y, z);
        glVertex3f(-x, y, z);
        glVertex3f(x, y, z);
        glVertex3f(x, -y, z);
        glEnd();
        glPopMatrix();

        glColor3f(0.0, 0.0, 0.0); // Set color to black for the first couple of messages.
        // Display messages.
        if (spaceBarCounter == 0) {
            glPushMatrix();
            glRasterPos3f(7.0, 1.0, 60.0); // Adjust position for message display.
            for (char c: "This is a game about a car moving through obstacles") {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
            glRasterPos3f(7.0, 0.0, 60.0); // Adjust position for message display.
            for (char c: "press space bar to continue...") {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }

            glPopMatrix();
        } else if (spaceBarCounter == 1) {
            glPushMatrix();
            glRasterPos3f(7.0, 1.0, 60.0); // Adjust position for message display.
            for (char c: "The obstacles are randomly distributed...") {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
            glRasterPos3f(7.0, 0.0, 60.0); // Adjust position for message display.
            for (char c: "To play this game use up,down,left and right arrow keys") {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
            glRasterPos3f(7.0, -1.0, 60.0); // Adjust position for message display.
            for (char c: "press space bar to continue") {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }

            glPopMatrix();
        }
    }

    glTranslatef(0.0, 0.0, -20.0 * zoom);  // Move the entire car back along the z_block-axis with zoom factor.
    glRotatef(angleX, 1.0, 0.0, 0.0);  // Rotate around the x_block-axis.
    glRotatef(angleY, 0.0, 1.0, 0.0);  // Rotate around the y_block-axis.

    glPushMatrix();
    glTranslatef(CX, CY, CZ);
    glRotatef(-90, 0.0, 1.0, 0.0);

    // Draw the wheels
    // ===============
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, texture[5]);

    // Front left wheel
    // ================
    glPushMatrix();
    glTranslatef(-carWidth / 2.0, -carHeight / 2.0, -carWidth / 2.0);
    glutSolidCylinder(wheelRadius, wheelHeight, 30, 20);  // Increased slices and stacks.
    glPopMatrix();

    // Front right wheel
    // =================
    glPushMatrix();
    glTranslatef(+carWidth / 2.0, -carHeight / 2.0, -carWidth / 2.0);
    glutSolidCylinder(wheelRadius, wheelHeight, 30, 20);  // Increased slices and stacks.
    glPopMatrix();

    // Rear left wheel
    // ===============
    glPushMatrix();
    glTranslatef(-carWidth / 2.0, -carHeight / 2.0, carWidth / 2.0 - wheelHeight);
    glutSolidCylinder(wheelRadius, wheelHeight, 30, 20);  // Increased slices and stacks.
    glPopMatrix();

    // Rear right wheel
    // ================
    glPushMatrix();
    glTranslatef(+carWidth / 2.0, -carHeight / 2.0, +carWidth / 2.0 - wheelHeight);
    glutSolidCylinder(wheelRadius, wheelHeight, 30, 20);  // Increased slices and stacks.
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);

    // Draw shaft from front left wheel to rear left wheel
    // ===================================================
    glColor3f(0.0, 0.0, 0.0);  // Black color for the shaft.
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex3f(-carWidth / 2.0, -carHeight / 2.0, -carWidth / 2.0);
    glVertex3f(-carWidth / 2.0, -carHeight / 2.0, carWidth / 2.0 - wheelHeight);
    glEnd();

    // Draw shaft from front right wheel to rear right wheel
    // =====================================================
    glBegin(GL_LINES);
    glVertex3f(carWidth / 2.0, -carHeight / 2.0, -carWidth / 2.0);
    glVertex3f(carWidth / 2.0, -carHeight / 2.0, carWidth / 2.0 - wheelHeight);
    glEnd();

    glLineWidth(1.0);  // Reset line width.
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    // Draw the car body
    // =================
    glColor3f(0.0, 0.0, 1.0);  // Blue color for the lower cuboid.
    glScalef(0.7, 0.4, 1);
    glPushMatrix();
    glTranslatef(0, -carHeight / 4.0 + wheelRadius * 2.0, 0);  // Adjust the translation.
    glScalef(3, 1, 1);  // Adjust the scaling for desired proportions.
    glutSolidCube(carWidth);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);

    // Draw the upper cuboid
    // =====================
    glColor3f(0.0, 0.0, 0.0);  // Black color for the upper cuboid.
    glPushMatrix();
    glTranslatef(+3, +carHeight + wheelRadius * 2.0 + carHeight * 0.3, 0);
    glScalef(1.5, 0.6, 0.8);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glutSolidCube(carWidth);
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
    glPopMatrix();

    // Draw the road
    // ===============
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-62.5, -10.8, 50.0);
    glTexCoord2f(8.0, 0.0);
    glVertex3f(62.5, -10.8, 50.0);
    glTexCoord2f(8.0, 8.0);
    glVertex3f(62.5, -10.8, -250.0);
    glTexCoord2f(0.0, 8.0);
    glVertex3f(-62.5, -10.8, -250.0);
    glEnd();
// Draw the start line
    // ===============
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-62.5, -10.7, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(62.5, -10.7, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(62.5, -10.7, -10.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-62.5, -10.7, -10.0);
    glEnd();
// Draw the ground
    // ===============
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-200, -10.9, 50.0);
    glTexCoord2f(8.0, 0.0);
    glVertex3f(200, -10.9, 50.0);
    glTexCoord2f(8.0, 8.0);
    glVertex3f(200, -10.9, -250.0);
    glTexCoord2f(0.0, 8.0);
    glVertex3f(-200, -10.9, -250.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_POLYGON);
    if (CZ - 60.0 < -250) {
        SKY_Z = -250;
    } else {
        SKY_Z = CZ - 60.0;
    }
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-200, -10.8, SKY_Z);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(200, -10.8, SKY_Z);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(200, 200.0, SKY_Z);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-200, 200.0, SKY_Z);


    glEnd();


    // Draw the Blocks
    // ===============
    for (int i = 0; i < 6; i++) {
        create_block(x_block * pow(-1, i) - h_block_noise[i] * pow(-1, i),
                     y_block,
                     z_block - i * vd_block + v_block_noise[i] * pow(-1, i));
    }

    // Check collisions with blocks
    for (size_t i = 0; i < blockXPositions.size(); i++) {
        // the following line is to ensure that the program stops checking/iterating over the vectors after it detected a collision
        if (checkCollisionWithBlock(blockXPositions[i], blockZPositions[i])) {
            glColor3f(0.0, 0.0, 0.0); // Set color to black for collision messages.
            // Display messages.
            glRasterPos3f(CX, CY + 10, CZ + 12); // Adjust position for message display.
            for (char c: collisionMessage1) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
            if (!isWaiting) displayRemainingTime(4);
            break;
        }
    }

    // Target
    // ======
    glPushMatrix();
    glTranslatef(0, 5, -190);
    glScalef(4.0, 4, 1.5);
    glutSolidCube(8.0);
    glPopMatrix();

    if (checkCollisionTarget()) {
        std::cout << "checkCollisionTarget            ";
        glColor3f(0.0, 0.0, 0.0); // Set color to red for collision messages.
        // Display messages.
        glRasterPos3f(8.0, 5.0, -180.0); // Adjust position for message display.
        for (char c: collisionMessage2) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        if (!isWaiting) displayRemainingTime(4);
    }


    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-16, -11, -183.9);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(16, -11, -183.9);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(16, 21, -183.9);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-16, 21, -183.9);
    glEnd();


    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Car Simulation");
    glutReshapeFunc(resize);

    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialkey);
    glutDisplayFunc(drawScene);
    createMenu();


    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();

    return 0;
}
