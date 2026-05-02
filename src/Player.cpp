#include <cstdlib> 
#include <GL/glut.h>
#include <cmath>

#include "../include/Constants.h"
#include "../include/Player.h"

namespace {
PlayerState g_player;

float LaneToX(int laneIndex) {
  return static_cast<float>(laneIndex) * Constants::kLaneWidth;
}
}  // namespace

namespace Player {
void Initialize() {
  g_player.lane = 0;
  g_player.x = 0.0f;
  g_player.y = Constants::kPlayerGroundY;
  g_player.z = 0.0f;
  g_player.radius = Constants::kPlayerRadius;
  g_player.velocityY = 0.0f;
  g_player.grounded = true;
  g_player.forwardRotation = 0.0f;
}

void Update(float dt, float currentSpeed) {
  g_player.x = LaneToX(g_player.lane);

  if (!g_player.grounded) {
    g_player.velocityY -= Constants::kGravity * dt;
    g_player.y += g_player.velocityY * dt;
    if (g_player.y <= Constants::kPlayerGroundY) {
      g_player.y = Constants::kPlayerGroundY;
      g_player.velocityY = 0.0f;
      g_player.grounded = true;
    }
  }

  // Update forward rotation based on current speed (wheel rolling animation)
  // Rotation speed is proportional to the road speed
  const float baseRotationPerSecond = 45.0f;  // Degrees per second per unit speed
  g_player.forwardRotation += baseRotationPerSecond * currentSpeed * dt;
  if (g_player.forwardRotation > 360.0f) {
    g_player.forwardRotation -= 360.0f;
  }
}

void Draw() {
  glPushMatrix();
  glTranslatef(g_player.x, g_player.y, g_player.z);
  
  // Apply forward rotation for wheel rolling effect (rotate around X-axis, reversed)
  glRotatef(-g_player.forwardRotation, 1.0f, 0.0f, 0.0f);
  
  // Draw main ball
  glColor3f(0.2f, 0.6f, 1.0f);
  glutSolidSphere(g_player.radius, 18, 18);
  
  // Draw curved stripes to emphasize rotation
  glDisable(GL_LIGHTING);
  glColor3f(0.1f, 0.8f, 1.0f);  // Lighter blue stripe
  
  // Draw two perpendicular stripe bands to show rotation
  glLineWidth(3.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    float x = g_player.radius * cosf(rad);
    float y = g_player.radius * sinf(rad);
    glVertex3f(x, y, 0.0f);
  }
  glEnd();
  
  // Draw another stripe perpendicular
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    float y = g_player.radius * cosf(rad);
    float z = g_player.radius * sinf(rad);
    glVertex3f(0.0f, y, z);
  }
  glEnd();
  
  glLineWidth(1.0f);
  glEnable(GL_LIGHTING);
  
  glPopMatrix();
}

void MoveLeft() {
  if (g_player.lane > -(Constants::kLaneCount / 2)) {
    g_player.lane -= 1;
  }
}

void MoveRight() {
  if (g_player.lane < (Constants::kLaneCount / 2)) {
    g_player.lane += 1;
  }
}

void Jump() {
  if (!g_player.grounded) {
    return;
  }
  g_player.velocityY = Constants::kJumpVelocity;
  g_player.grounded = false;
}

PlayerState GetState() {
  return g_player;
}
}  // namespace Player
