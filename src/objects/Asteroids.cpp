#include <cstdlib> 
#include <GL/glut.h>
#include <vector>

#include "../../include/Constants.h"
#include "../../include/objects/Asteroids.h"

namespace {
struct Asteroid {
  float x;
  float z;
  float size;
  float rotation;
};

std::vector<Asteroid> g_asteroids;

void AddAsteroid(int laneIndex, float z, int index) {
  Asteroid asteroid;
  asteroid.x = static_cast<float>(laneIndex) * Constants::kLaneWidth;
  asteroid.z = z;
  asteroid.size = Constants::kObstacleSize;
  asteroid.rotation = static_cast<float>((index * 37) % 360);
  g_asteroids.push_back(asteroid);
}
}  // namespace

namespace Asteroids {
void Initialize() {
  g_asteroids.clear();
  const int asteroidCount = 5;
  for (int i = 0; i < asteroidCount; ++i) {
    const int laneIndex = (i % Constants::kLaneCount) - (Constants::kLaneCount / 2);
    const float z = Constants::kObstacleStartZ - (Constants::kObstacleSpacing * i);
    AddAsteroid(laneIndex, z, i);
  }
}

void Update(float dt) {
  const float travel = Constants::kObstacleSpeed * dt;
  const float wrapDistance =
      Constants::kObstacleSpacing * static_cast<float>(g_asteroids.size());

  for (Asteroid& asteroid : g_asteroids) {
    asteroid.z += travel;
    if (asteroid.z > Constants::kObstacleResetZ) {
      asteroid.z -= wrapDistance;
    }
  }
}

void Draw() {
  glColor3f(Constants::kAsteroidColorR, Constants::kAsteroidColorG, Constants::kAsteroidColorB);
  for (const Asteroid& asteroid : g_asteroids) {
    const float baseScale = asteroid.size * 0.6f;
    glPushMatrix();
    glTranslatef(asteroid.x, Constants::kGroundY + (asteroid.size * 0.6f), asteroid.z);
    glRotatef(asteroid.rotation, 0.3f, 1.0f, 0.2f);
    glScalef(
        baseScale * Constants::kAsteroidScaleX,
        baseScale * Constants::kAsteroidScaleY,
        baseScale * Constants::kAsteroidScaleZ);
    glutSolidIcosahedron();
    glPopMatrix();
  }
}

std::vector<Physics::Aabb> GetObstacleAabbs() {
  std::vector<Physics::Aabb> boxes;
  boxes.reserve(g_asteroids.size());
  for (const Asteroid& asteroid : g_asteroids) {
    const float half = asteroid.size * 0.5f;
    Physics::Aabb box;
    box.minX = asteroid.x - half;
    box.maxX = asteroid.x + half;
    box.minY = Constants::kGroundY;
    box.maxY = Constants::kGroundY + asteroid.size;
    box.minZ = asteroid.z - half;
    box.maxZ = asteroid.z + half;
    boxes.push_back(box);
  }
  return boxes;
}
}  // namespace Asteroids
