#include <cstdlib>  
#include <GL/glut.h>
#include <cstdio>
#include <vector>
#include <cstring>

#include "../include/Camera.h"
#include "../include/Constants.h"
#include "../include/Environment.h"
#include "../include/GameState.h"
#include "../include/Graphics.h"
#include "../include/Physics.h"
#include "../include/Player.h"

namespace {
    GameState::Screen g_screen = GameState::Screen::Menu;
    int g_windowWidth = Constants::kWindowWidth;
    int g_windowHeight = Constants::kWindowHeight;
    float g_scoreSeconds = 0.0f;
    int g_coinCount = 0;

    void ResetRun() {
        Player::Initialize();
        Environment::Initialize();
        g_scoreSeconds = 0.0f;
        g_coinCount = 0;
    }

    void DrawBitmapText(float x, float y, const char* text, void* font) {
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

    void RenderHud() {
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, g_windowWidth, 0.0, g_windowHeight);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glColor3f(1.0f, 1.0f, 1.0f);
        char scoreLine[64];
        char coinLine[64];
        std::snprintf(scoreLine, sizeof(scoreLine), "Score: %.1f", g_scoreSeconds);
        std::snprintf(coinLine, sizeof(coinLine), "Coins: %d", g_coinCount);
        DrawBitmapText(15.0f, g_windowHeight - 35.0f, scoreLine, GLUT_BITMAP_HELVETICA_18);
        DrawBitmapText(15.0f, g_windowHeight - 65.0f, coinLine, GLUT_BITMAP_HELVETICA_18);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }

    void RenderOverlay(const char* part1, const char* part2, const char* line1, const char* line2, const char* line3) {
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, g_windowWidth, 0.0, g_windowHeight);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(g_windowWidth, 0);
        glVertex2f(g_windowWidth, g_windowHeight);
        glVertex2f(0, g_windowHeight);
        glEnd();

        if (part1 != nullptr && part2 != nullptr) {
            glColor3f(1.0f, 1.0f, 0.0f);
            float scale = 0.45f;
            float thickness = 4.0f;
            float totalWidth = 400.0f;
            float startX = (g_windowWidth - totalWidth) / 2.0f;
            float headerY = g_windowHeight * 0.75f;
            DrawStrokeText(startX, headerY, part1, scale, thickness);
            DrawStrokeText(startX + 220.0f, headerY, part2, scale, thickness);
        }

        auto drawCenteredBitmap = [&](float y, const char* text, void* font, float r, float g, float b) {
            if (text == nullptr) return;
            glColor3f(r, g, b);
            int textWidth = glutBitmapLength(font, (const unsigned char*)text);
            float x = (g_windowWidth - (float)textWidth) / 2.0f;
            DrawBitmapText(x, y, text, font);
        };

        const float centerY = g_windowHeight * 0.5f;
        drawCenteredBitmap(centerY, line1, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 1.0f, 1.0f);
        drawCenteredBitmap(centerY - 50.0f, line2, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 1.0f, 1.0f);
        drawCenteredBitmap(centerY - 100.0f, line3, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 1.0f, 1.0f);

        glDisable(GL_BLEND);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }

    void RenderScene3d() {
        const PlayerState player = Player::GetState();
        Camera::Apply(g_windowWidth, g_windowHeight, player.x, player.y, player.z);
        Environment::Draw();
        Player::Draw();
    }

    void UpdateGameplay(float dt) {
        Player::Update(dt);
        Environment::Update(dt);

        if (g_screen == GameState::Screen::Playing) {
            g_scoreSeconds += dt;
            const PlayerState player = Player::GetState();
            g_coinCount += Environment::CollectCoins(player.x, player.y, player.z, player.radius);

            const std::vector<Physics::Aabb> obstacles = Environment::GetObstacleAabbs();
            for (const Physics::Aabb& box : obstacles) {
                if (Physics::CheckCircleAabb(player.x, player.y, player.z, player.radius, box)) {
                    g_screen = GameState::Screen::GameOver;
                    break;
                }
            }
        }
    }
}

namespace GameState {
    void Initialize() {
        Graphics::SetupLighting();
        ResetRun();
        g_screen = Screen::Menu;
    }

    void Update(float dt) {
        if (g_screen == Screen::Menu || g_screen == Screen::Playing) {
            UpdateGameplay(dt);
        }
    }

    void Render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (g_screen != Screen::Playing) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            for (int i = 0; i < 8; i++) {
                glPushMatrix();
                float scale = 1.0f + (i * 0.006f);
                glScalef(scale, scale, 1.0f);
                glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
                RenderScene3d();
                glPopMatrix();
            }
            glDisable(GL_BLEND);
        }
        else {
            RenderScene3d();
            RenderHud();
        }

        if (g_screen == Screen::Menu) {
            RenderOverlay("START", "MENU", "Endless Runner 3D", "Press Enter to Start", nullptr);
        }
        else if (g_screen == Screen::GameOver) {
            char scoreLine[64];
            std::snprintf(scoreLine, sizeof(scoreLine), "Score: %.1f  Coins: %d", g_scoreSeconds, g_coinCount);
            RenderOverlay("GAME", "OVER", "Final Results:", scoreLine, "Press R to Restart");
        }

        glutSwapBuffers();
    }

    void OnKeyDown(unsigned char key, int, int) {
        if (key == 27) std::exit(0);
        if (g_screen == Screen::Menu && key == 13) {
            ResetRun();
            g_screen = Screen::Playing;
            return;
        }
        if (g_screen == Screen::GameOver && (key == 'r' || key == 'R')) {
            ResetRun();
            g_screen = Screen::Playing;
            return;
        }
        if (g_screen != Screen::Playing) return;
        if (key == 'a' || key == 'A') Player::MoveLeft();
        else if (key == 'd' || key == 'D') Player::MoveRight();
        else if (key == ' ') Player::Jump();
    }

    void OnSpecialDown(int key, int, int) {
        if (g_screen != Screen::Playing) return;
        if (key == GLUT_KEY_LEFT) Player::MoveLeft();
        else if (key == GLUT_KEY_RIGHT) Player::MoveRight();
        else if (key == GLUT_KEY_UP) Player::Jump();
    }

    void OnResize(int width, int height) {
        if (height == 0) height = 1;
        g_windowWidth = width;
        g_windowHeight = height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
    }

    Screen GetState() { return g_screen; }
    void SetState(Screen state) { g_screen = state; }
}