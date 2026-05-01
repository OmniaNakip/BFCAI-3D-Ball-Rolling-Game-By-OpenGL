#include <cstdlib> 
#include <GL/glut.h>

#include "../include/Camera.h"
#include "../include/Constants.h"

namespace Camera {
void Apply(int width, int height, float targetX, float targetY, float targetZ) {
  if (height == 0) {
    height = 1;
  }

  const float aspect = static_cast<float>(width) / static_cast<float>(height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, aspect, 0.1f, 200.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  const float eyeX = 0.0f;
  const float eyeY = targetY + Constants::kCameraHeight;
  const float eyeZ = targetZ + Constants::kCameraDistance;

  const float centerX = 0.0f;
  const float centerY = targetY;
  const float centerZ = targetZ + Constants::kCameraLookAhead;

  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);
}
}  // namespace Camera
