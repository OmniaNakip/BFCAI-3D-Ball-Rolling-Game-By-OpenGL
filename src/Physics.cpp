#include "../include/Physics.h"

namespace {
float Clamp(float value, float minValue, float maxValue) {
  if (value < minValue) {
    return minValue;
  }
  if (value > maxValue) {
    return maxValue;
  }
  return value;
}
}  // namespace

namespace Physics {
bool CheckAabbOverlap(const Aabb& a, const Aabb& b) {
  return (a.minX <= b.maxX && a.maxX >= b.minX) && (a.minY <= b.maxY && a.maxY >= b.minY) &&
         (a.minZ <= b.maxZ && a.maxZ >= b.minZ);
}

bool CheckCircleAabb(float cx, float cy, float cz, float radius, const Aabb& box) {
  const float closestX = Clamp(cx, box.minX, box.maxX);
  const float closestY = Clamp(cy, box.minY, box.maxY);
  const float closestZ = Clamp(cz, box.minZ, box.maxZ);

  const float dx = cx - closestX;
  const float dy = cy - closestY;
  const float dz = cz - closestZ;

  const float distanceSquared = (dx * dx) + (dy * dy) + (dz * dz);
  return distanceSquared <= (radius * radius);
}
}  // namespace Physics
