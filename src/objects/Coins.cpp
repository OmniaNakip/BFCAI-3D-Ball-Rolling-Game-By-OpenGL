#include <cstdlib> 
#include <GL/glut.h>
#include <vector>

#include "../../include/Constants.h"
#include "../../include/Physics.h"
#include "../../include/objects/Coins.h"

namespace {
struct Coin {
  float x;
  float z;
  float rotation;  // Rotation angle for spinning animation
};

std::vector<Coin> g_coins;

void AddCoin(int laneIndex, float z) {
  Coin coin;
  coin.x = static_cast<float>(laneIndex) * Constants::kLaneWidth;
  coin.z = z;
  coin.rotation = 0.0f;
  g_coins.push_back(coin);
}
}  // namespace

namespace Coins {
void Initialize() {
  g_coins.clear();
  for (int i = 0; i < Constants::kCoinCount; ++i) {
    const int laneIndex = (i % Constants::kLaneCount) - (Constants::kLaneCount / 2);
    const float z = Constants::kCoinStartZ - (Constants::kCoinSpacing * i);
    AddCoin(laneIndex, z);
  }
}

void Update(float dt, float currentSpeed) {
  const float travel = currentSpeed * dt;
  const float wrapDistance = Constants::kCoinSpacing * static_cast<float>(g_coins.size());
  const float rotationSpeed = 180.0f;  // Degrees per second
  
  for (Coin& coin : g_coins) {
    coin.z += travel;
    coin.rotation += rotationSpeed * dt;
    if (coin.rotation > 360.0f) {
      coin.rotation -= 360.0f;
    }
    if (coin.z > Constants::kObstacleResetZ) {
      coin.z -= wrapDistance;
    }
  }
}

void Draw() {
  const GLboolean lightingEnabled = glIsEnabled(GL_LIGHTING);
  if (lightingEnabled) {
    glDisable(GL_LIGHTING);
  }

  glColor3f(Constants::kCoinColorR, Constants::kCoinColorG, Constants::kCoinColorB);
  for (const Coin& coin : g_coins) {
    glPushMatrix();
    glTranslatef(coin.x, Constants::kCoinHeight, coin.z);
    glRotatef(coin.rotation, 1.0f, 0.0f, 0.0f);  // Rotate about X-axis for spinning effect
    // Scale to create a coin-like disk shape (flat and circular)
    glScalef(1.0f, 0.2f, 1.0f);
    glutSolidSphere(Constants::kCoinRadius, 16, 16);
    glPopMatrix();
  }

  if (lightingEnabled) {
    glEnable(GL_LIGHTING);
  }
}

int Collect(float cx, float cy, float cz, float radius) {
  int collected = 0;
  const float wrapDistance = Constants::kCoinSpacing * static_cast<float>(g_coins.size());
  for (Coin& coin : g_coins) {
    Physics::Aabb box;
    box.minX = coin.x - Constants::kCoinRadius;
    box.maxX = coin.x + Constants::kCoinRadius;
    box.minY = Constants::kCoinHeight - Constants::kCoinRadius;
    box.maxY = Constants::kCoinHeight + Constants::kCoinRadius;
    box.minZ = coin.z - Constants::kCoinRadius;
    box.maxZ = coin.z + Constants::kCoinRadius;

    if (Physics::CheckCircleAabb(cx, cy, cz, radius, box)) {
      ++collected;
      coin.z -= wrapDistance;
    }
  }
  return collected;
}
}  // namespace Coins
