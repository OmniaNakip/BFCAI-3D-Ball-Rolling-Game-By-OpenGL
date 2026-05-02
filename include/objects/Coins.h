#ifndef OBJECTS_COINS_H
#define OBJECTS_COINS_H

namespace Coins {
void Initialize();
void Update(float dt, float currentSpeed);
void Draw();
int Collect(float cx, float cy, float cz, float radius);
}  // namespace Coins

#endif  // OBJECTS_COINS_H
