#include <GL/glut.h>
#include <vector>

#include "Constants.h"
#include "Environment.h"

namespace {
struct Obstacle {
  float x;
  float z;
  float size;
};

std::vector<Obstacle> g_obstacles;

void AddObstacle(int laneIndex, float z) {
  Obstacle obstacle;
  obstacle.x = static_cast<float>(laneIndex) * Constants::kLaneWidth;
  obstacle.z = z;
  obstacle.size = Constants::kObstacleSize;
  g_obstacles.push_back(obstacle);
}
}  // namespace

namespace Environment {
void Initialize() {
  g_obstacles.clear();
  const int obstacleCount = 5;
  for (int i = 0; i < obstacleCount; ++i) {
    const int laneIndex = (i % Constants::kLaneCount) - (Constants::kLaneCount / 2);
    const float z = Constants::kObstacleStartZ - (Constants::kObstacleSpacing * i);
    AddObstacle(laneIndex, z);
  }
}

void Update(float dt) {
  const float travel = Constants::kObstacleSpeed * dt;
  const float wrapDistance = Constants::kObstacleSpacing * static_cast<float>(g_obstacles.size());
  for (Obstacle& obstacle : g_obstacles) {
    obstacle.z += travel;
    if (obstacle.z > Constants::kObstacleResetZ) {
      obstacle.z -= wrapDistance;
    }
  }
}

void Draw() {
  const float halfWidth = Constants::kGroundWidth * 0.5f;

  glColor3f(0.2f, 0.2f, 0.2f);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-halfWidth, Constants::kGroundY, 0.0f);
  glVertex3f(halfWidth, Constants::kGroundY, 0.0f);
  glVertex3f(halfWidth, Constants::kGroundY, -Constants::kGroundLength);
  glVertex3f(-halfWidth, Constants::kGroundY, -Constants::kGroundLength);
  glEnd();

  glColor3f(0.8f, 0.3f, 0.3f);
  for (const Obstacle& obstacle : g_obstacles) {
    glPushMatrix();
    glTranslatef(obstacle.x, Constants::kGroundY + (obstacle.size * 0.5f), obstacle.z);
    glutSolidCube(obstacle.size);
    glPopMatrix();
  }
}

std::vector<Physics::Aabb> GetObstacleAabbs() {
  std::vector<Physics::Aabb> boxes;
  boxes.reserve(g_obstacles.size());
  for (const Obstacle& obstacle : g_obstacles) {
    const float half = obstacle.size * 0.5f;
    Physics::Aabb box;
    box.minX = obstacle.x - half;
    box.maxX = obstacle.x + half;
    box.minY = Constants::kGroundY;
    box.maxY = Constants::kGroundY + obstacle.size;
    box.minZ = obstacle.z - half;
    box.maxZ = obstacle.z + half;
    boxes.push_back(box);
  }
  return boxes;
}
}  // namespace Environment
