#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Camera.h"
#include "Constants.h"
#include "Environment.h"
#include "GameState.h"
#include "Graphics.h"
#include "Physics.h"
#include "Player.h"

namespace {
GameState::Screen g_screen = GameState::Screen::Menu;
int g_windowWidth = Constants::kWindowWidth;
int g_windowHeight = Constants::kWindowHeight;
float g_scoreSeconds = 0.0f;
int g_coinCount = 0;

void ResetRun() {
  Player::Initialize();
  Environment::Initialize();
  g_scoreSeconds = 0.0f;
  g_coinCount = 0;
}

void DrawBitmapText(float x, float y, const char* text) {
  glRasterPos2f(x, y);
  for (const char* p = text; *p != '\0'; ++p) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
  }
}

void RenderOverlay(const char* line1, const char* line2, const char* line3) {
  const GLboolean lightingEnabled = glIsEnabled(GL_LIGHTING);
  const GLboolean depthEnabled = glIsEnabled(GL_DEPTH_TEST);

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, g_windowWidth, 0.0, g_windowHeight);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glColor3f(1.0f, 1.0f, 1.0f);

  const float startX = g_windowWidth * 0.5f - 110.0f;
  const float startY = g_windowHeight * 0.6f;
  DrawBitmapText(startX, startY, line1);
  if (line2 != nullptr) {
    DrawBitmapText(startX, startY - 24.0f, line2);
  }
  if (line3 != nullptr) {
    DrawBitmapText(startX, startY - 48.0f, line3);
  }

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  if (depthEnabled) {
    glEnable(GL_DEPTH_TEST);
  }
  if (lightingEnabled) {
    glEnable(GL_LIGHTING);
  }
}

void RenderHud() {
  const GLboolean lightingEnabled = glIsEnabled(GL_LIGHTING);
  const GLboolean depthEnabled = glIsEnabled(GL_DEPTH_TEST);

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, g_windowWidth, 0.0, g_windowHeight);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glColor3f(1.0f, 1.0f, 1.0f);

  char scoreLine[64];
  char coinLine[64];
  std::snprintf(scoreLine, sizeof(scoreLine), "Score: %.1f", g_scoreSeconds);
  std::snprintf(coinLine, sizeof(coinLine), "Coins: %d", g_coinCount);

  DrawBitmapText(12.0f, g_windowHeight - 24.0f, scoreLine);
  DrawBitmapText(12.0f, g_windowHeight - 46.0f, coinLine);

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  if (depthEnabled) {
    glEnable(GL_DEPTH_TEST);
  }
  if (lightingEnabled) {
    glEnable(GL_LIGHTING);
  }
}

void RenderScene3d() {
  const PlayerState player = Player::GetState();
  Camera::Apply(g_windowWidth, g_windowHeight, player.x, player.y, player.z);
  Environment::Draw();
  Player::Draw();
}

void UpdateGameplay(float dt) {
  Player::Update(dt);
  Environment::Update(dt);
  g_scoreSeconds += dt;

  const PlayerState player = Player::GetState();
  g_coinCount += Environment::CollectCoins(player.x, player.y, player.z, player.radius);
  const std::vector<Physics::Aabb> obstacles = Environment::GetObstacleAabbs();
  for (const Physics::Aabb& box : obstacles) {
    if (Physics::CheckCircleAabb(player.x, player.y, player.z, player.radius, box)) {
      g_screen = GameState::Screen::GameOver;
      break;
    }
  }
}
}  // namespace

namespace GameState {
void Initialize() {
  Graphics::SetupLighting();
  ResetRun();
  g_screen = Screen::Menu;
}

void Update(float dt) {
  if (g_screen == Screen::Playing) {
    UpdateGameplay(dt);
  }
}

void Render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  RenderScene3d();

  if (g_screen == Screen::Playing) {
    RenderHud();
  }

  if (g_screen == Screen::Menu) {
    RenderOverlay("Endless Runner 3D", "Press Enter to Start", nullptr);
  } else if (g_screen == Screen::GameOver) {
    char scoreLine[64];
    std::snprintf(scoreLine, sizeof(scoreLine), "Score: %.1f  Coins: %d", g_scoreSeconds,
                  g_coinCount);
    RenderOverlay("Game Over", "Press R to Restart", scoreLine);
  }

  glutSwapBuffers();
}

void OnKeyDown(unsigned char key, int, int) {
  if (key == 27) {
    std::exit(0);
  }

  if (g_screen == Screen::Menu && key == 13) {
    ResetRun();
    g_screen = Screen::Playing;
    return;
  }

  if (g_screen == Screen::GameOver && (key == 'r' || key == 'R')) {
    ResetRun();
    g_screen = Screen::Playing;
    return;
  }

  if (g_screen != Screen::Playing) {
    return;
  }

  if (key == 'a' || key == 'A') {
    Player::MoveLeft();
  } else if (key == 'd' || key == 'D') {
    Player::MoveRight();
  } else if (key == ' ') {
    Player::Jump();
  }
}

void OnSpecialDown(int key, int, int) {
  if (g_screen != Screen::Playing) {
    return;
  }

  if (key == GLUT_KEY_LEFT) {
    Player::MoveLeft();
  } else if (key == GLUT_KEY_RIGHT) {
    Player::MoveRight();
  } else if (key == GLUT_KEY_UP) {
    Player::Jump();
  }
}

void OnResize(int width, int height) {
  if (height == 0) {
    height = 1;
  }
  g_windowWidth = width;
  g_windowHeight = height;
  glViewport(0, 0, width, height);
}

Screen GetState() {
  return g_screen;
}

void SetState(Screen state) {
  g_screen = state;
}
}  // namespace GameState
