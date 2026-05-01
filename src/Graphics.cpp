#include <GL/glut.h>

#include "Graphics.h"

namespace Graphics {
void SetupLighting() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  const GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  const GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  const GLfloat specular[] = {0.4f, 0.4f, 0.4f, 1.0f};
  const GLfloat position[] = {0.0f, 6.0f, 4.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 24.0f);
}
}  // namespace Graphics
