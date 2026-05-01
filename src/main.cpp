#include <GL/glut.h>
#include <cstdio>
#include <chrono>

#include "Constants.h"
#include "GameState.h"

namespace {
auto g_lastTime = std::chrono::high_resolution_clock::now();

void DisplayCallback() {
  GameState::Render();
}

void KeyboardCallback(unsigned char key, int x, int y) {
  GameState::OnKeyDown(key, x, y);
}

void SpecialCallback(int key, int x, int y) {
  GameState::OnSpecialDown(key, x, y);
}

void ReshapeCallback(int width, int height) {
  GameState::OnResize(width, height);
}

void TimerCallback(int value) {
  auto currentTime = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration<float>(currentTime - g_lastTime);
  float dt = elapsed.count();
  
  if (dt > 0.05f) {
    dt = 0.05f;
  }
  
  g_lastTime = currentTime;
  
  GameState::Update(dt);
  glutPostRedisplay();
  
  glutTimerFunc(Constants::kFrameMs, TimerCallback, 0);
}

void InitializeOpenGL(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(Constants::kWindowWidth, Constants::kWindowHeight);
  glutInitWindowPosition(50, 50);
  glutCreateWindow(Constants::kWindowTitle);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  
  glClearColor(
    Constants::kClearColorR,
    Constants::kClearColorG,
    Constants::kClearColorB,
    Constants::kClearColorA
  );
  
  glutDisplayFunc(DisplayCallback);
  glutKeyboardFunc(KeyboardCallback);
  glutSpecialFunc(SpecialCallback);
  glutReshapeFunc(ReshapeCallback);
  glutTimerFunc(Constants::kFrameMs, TimerCallback, 0);
}
}  // namespace

int main(int argc, char* argv[]) {
  InitializeOpenGL(argc, argv);
  GameState::Initialize();
  
  glutMainLoop();
  
  return 0;
}
