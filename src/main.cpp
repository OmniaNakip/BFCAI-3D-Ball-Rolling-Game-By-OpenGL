#include <cstdlib>
#include <GL/glut.h>
#include "../include/Constants.h"
#include "../include/GameState.h"

void DisplayCallback() {
    GameState::Render();
}

void KeyboardCallback(unsigned char key, int x, int y) {
    GameState::OnKeyDown(key, x, y);
}

void SpecialCallback(int key, int x, int y) {
    GameState::OnSpecialDown(key, x, y);
}

void MouseCallback(int button, int state, int x, int y) {
    GameState::OnMouse(button, state, x, y);
}

void ReshapeCallback(int width, int height) {
    GameState::OnResize(width, height);
}

void TimerCallback(int value) {
    GameState::Update(Constants::kFrameSeconds);
    glutPostRedisplay();
    glutTimerFunc(Constants::kFrameMs, TimerCallback, 0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(Constants::kWindowWidth, Constants::kWindowHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow(Constants::kWindowTitle);
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(
        Constants::kClearColorR,
        Constants::kClearColorG,
        Constants::kClearColorB,
        Constants::kClearColorA
    );
    
    glutDisplayFunc(DisplayCallback);
    glutKeyboardFunc(KeyboardCallback);
    glutSpecialFunc(SpecialCallback);
    glutMouseFunc(MouseCallback);
    glutReshapeFunc(ReshapeCallback);
    glutTimerFunc(Constants::kFrameMs, TimerCallback, 0);
    
    GameState::Initialize();
    
    GameState::OnResize(Constants::kWindowWidth, Constants::kWindowHeight);

    glutMainLoop();
    
    return 0;
}