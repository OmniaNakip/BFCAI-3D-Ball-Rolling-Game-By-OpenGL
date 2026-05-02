#ifndef GAME_STATE_H
#define GAME_STATE_H

namespace GameState {
enum class Screen {
  Menu,
  About,
  Playing,
  GameOver
};

void Initialize();
void StartGame();
void Update(float dt);
void Render();
void OnKeyDown(unsigned char key, int x, int y);
void OnSpecialDown(int key, int x, int y);
void OnMouse(int button, int state, int x, int y);
void OnResize(int width, int height);
Screen GetState();
void SetState(Screen state);
}  // namespace GameState

#endif  // GAME_STATE_H
