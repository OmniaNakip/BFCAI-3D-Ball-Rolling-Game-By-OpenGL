#ifndef UI_H
#define UI_H

#include <GL/glut.h>

namespace UI {
enum class Action {
    None,
    Start,
    About,
    Back,
    Quit
};

void RenderMenu(int width, int height);
void RenderAbout(int width, int height);

Action HandleMenuMouse(int button, int state, int x, int y, int width, int height);
Action HandleAboutMouse(int button, int state, int x, int y, int width, int height);
}  // namespace UI

#endif  // UI_H