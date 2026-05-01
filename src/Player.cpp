#include <GL/glut.h>

#include "Constants.h"
#include "Player.h"

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
}

void Update(float dt) {
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
}

void Draw() {
  glPushMatrix();
  glTranslatef(g_player.x, g_player.y, g_player.z);
  glColor3f(0.2f, 0.6f, 1.0f);
  glutSolidSphere(g_player.radius, 18, 18);
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
