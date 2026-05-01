#ifndef PHYSICS_H
#define PHYSICS_H

namespace Physics {
struct Aabb {
  float minX;
  float minY;
  float minZ;
  float maxX;
  float maxY;
  float maxZ;
};

bool CheckAabbOverlap(const Aabb& a, const Aabb& b);
bool CheckCircleAabb(float cx, float cy, float cz, float radius, const Aabb& box);
}  // namespace Physics

#endif  // PHYSICS_H
