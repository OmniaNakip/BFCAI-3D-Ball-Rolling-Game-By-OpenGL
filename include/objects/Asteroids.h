#ifndef OBJECTS_ASTEROIDS_H
#define OBJECTS_ASTEROIDS_H

#include <vector>

#include "Physics.h"

namespace Asteroids {
void Initialize();
void Update(float dt);
void Draw();
std::vector<Physics::Aabb> GetObstacleAabbs();
}  // namespace Asteroids

#endif  // OBJECTS_ASTEROIDS_H
