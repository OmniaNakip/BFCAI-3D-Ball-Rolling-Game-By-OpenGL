#include <cstdlib> 
#include <GL/glut.h>
#include "../include/Constants.h"
#include "../include/Environment.h"
#include "../include/objects/Asteroids.h"
#include "../include/objects/Coins.h"

namespace {
float g_roadOffset = 0.0f;

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

}  // namespace

namespace Environment {
void Initialize() {
  g_roadOffset = 0.0f;
  Asteroids::Initialize();
  Coins::Initialize();
}

void Update(float dt) {
  const float travel = Constants::kObstacleSpeed * dt;
  const float segmentStep = Constants::kEdgeSegmentLength + Constants::kEdgeSegmentGap;

  g_roadOffset += travel;
  if (g_roadOffset > segmentStep) {
    g_roadOffset -= segmentStep;
  }

  Asteroids::Update(dt);
  Coins::Update(dt);
}

void Draw() {
  const float halfWidth = Constants::kGroundWidth * 0.5f;

  DrawGround(halfWidth);
  DrawRoadEdges(halfWidth);
  Asteroids::Draw();
  Coins::Draw();
}

std::vector<Physics::Aabb> GetObstacleAabbs() {
  return Asteroids::GetObstacleAabbs();
}

int CollectCoins(float cx, float cy, float cz, float radius) {
  return Coins::Collect(cx, cy, cz, radius);
}
}  // namespace Environment
