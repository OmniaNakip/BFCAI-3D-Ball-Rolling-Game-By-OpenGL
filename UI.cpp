#include "UI.h"

int screen = 0;

void drawText(float x, float y, string text, void* font = GLUT_BITMAP_HELVETICA_18)
{
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(font, c);
}

void drawMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1400, 0, 700);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 0.8, 0);
    drawText(600, 600, "BALL GAME");

    glColor3f(0.1, 0.6, 0.1);
    glBegin(GL_QUADS);
        glVertex2f(550, 420);
        glVertex2f(850, 420);
        glVertex2f(850, 360);
        glVertex2f(550, 360);
    glEnd();
    glColor3f(1, 1, 1);
    drawText(640, 385, "START GAME");

    glColor3f(0.1, 0.1, 0.6);
    glBegin(GL_QUADS);
        glVertex2f(550, 320);
        glVertex2f(850, 320);
        glVertex2f(850, 260);
        glVertex2f(550, 260);
    glEnd();

    // FIXED VISIBILITY ISSUE
    glColor3f(1, 1, 1);
    drawText(640, 285, "ABOUT GAME");

    glColor3f(0.6, 0.1, 0.1);
    glBegin(GL_QUADS);
        glVertex2f(550, 220);
        glVertex2f(850, 220);
        glVertex2f(850, 160);
        glVertex2f(550, 160);
    glEnd();
    glColor3f(1, 1, 1);
    drawText(650, 185, "QUIT");

    glutSwapBuffers();
}

void drawAbout()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1400, 0, 700);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 0.8, 0);
    drawText(600, 620, "ABOUT GAME");

    glColor3f(1, 1, 1);
    drawText(100, 550, "Hint: Avoid obstacles and survive!");
    drawText(100, 500, "Use arrow keys to move");

    drawText(100, 420, "Team Members:");
    drawText(100, 380, "Ahmed Hazem Elabady");
    drawText(100, 350, "Ahmed Badwy");
    drawText(100, 320, "Alaa Osama Mohamed Bekhit");
    drawText(100, 290, "Abanoub Rizk Gad");
    drawText(100, 260, "Abdelrahman Reda Abdelrahman Abdelstar");
    drawText(100, 230, "Omnia Mohamed Ahmed Naqeeb");

    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
        glVertex2f(600, 100);
        glVertex2f(800, 100);
        glVertex2f(800, 50);
        glVertex2f(600, 50);
    glEnd();
    glColor3f(1, 1, 1);
    drawText(670, 70, "BACK");

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    y = 700 - y;

    if (screen == 0)
    {
        if (x > 550 && x < 850 && y > 360 && y < 420) screen = 1;
        else if (x > 550 && x < 850 && y > 260 && y < 320) screen = 2;
        else if (x > 550 && x < 850 && y > 160 && y < 220) exit(0);
    }
    else if (screen == 2)
    {
        if (x > 600 && x < 800 && y > 50 && y < 100) screen = 0;
    }
}
