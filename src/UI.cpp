#include "../include/UI.h"

namespace {
void DrawBitmapText(float x, float y, const char* text, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (const char* p = text; *p != '\0'; ++p) {
        glutBitmapCharacter(font, *p);
    }
}

void DrawStrokeText(float x, float y, const char* text, float scale, float thickness) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);
    glLineWidth(thickness);
    for (const char* p = text; *p != '\0'; ++p) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
    glLineWidth(1.0f);
    glPopMatrix();
}

int BitmapTextWidth(const char* text, void* font = GLUT_BITMAP_HELVETICA_18) {
    int width = 0;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(text);
    for (; *p != '\0'; ++p) {
        width += glutBitmapWidth(font, *p);
    }
    return width;
}

float StrokeTextWidth(const char* text, void* font, float scale) {
    if (!text) return 0.0f;
    return static_cast<float>(glutStrokeLength(font, reinterpret_cast<const unsigned char*>(text))) * scale;
}

float CenterX(float screenWidth, float textWidth) {
    return (screenWidth - textWidth) * 0.5f;
}

struct Rect {
    float x1, y1, x2, y2;
};

bool Contains(const Rect& rect, int x, int y) {
    return x >= rect.x1 && x <= rect.x2 && y >= rect.y1 && y <= rect.y2;
}
}

namespace UI {
void RenderMenu(int width, int height) {
    if (width <= 0 || height <= 0) return;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, static_cast<double>(width), 0.0, static_cast<double>(height));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Semi-transparent overlay background
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(width, 0);
    glVertex2f(width, height);
    glVertex2f(0, height);
    glEnd();

    // Title
    glColor3f(1.0f, 0.8f, 0.0f);
    const char* titleLeft = "START";
    const char* titleRight = "MENU";
    const float titleScale = 0.4f;
    const float titleGap = width * 0.04f;
    const float titleLeftWidth = StrokeTextWidth(titleLeft, GLUT_STROKE_ROMAN, titleScale);
    const float titleRightWidth = StrokeTextWidth(titleRight, GLUT_STROKE_ROMAN, titleScale);
    const float titleLeftX = CenterX(static_cast<float>(width), titleLeftWidth + titleGap + titleRightWidth);
    const float titleRightX = titleLeftX + titleLeftWidth + titleGap;
    DrawStrokeText(titleLeftX, height * 0.75f, titleLeft, titleScale, 3.0f);
    DrawStrokeText(titleRightX, height * 0.75f, titleRight, titleScale, 3.0f);

    // Start button (clickable text)
    const char* startText = "► START GAME";
    const float startX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(startText)));
    glColor3f(0.1f, 0.6f, 0.1f);
    DrawBitmapText(startX, height * 0.60f, startText);

    // About button (clickable text)
    const char* aboutText = "► ABOUT GAME";
    const float aboutX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(aboutText)));
    glColor3f(0.1f, 0.1f, 0.6f);
    DrawBitmapText(aboutX, height * 0.50f, aboutText);

    // Quit button (clickable text)
    const char* quitText = "► QUIT";
    const float quitX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(quitText)));
    glColor3f(0.6f, 0.1f, 0.1f);
    DrawBitmapText(quitX, height * 0.40f, quitText);

    glDisable(GL_BLEND);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void RenderAbout(int width, int height) {
    if (width <= 0 || height <= 0) return;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, static_cast<double>(width), 0.0, static_cast<double>(height));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Semi-transparent overlay background
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(width, 0);
    glVertex2f(width, height);
    glVertex2f(0, height);
    glEnd();

    // Title
    glColor3f(1.0f, 0.8f, 0.0f);
    const char* aboutLeft = "ABOUT";
    const char* aboutRight = "GAME";
    const float aboutScale = 0.4f;
    const float aboutGap = width * 0.04f;
    const float aboutLeftWidth = StrokeTextWidth(aboutLeft, GLUT_STROKE_ROMAN, aboutScale);
    const float aboutRightWidth = StrokeTextWidth(aboutRight, GLUT_STROKE_ROMAN, aboutScale);
    const float aboutLeftX = CenterX(static_cast<float>(width), aboutLeftWidth + aboutGap + aboutRightWidth);
    const float aboutRightX = aboutLeftX + aboutLeftWidth + aboutGap;
    DrawStrokeText(aboutLeftX, height * 0.85f, aboutLeft, aboutScale, 3.0f);
    DrawStrokeText(aboutRightX, height * 0.85f, aboutRight, aboutScale, 3.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    DrawBitmapText(width * 0.1f, height * 0.75f, "Hint: Avoid obstacles and survive!");
    DrawBitmapText(width * 0.1f, height * 0.70f, "Use arrow keys to move");

    DrawBitmapText(width * 0.1f, height * 0.60f, "Team Members:");
    DrawBitmapText(width * 0.1f, height * 0.54f, "Ahmed Hazem Elabady");
    DrawBitmapText(width * 0.1f, height * 0.48f, "Ahmed Badwy");
    DrawBitmapText(width * 0.1f, height * 0.42f, "Alaa Osama Mohamed Bekhit");
    DrawBitmapText(width * 0.1f, height * 0.36f, "Abanoub Rizk Gad");
    DrawBitmapText(width * 0.1f, height * 0.30f, "Abdelrahman Reda Abdelrahman Abdelstar");
    DrawBitmapText(width * 0.1f, height * 0.24f, "Omnia Mohamed Ahmed Naqeeb");

    const char* backText = "◄ BACK";
    const float backX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(backText)));
    glColor3f(0.6f, 0.1f, 0.1f);
    DrawBitmapText(backX, height * 0.10f, backText);

    glDisable(GL_BLEND);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

Action HandleMenuMouse(int button, int state, int x, int y, int width, int height) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return Action::None;
    if (width <= 0 || height <= 0) return Action::None;

    const int flippedY = height - y;

    // Approximate text click areas
    const char* startText = "► START GAME";
    const char* aboutText = "► ABOUT GAME";
    const char* quitText = "► QUIT";
    const float startX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(startText)));
    const float aboutX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(aboutText)));
    const float quitX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(quitText)));
    const float paddingX = 10.0f;
    Rect startRect = {startX - paddingX, height * 0.56f, startX + BitmapTextWidth(startText) + paddingX, height * 0.64f};
    Rect aboutRect = {aboutX - paddingX, height * 0.46f, aboutX + BitmapTextWidth(aboutText) + paddingX, height * 0.54f};
    Rect quitRect = {quitX - paddingX, height * 0.36f, quitX + BitmapTextWidth(quitText) + paddingX, height * 0.44f};

    if (Contains(startRect, x, flippedY)) return Action::Start;
    if (Contains(aboutRect, x, flippedY)) return Action::About;
    if (Contains(quitRect, x, flippedY)) return Action::Quit;

    return Action::None;
}

Action HandleAboutMouse(int button, int state, int x, int y, int width, int height) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return Action::None;
    if (width <= 0 || height <= 0) return Action::None;

    const int flippedY = height - y;

    const char* backText = "◄ BACK";
    const float backX = CenterX(static_cast<float>(width), static_cast<float>(BitmapTextWidth(backText)));
    Rect backRect = {backX - 10.0f, height * 0.06f, backX + BitmapTextWidth(backText) + 10.0f, height * 0.14f};
    if (Contains(backRect, x, flippedY)) return Action::Back;

    return Action::None;
}
}  // namespace UI
