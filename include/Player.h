#ifndef PLAYER_H
#define PLAYER_H

struct PlayerState {
  float x;
  float y;
  float z;
  float radius;
  float velocityY;
  bool grounded;
  int lane;
  float forwardRotation;  // Rotation for wheel rolling animation
};

namespace Player {
void Initialize();
void Update(float dt, float currentSpeed);
void Draw();
void MoveLeft();
void MoveRight();
void Jump();
PlayerState GetState();
}  // namespace Player

#endif  // PLAYER_H
