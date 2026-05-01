#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>

#include "Physics.h"

namespace Environment {
void Initialize();
void Update(float dt);
void Draw();
std::vector<Physics::Aabb> GetObstacleAabbs();
}  // namespace Environment

#endif  // ENVIRONMENT_H
