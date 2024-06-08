#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

bool carMoving = true; // Initialize car movement to false
bool isDay = true;


// Enum for color options
enum ColorOptions {
    RED = 1,
    PURPLE,
    ORANGE,
    PINK,
    BACK
};
int currentColor = RED; // Default color is red
void toggleDayNightMode() {
    isDay = !isDay; // Toggle the day/night mode
}

void drawTextRightAligned(const char* text, int length, int x, int y) {
    int textWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)text);
    glRasterPos2i(x - textWidth, y);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)text[i]);
    }
}

void drawText(const char* text, int length, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'E':
    case 'e':
        exit(0); // Exit the program when 'E' or 'e' is pressed
        break;
    case 'N':
    case 'n':
        toggleDayNightMode(); // Toggle day/night mode when 'N' or 'n' is pressed
        glutPostRedisplay(); // Request a redraw
        break;
    case 'D':
    case 'd':
        toggleDayNightMode(); // Toggle day/night mode when 'D' or 'd' is pressed
        glutPostRedisplay(); // Request a redraw
        break;
    }
}

void circle(GLfloat r, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void sun(GLfloat cx, GLfloat cy, GLfloat radius, int num_rays)
{
    if (isDay) {
        glColor3ub(255, 215, 0); // Yellow color for sun
    }
    else {
        glColor3ub(192, 192, 192); // Grey color for moon
    }
    circle(radius, cx, cy); // Draw sun/moon as a circle

    if (isDay) {
        float angleIncrement = 360.0 / num_rays;
        for (int i = 0; i < num_rays; ++i) {
            float angleRad = angleIncrement * i * 3.1416 / 180;
            float x1 = cx + radius * cos(angleRad);
            float y1 = cy + radius * sin(angleRad);
            float x2 = cx + (radius + 20) * cos(angleRad); // Lengthen the rays by 20 units
            float y2 = cy + (radius + 20) * sin(angleRad);
            glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glEnd();
        }
    }
}

void drawTree(float x, float y) {
    glColor3ub(139, 69, 19); // Brown trunk
    glBegin(GL_POLYGON);
    glVertex2f(x - 5, y); // Bottom-left corner of trunk
    glVertex2f(x + 5, y); // Bottom-right corner of trunk
    glVertex2f(x + 5, y + 40); // Top-right corner of trunk
    glVertex2f(x - 5, y + 40); // Top-left corner of trunk
    glEnd();

    glColor3ub(0, 100, 0); // Green leaves
    glBegin(GL_POLYGON);
    glVertex2f(x - 25, y + 40); // Bottom-left corner of leaves
    glVertex2f(x + 25, y + 40); // Bottom-right corner of leaves
    glVertex2f(x, y + 100); // Top corner of leaves
    glEnd();
}

void drawDottedLine(float startX, float endX, float y) {
    // Set stipple pattern for dashed line
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);

    // Draw dashed line
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(startX, y);
    glVertex2f(endX, y);
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

void init(void)
{
    glClearColor(0.53, 0.81, 0.925, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500, 0.0, 500); // window size
}



void hills() {
    // Hills 1
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(-40, 300);
    glVertex2d(200, 300);
    glVertex2d(100, 450);
    glEnd();

    // Hills 2
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2d(150, 300);
    glVertex2d(350, 300);
    glVertex2d(250, 450);
    glEnd();

    // Hills 3
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2d(300, 300);
    glVertex2d(520, 300);
    glVertex2d(400, 450);
    glEnd();
}
float bx = 10;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Ground Color
    if (isDay) {
        // Day mode background
        glClearColor(0.53, 0.81, 0.925, 0.0); // Blue sky
        // Other drawing functions for day mode
    }
    else {
        // Night mode background
        glClearColor(0.0, 0.0, 0.1, 0.0); // Dark blue sky
        // Other drawing functions for night mode
    }
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 150);
    glVertex2d(0, 150);
    glEnd();

    // Draw "Hello, player!" text in the center
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    drawText("Hello, player!", 14, 350, 320);

    // Road
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 55);
    glVertex2d(500, 55);
    glVertex2d(500, 115);
    glVertex2d(0, 115);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 60);
    glVertex2d(500, 60);
    glVertex2d(500, 110);
    glVertex2d(0, 110);
    glEnd();

    // Dotted line
    drawDottedLine(0, 500, 85);
    drawDottedLine(0, 500, 85 + 30);

    // Hills
    hills();

    drawTree(50, 150);
    drawTree(200, 150);
    drawTree(350, 150);

    // Sun design
    sun(175, 450, 30, 12);

    glPushMatrix();
    glTranslatef(bx, 0, 0);

    // Car body
    switch (currentColor) {
    case RED:
        glColor3ub(255, 0, 0);
        break;
    case PURPLE:
        glColor3ub(128, 0, 128);
        break;
    case ORANGE:
        glColor3ub(255, 165, 0);
        break;
    case PINK:
        glColor3ub(255, 105, 180);
        break;
    }

    glBegin(GL_POLYGON);
    glVertex2d(410, 100);
    glVertex2d(490, 100);
    glVertex2d(485, 130);
    glVertex2d(410, 130);
    glEnd();

    // Car roof
    switch (currentColor) {
    case RED:
        glColor3ub(255, 0, 0);
        break;
    case PURPLE:
        glColor3ub(128, 0, 128);
        break;
    case ORANGE:
        glColor3ub(255, 165, 0);
        break;
    case PINK:
        glColor3ub(255, 105, 180);
        break;
    }
    glBegin(GL_POLYGON);
    glVertex2d(420, 130);
    glVertex2d(475, 130);
    glVertex2d(465, 160);
    glVertex2d(430, 160);
    glEnd();

    // Car windows
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(425, 130);
    glVertex2d(445, 130);
    glVertex2d(445, 150);
    glVertex2d(430, 150);
    glEnd();

    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(450, 130);
    glVertex2d(470, 130);
    glVertex2d(465, 150);
    glVertex2d(450, 150);
    glEnd();

    // Car wheels
    glColor3ub(0, 0, 0);
    circle(10, 435, 100);
    circle(10, 465, 100);

    glColor3ub(245, 245, 245);
    circle(6, 435, 100);
    circle(6, 465, 100);

    // Draw headlight
    glColor3ub(255, 255, 0); // Yellow color for headlight
    circle(5, 485, 118); // Adjust position and size accordingly
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    drawTextRightAligned("Transylvania University from Brasov", 36, 600, 40);
    drawTextRightAligned("Faculty of Electrical Engineering and Computer Science", 54, 657, 30);
    drawTextRightAligned("Information Technology", 25, 563, 20);
    drawTextRightAligned("Popa Maria-Irina", 17, 540, 10);
    
    if (carMoving) {
        bx += 0.05;
        if (bx > 0) // Adjusted to stop at the right end of the screen
            bx = -500; // Adjusted to start again from the left end of the screen
    }

    glutPostRedisplay();
    glFlush();
}

void menu(int choice)
{
    switch (choice) {
    case RED:
    case PURPLE:
    case ORANGE:
    case PINK:
        currentColor = choice;
        glutPostRedisplay();
        break;
    case BACK:
        break;
    }
}

void createMenu()
{
    int submenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Purple", PURPLE);
    glutAddMenuEntry("Orange", ORANGE);
    glutAddMenuEntry("Pink", PINK);

    glutCreateMenu(menu);
    glutAddSubMenu("Change color", submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // Using GLUT_LEFT_BUTTON
        // Toggle the car's movement state
        carMoving = !carMoving;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(300, 50);
    glutCreateWindow("A Moving Car Scenario");
    glutKeyboardFunc(keyboard);
    init();
    glutDisplayFunc(display);
    createMenu(); // Create the menu
    glutMouseFunc(mouse); // Register the mouse callback function
    glutMainLoop();
    
    return 0;
}
