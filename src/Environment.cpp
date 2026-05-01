#include <GL/glut.h>
#include <vector>

#include "Constants.h"
#include "Environment.h"

namespace {
struct Obstacle {
  float x;
  float z;
  float size;
  float rotation;
};

struct Coin {
  float x;
  float z;
};

std::vector<Obstacle> g_obstacles;
std::vector<Coin> g_coins;
float g_roadOffset = 0.0f;

void AddObstacle(int laneIndex, float z, int index) {
  Obstacle obstacle;
  obstacle.x = static_cast<float>(laneIndex) * Constants::kLaneWidth;
  obstacle.z = z;
  obstacle.size = Constants::kObstacleSize;
  obstacle.rotation = static_cast<float>((index * 37) % 360);
  g_obstacles.push_back(obstacle);
}

void AddCoin(int laneIndex, float z) {
  Coin coin;
  coin.x = static_cast<float>(laneIndex) * Constants::kLaneWidth;
  coin.z = z;
  g_coins.push_back(coin);
}

void DrawGround(float halfWidth) {
  const float backZ = Constants::kGroundBackZ;
  const float frontZ = -Constants::kGroundLength;

  glColor3f(0.2f, 0.2f, 0.2f);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-halfWidth, Constants::kGroundY, backZ);
  glVertex3f(halfWidth, Constants::kGroundY, backZ);
  glVertex3f(halfWidth, Constants::kGroundY, frontZ);
  glVertex3f(-halfWidth, Constants::kGroundY, frontZ);
  glEnd();
}

void DrawRoadEdges(float halfWidth) {
  const GLboolean lightingEnabled = glIsEnabled(GL_LIGHTING);
  if (lightingEnabled) {
    glDisable(GL_LIGHTING);
  }

  const float edgeY = Constants::kGroundY + Constants::kRoadEdgeHeight;
  const float edgeWidth = Constants::kRoadEdgeWidth;
  const float segmentLength = Constants::kEdgeSegmentLength;
  const float segmentStep = Constants::kEdgeSegmentLength + Constants::kEdgeSegmentGap;
  const float totalLength = Constants::kGroundBackZ + Constants::kGroundLength;
  const int segmentCount = static_cast<int>(totalLength / segmentStep) + 2;

  for (int i = 0; i < segmentCount; ++i) {
    float zStart = Constants::kGroundBackZ + g_roadOffset - (static_cast<float>(i) * segmentStep);
    if (zStart > Constants::kGroundBackZ) {
      zStart = Constants::kGroundBackZ;
    }
    float zEnd = zStart - segmentLength;
    if (zEnd < -Constants::kGroundLength) {
      zEnd = -Constants::kGroundLength;
    }

    if (i % 2 == 0) {
      glColor3f(Constants::kEdgeColor1R, Constants::kEdgeColor1G, Constants::kEdgeColor1B);
    } else {
      glColor3f(Constants::kEdgeColor2R, Constants::kEdgeColor2G, Constants::kEdgeColor2B);
    }

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-halfWidth, edgeY, zStart);
    glVertex3f(-halfWidth + edgeWidth, edgeY, zStart);
    glVertex3f(-halfWidth + edgeWidth, edgeY, zEnd);
    glVertex3f(-halfWidth, edgeY, zEnd);

    glVertex3f(halfWidth - edgeWidth, edgeY, zStart);
    glVertex3f(halfWidth, edgeY, zStart);
    glVertex3f(halfWidth, edgeY, zEnd);
    glVertex3f(halfWidth - edgeWidth, edgeY, zEnd);
    glEnd();
  }

  if (lightingEnabled) {
    glEnable(GL_LIGHTING);
  }
}

void DrawObstacles() {
  glColor3f(Constants::kAsteroidColorR, Constants::kAsteroidColorG, Constants::kAsteroidColorB);
  for (const Obstacle& obstacle : g_obstacles) {
    const float baseScale = obstacle.size * 0.6f;
    glPushMatrix();
    glTranslatef(obstacle.x, Constants::kGroundY + (obstacle.size * 0.6f), obstacle.z);
    glRotatef(obstacle.rotation, 0.3f, 1.0f, 0.2f);
    glScalef(
        baseScale * Constants::kAsteroidScaleX,
        baseScale * Constants::kAsteroidScaleY,
        baseScale * Constants::kAsteroidScaleZ);
    glutSolidIcosahedron();
    glPopMatrix();
  }
}

void DrawCoins() {
  const GLboolean lightingEnabled = glIsEnabled(GL_LIGHTING);
  if (lightingEnabled) {
    glDisable(GL_LIGHTING);
  }

  glColor3f(Constants::kCoinColorR, Constants::kCoinColorG, Constants::kCoinColorB);
  for (const Coin& coin : g_coins) {
    glPushMatrix();
    glTranslatef(coin.x, Constants::kCoinHeight, coin.z);
    glutSolidSphere(Constants::kCoinRadius, 16, 16);
    glPopMatrix();
  }

  if (lightingEnabled) {
    glEnable(GL_LIGHTING);
  }
}
}  // namespace

namespace Environment {
void Initialize() {
  g_obstacles.clear();
  g_coins.clear();
  g_roadOffset = 0.0f;

  const int obstacleCount = 5;
  for (int i = 0; i < obstacleCount; ++i) {
    const int laneIndex = (i % Constants::kLaneCount) - (Constants::kLaneCount / 2);
    const float z = Constants::kObstacleStartZ - (Constants::kObstacleSpacing * i);
    AddObstacle(laneIndex, z, i);
  }

  for (int i = 0; i < Constants::kCoinCount; ++i) {
    const int laneIndex = (i % Constants::kLaneCount) - (Constants::kLaneCount / 2);
    const float z = Constants::kCoinStartZ - (Constants::kCoinSpacing * i);
    AddCoin(laneIndex, z);
  }

}

void Update(float dt) {
  const float travel = Constants::kObstacleSpeed * dt;
  const float segmentStep = Constants::kEdgeSegmentLength + Constants::kEdgeSegmentGap;

  g_roadOffset += travel;
  if (g_roadOffset > segmentStep) {
    g_roadOffset -= segmentStep;
  }

  const float obstacleWrap =
      Constants::kObstacleSpacing * static_cast<float>(g_obstacles.size());
  for (Obstacle& obstacle : g_obstacles) {
    obstacle.z += travel;
    if (obstacle.z > Constants::kObstacleResetZ) {
      obstacle.z -= obstacleWrap;
    }
  }

  const float coinWrap = Constants::kCoinSpacing * static_cast<float>(g_coins.size());
  for (Coin& coin : g_coins) {
    coin.z += travel;
    if (coin.z > Constants::kObstacleResetZ) {
      coin.z -= coinWrap;
    }
  }

}

void Draw() {
  const float halfWidth = Constants::kGroundWidth * 0.5f;

  DrawGround(halfWidth);
  DrawRoadEdges(halfWidth);
  DrawObstacles();
  DrawCoins();
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

int CollectCoins(float cx, float cy, float cz, float radius) {
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
}  // namespace Environment
