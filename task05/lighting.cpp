#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>

using namespace std;

int generate_random_number(int low, int up) {
    return  (rand() % (up - low + 1)) + low;
}

// Globals.
float carWidth = 10.0;          // Width of the car body.
float carHeight = 6.0;          // Height of the car body.
float wheelRadius = 2.0;        // Radius of the wheels.
float wheelHeight = 1.0;        // Height of the wheels.

float x_block = generate_random_number(20,40);              // Initial x_block position.
float y_block = 9.0;                                                // Initial y_block position.
float z_block = -generate_random_number(15,25);            // Initial z_block position.
float vd_block = generate_random_number(15,30);             // Distance between blocks vertically.
int v_block_noise[6];                                               // Noise for the vertical distance between blocks.
int h_block_noise[6];                                                           // Noise for the horizontal distance between blocks.
float angleX = 0.0;             // Initial rotation angle around the x-axis.
float angleY = 0.0;             // Initial rotation angle around the y-axis.
float zoom = 1.0;               // Initial zoom factor.
bool isBegin = true;            // Begin the game.

float CX(0), CY(-6.3), CZ(0);   //13.3(position of the ground center)-5/2(thickness of ground)-5/2(car height/2 <center of the wheels>)-2(wheels radios)

// Check collision with the target
float targetX(0), targetY(5), targetZ(-190), targetCubeSize(12.0);
float targetLengthX(32.0), targetLengthY(32.0), targetLengthZ(12.0);
float carBodyCubeSize(10.0);

// Check collision with the obstacles
std::vector<float> blockXPositions;
std::vector<float> blockZPositions;

float carLengthX(4.0), carLengthY(10.0), carLengthZ(21.0);
float blockLengthX(20.0), blockLengthY(40.0), blockLengthZ(20.0);
float blockX(30), blockY(9), blockZ(-25);

// Messages
std::string collisionMessage1 = "Game Over!\n";
std::string collisionMessage2 = "You Win!\n";

// space bar detection as when the user clicks on space bar 2 times at the beginning, the game starts
int spaceBarCounter = 0;

//The timer function callback declaration
void displayRemainingTime(int value);
bool isWaiting = 0;

// Lighting Globals
// Directional light from the top-left-front
GLfloat lightDirection[] = { 1, -1, 10, 0.0 };
// Warm orange color for sunset, will work as the diffusion and the specular property
GLfloat sunsetColor[] = { 1.0, 0.6, 0.2, 1.0 }; //= {0.0,0.0,0.0,1.0};// = { 1.0, 0.6, 0.2, 1.0 };

// Material Property Vectors || Globals
// Material properties for the car body.
float carMatAmb[] = { 0.0, 0.0, 1.0, 0.1 };
float carMatDif[] = { 0.0, 0.0, 1.0, 0.1 };
float carMatSpec[] = { 1.0, 1.0, 1.0, 0.1 };
float carMatShine[] = { 50.0 };
float carMatEmission[] = { 0.0, 0.0, 0.0, 1.0 };

// Material properties for the ground.
float groundMatAmb[] = { 0.57, 0.0, 0.34, 1.0 };
float groundMatDif[] = { 0.57, 0.0, 0.34, 1.0 };
float groundMatSpec[] = { 0.0, 0.0, 0.0, 1.0 };
float groundMatShine[] = { 0.0 };
float groundMatEmission[] = { 0.0, 0.0, 0.0, 1.0 };

// Material properties for the blocks.
float blockMatAmb[] = { 0.8588, 0.3216, 0.0353, 1.0 };
float blockMatDif[] = { 0.8588, 0.3216, 0.0353, 1.0 };
float blockMatSpec[] = { 0.10, 0.10, 0.10, 1.0 };
float blockMatShine[] = { 0.0 };
float blockMatEmission[] = { 0.0, 0.0, 0.0, 1.0 };

// Material properties for the target.
float targetMatAmb[] = { 1.0, 0.5, 1.0, 1.0 };
float targetMatDif[] = { 1.0, 0.5, 1.0, 1.0 };
float targetMatSpec[] = { 0.20, 0.20, 0.20, 1.0 };
float targetMatShine[] = { 0.0 };
float targetMatEmission[] = { 0.0, 0.0, 0.0, 1.0 };

// Material properties for the Wheels.
float wheelsMatAmb[] = { 1.0, 0.5, 1.0, 1.0 };
float wheelsMatDif[] = { 1.0, 0.5, 1.0, 1.0 };
float wheelsMatSpec[] = { 0.20, 0.20, 0.20, 1.0 };

// Spotlight globals
static float spotAngle = 50.0; // Spotlight cone half-angle.
float spotDirection[] = { 0.0, 0.0, -1.0 }; // Spotlight direction.
static float spotExponent = 1.0; // Spotlight attenuation exponent.
float spotLightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
float light1Pos[]={0.0, 0.0, 0.0,1.0};
float light2Pos[]={0.0, 0.0, 0.0};
bool showHideCone = 0.0;
float lengthOfCone = 40;
bool light1On = 1;
bool light2On = 1;
float L1 (0.0), L2(0.0), L3(0.0);

bool checkCollisionTarget() {
    // 18 and 18.5 was manually calculated based on the half of the Z length of the car and the target after all transformations applied
    bool collisionX = (fabs(CX - targetX) <= 18);
    bool collisionZ = (fabs(CZ - targetZ) <= 18.5);

    return collisionX && collisionZ;
}

bool collisionBlocks = false;

bool checkCollisionWithBlock(float blockX, float blockZ) {
    // Adjust collision logic based on your requirements
    bool collisionX = (fabs(CX - blockX) <= 15);
    bool collisionZ = (fabs(CZ - blockZ) <= 20.5);

    collisionBlocks = collisionX && collisionZ;
    return collisionBlocks;
}

// Initialization routine.
void setup(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);


    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunsetColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunsetColor);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotLightDifAndSpec);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spotLightDifAndSpec);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);



    glLightfv(GL_LIGHT2, GL_DIFFUSE, spotLightDifAndSpec);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spotLightDifAndSpec);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);


    float globAmb[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // Enable color material mode:
    // The ambient and diffuse color of the front faces will track the color set by glColor().
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void create_block(float x, float y, float z) {
    glColor3f(0.8588, 0.3216, 0.0353);
    glMaterialfv(GL_FRONT, GL_AMBIENT, blockMatAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blockMatDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, blockMatSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, blockMatShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, blockMatEmission);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0, 2.0, 1.0);
    glutSolidCube(20.0);
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

// Drawing routine.
void drawScene(void) {


    if (isBegin){
        change_block_noise();
        isBegin = false;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Spotlight properties.
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);


    // Update the camera position to follow the car.
    if (spaceBarCounter==2){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        gluLookAt(
                CX+zoom, CY + 10.0+zoom, CZ + 15.0 + zoom,  // eye position
                CX+zoom, CY+5+zoom, CZ+zoom,                 // center position (look at the car)
                0.0, 1.0, 0.0                       // up vector
        );
        // for animation
        glTranslatef(CX+5, CY+8, CZ-60); // center position (look at the car)
        glRotatef(angleX, 1.0, 0.0, 0.0);  // Rotate around the x_block-axis.
        glRotatef(angleY, 0.0, 1.0, 0.0);  // Rotate around the y_block-axis.
        glTranslatef(-CX-5,-CY-8,-CZ+60);



    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);

        gluLookAt(0.0,0.0,50.0,   0.0,0.0,55.0,  0.0,1.0,0.0 );
        float x =20.0; float y=10.0; float z=70.0;

        glPushMatrix();
        // A baby blue square for the first couple of messages
        glBegin(GL_POLYGON);
        glColor4f(0.678, 0.847, 0.902, 1.0);
        glVertex3f(-x,-y,z);
        glVertex3f(-x,y,z);
        glVertex3f(x,y,z);
        glVertex3f(x,-y,z);
        glEnd();
        glPopMatrix();

        glColor3f(0.0, 0.0, 0.0); // Set color to black for the first couple of messages.
        // Display messages.
        if(spaceBarCounter == 0){
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
        }

        else if (spaceBarCounter ==1 ){
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

    glTranslatef(0.0, 0.0, -20.0 );  // Move the entire car back along the z_block-axis with zoom factor.


    glPushMatrix();
    glTranslatef(CX, CY, CZ);
    glRotatef(-90, 0.0, 1.0, 0.0);

    // Draw the wheels
    // ===============
    glColor3f(0.0, 0.0, 0.0);  // Black color for the wheels.
    glMaterialfv(GL_FRONT, GL_AMBIENT, wheelsMatAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wheelsMatDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wheelsMatSpec);

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

    // Draw the car body
    // =================
    glColor3f(0.0, 0.0, 1.0);  // Blue color for the lower cuboid.
    glMaterialfv(GL_FRONT, GL_AMBIENT, carMatAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, carMatDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, carMatSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, carMatShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, carMatEmission);
    glScalef(0.7, 0.4, 1);
    glPushMatrix();
    glTranslatef(0, -carHeight / 4.0 + wheelRadius * 2.0, 0);  // Adjust the translation.
    glScalef(3, 1, 1);  // Adjust the scaling for desired proportions.
    glutSolidCube(carWidth);
    glPopMatrix();

    // Draw the upper cuboid
    // =====================
    glColor3f(0.0, 0.0, 0.0);  // Black color for the upper cuboid.
    glPushMatrix();
    glTranslatef(+3, +carHeight + wheelRadius * 2.0 + carHeight * 0.3, 0);
    glScalef(1.5, 0.6, 0.8);
    glutSolidCube(carWidth);
    glPopMatrix();

    // Draw the Spotlight balls
    // =====================
    glPushMatrix();//////////////////////////////////////////////////////////push1
    glRotatef(-90, 0.0, -1.0, 0.0);
    if (light1On) glEnable(GL_LIGHT1); else glDisable(GL_LIGHT1);
    if (light2On) glEnable(GL_LIGHT2); else glDisable(GL_LIGHT2);

    glPushMatrix();//////////////////////////////////////////////////////////push2
    glTranslatef(-2.6+L1, 4.2+L2 , -15.2+L3); //cone (yes), ball (yes) and spot pos
    std::cout<<"L1 L2 L3 are "<<L1<<" "<<L2<<" "<<L3<<endl;

    glDisable(GL_LIGHTING);
    glutWireSphere(1,10,10); //ball (right) not affected by light
    glEnable(GL_LIGHTING); ///enabling done

    glLightfv(GL_LIGHT1, GL_POSITION,light1Pos );

    glPopMatrix();//////////////////////////////////////////////////////////pop2

    glPushMatrix(); //////////////////////////////////////////////////////////push4

    glTranslatef(2.4+L1, 4.2+L2 , -15.2+L3); //cone, ball and spot pos

    glDisable(GL_LIGHTING);
    glutWireSphere(1,10,10); //ball (left) not affected by light
    glEnable(GL_LIGHTING); ///enabling don

    glLightfv(GL_LIGHT2, GL_POSITION,light2Pos );

    glPopMatrix();//////////////////////////////////////////////////////////pop4

    glPopMatrix();//////////////////////////////////////////////////////////pop1

    glPopMatrix();/////////////////////final pop all the above is under (glTranslatef(CX, CY, CZ); glRotatef(-90, 0.0, 1.0, 0.0);)

    // Draw the ground
    // ===============
    glColor3f(0.57, 0, 0.34);  // Reddish color for the ground.
    glMaterialfv(GL_FRONT, GL_AMBIENT, groundMatAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, groundMatDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, groundMatSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, groundMatShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, groundMatEmission);
    glPushMatrix();
    glTranslatef(0.0, -13.3, -88);
    glScalef(25.0, 1, 40.0);
    glutSolidCube(5.0);
    glPopMatrix();



    // Draw the Blocks
    // ===============
    for (int i = 0; i < 6; i++) {
        create_block(x_block * pow(-1,i) - h_block_noise[i]* pow(-1,i),
                     y_block,
                     z_block - i * vd_block + v_block_noise[i] * pow(-1,i) );
    }

    // Check collisions with blocks
    for (size_t i = 0; i < blockXPositions.size(); i++) {
        // the following line is to ensure that the program stops checking/iterating over the vectors after it detected a collision
        if (checkCollisionWithBlock(blockXPositions[i], blockZPositions[i])) {
            glColor3f(0.0, 0.0, 0.0); // Set color to black for collision messages.
            // Display messages.
            glRasterPos3f(CX, CY + 10, CZ + 12); // Adjust position for message display.
            for (char c : collisionMessage1) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            }
            if (!isWaiting) displayRemainingTime(4);
            break;
        }
    }

    // Target
    // ======
    glColor3f(1.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, targetMatAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, targetMatDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, targetMatSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, targetMatShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, targetMatEmission);
    glPushMatrix();
    glTranslatef(0, 5, -190);
    glScalef(4.0, 4, 1.5);
    glutSolidCube(8.0);
    glPopMatrix();

    if (checkCollisionTarget()) {
        glColor3f(0.0, 0.0, 0.0); // Set color to red for collision messages.
        // Display messages.
        glRasterPos3f(8.0, 5.0, -180.0); // Adjust position for message display.
        for (char c : collisionMessage2) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        if(!isWaiting) displayRemainingTime(4);
    }

    // Draw Target Symbol
    // Define the center
    float centerX = 0;
    float centerY = 5;
    float centerZ = -183;

    // Define the colors for the circles
    float colors[4][3] = {
            {0.0, 0.0, 0.0},  // Black
            {1.0, 1.0, 1.0},  // White
            {1.0, 0.0, 0.0},  // Red
            {0.0, 1.0, 0.0}   // Green
    };

    // Draw four filled circles with decreasing radii
    for (int i = 0; i < 4; ++i) {
        float radius = 6.0 - i * 1.0;
        int numSegments = 100;
        glBegin(GL_TRIANGLE_FAN);
        glColor3fv(colors[i]);
        glVertex3f(centerX, centerY, centerZ);
        for (int j = 0; j <= numSegments; ++j) {
            float theta = 2.0 * M_PI * static_cast<float>(j) / static_cast<float>(numSegments);
            float x = centerX + radius * cos(theta);
            float y = centerY + radius * sin(theta);
            glVertex3f(x, y, centerZ);
        }
        glEnd();

        // move to the next circle (prevention of intersection)
        centerZ += 1.0;
    }

    glutSwapBuffers();
}

void displayRemainingTime(int value) {
    if (value > 0) {
        isWaiting = true;  // Set the waiting state.
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0); // Set color to red for collision messages.
        if (collisionBlocks){
            glRasterPos3f(CX, CY + 8, CZ + 12);
        }
        else if (checkCollisionTarget()){
            glRasterPos3f(6.0, 3.0, -180.0); // Adjust position for message display.
        }
        std::string message = "Wait " + std::to_string(value) + " seconds and the game will restart";
        for (char c : message) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
        glPopMatrix();
        glutTimerFunc(1000, displayRemainingTime, value - 1);
    }
    else {
        // Restart the game
        CX = 0;
        CY = -6.3;
        CZ = 0.0;
        isWaiting = false;  // Reset the waiting state.
        x_block = generate_random_number(20, 40);           // Initial x_block position.
        z_block = -generate_random_number(15, 25);            // Initial z_block position.
        vd_block = generate_random_number(15, 30);

        // Clear the vectors when restarting the game
        blockXPositions.clear();
        blockZPositions.clear();
        collisionBlocks = 0;
        glutPostRedisplay();  // Trigger redraw to update the display.
    }

    glutSwapBuffers();
}
// OpenGL window reshape routine.
void resize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (double) w / (double) h, 1.0, 120.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

// Keyboard input processing routine.
void specialkey(int key, int x, int y){
    if(spaceBarCounter == 2 && (!(checkCollisionTarget() || collisionBlocks))){
        switch(key){
            case GLUT_KEY_UP:       //when the up key is pressed CZ++;
                if(CZ!=-173)
                    CZ--;
                break;
            case GLUT_KEY_DOWN:     //when the down arrow key is pressed CZ--;
                if(CZ!=7)
                    CZ++;
                break;
            case GLUT_KEY_LEFT:     //when the left arrow key is pressed CX--;
                if(CX!=-55 )
                    CX--;
                break;
            case GLUT_KEY_RIGHT:    //when the right arrow key is pressed CX++;
                if(CX!=55)
                    CX++;
                break;
            case GLUT_KEY_PAGE_DOWN:
            {
                std::cout<<"key page down, the spot angle is "<<spotAngle<< endl;
                if (spotAngle > 0.0) spotAngle -= 1.0;
            }
                break;
            case GLUT_KEY_PAGE_UP:
            {
                std::cout<<"key page up, the spot angle is "<<spotAngle<< endl;
                if (spotAngle < 90.0) spotAngle += 1.0;
            }
                break;
        }
    }
    glutPostRedisplay();
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
        case 'g':  // Restart the game.
            if (checkCollisionTarget() || collisionBlocks) {
                CX = 0;
                CY = -6.3;
                CZ = 0;
                angleX = 0.0;
                angleY = 0.0;
                zoom = 1.0;
                x_block = generate_random_number(20,40);                // Initial x_block position.
                z_block = -generate_random_number(21,30);               // Initial z_block position.
                vd_block = generate_random_number(15,30);
                change_block_noise();

                // Clear the vectors when restarting the game
                blockXPositions.clear();
                blockZPositions.clear();

                collisionBlocks = 0;
            }
            break;
        case 'f':  // Restart the game.
            if (checkCollisionTarget() || collisionBlocks) {
                CX = 0;
                CY = -6.3;
                CZ = 0;
                angleX = 0.0;
                angleY = 0.0;
                zoom = 1.0;

                collisionBlocks = 0;
            }
            break;
        case ' ':
            if (spaceBarCounter<=1)spaceBarCounter +=1;
            break;
        case 't':
        {
            std::cout<<"key t, the spot exponent is "<<spotExponent<< endl;
            if (spotExponent > 0.0) spotExponent -= 0.1;

        }
            break;
        case 'T':
        {
            std::cout<<"key T, the spot exponent is "<<spotExponent<< endl;
            spotExponent += 0.1;}
            break;
        case 's':
            showHideCone = !showHideCone;
            std::cout<<"show hide cone "<<showHideCone<<endl;
            break;
        case 'p':
            light1On = !light1On;
            std::cout<<" light 1 is "<<light1On<<endl;
            break;
        case 'a':
            light2On = !light2On;
            std::cout<<" light 2 is "<<light1On<<endl;
            break;

        case '7':
            L1-=0.2;
            break;
        case'8':
            L1+=0.2;
            break;
        case '4':
            L2-=0.2;
            break;
        case '5':
            L2+=0.2;
            break;
        case '1':
            L3-=0.2;
            break;
        case '2':
            L3+=0.2;
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }

    glutPostRedisplay();  // Request a redraw after updating the scene parameters.
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Car Simulation");
    glutDisplayFunc(drawScene);

    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialkey);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();

    return 0;
}
