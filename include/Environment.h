#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>

#include "Physics.h"

namespace Environment {
void Initialize();
void Update(float dt);
void Draw();
float GetCurrentSpeed();
std::vector<Physics::Aabb> GetObstacleAabbs();
int CollectCoins(float cx, float cy, float cz, float radius);
}  // namespace Environment

#endif  // ENVIRONMENT_H
