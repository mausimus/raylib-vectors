#pragma once

#include "stdafx.h"

#if defined(PLATFORM_WEB)
    constexpr int   screenWidth  = 1856;
    constexpr int   screenHeight = 1044;
#else
    constexpr int   screenWidth  = 1920;
    constexpr int   screenHeight = 1080;
#endif

constexpr int   aspectH = 16;
constexpr int   aspectV = 9;
constexpr int   screenSize = screenWidth * screenHeight;

#define WINDOW_TITLE "game"
#define FULLSCREEN_KEY KEY_F
#define GLOW
#define TARGET_FPS 60

#define DRAW_PIXELS
#define DRAW_SHAPES
#define DRAW_BACKGROUND

class Screen;
class Assets;

class Game
{
protected:
    std::vector<Screen*> m_screens;
    Screen* m_activeScreen;

    void LoadScreens();

    virtual void CreateScreens() = 0;
    virtual void OnTick(double deltaTime, double totalTime) = 0;
    virtual void OnSwitchScreen(int prevScreen, int nextScreen) = 0;

public:

    Assets* m_assets;

    int m_frameCounter;
    float m_mouseX;
    float m_mouseY;
    double m_screenTime;

    Game();

    void Start();
    void Tick(double deltaTime, double totalTime);
    void DrawBackground();
    void DrawPixels(Color* framebuffer, Rectangle *rect, bool* fullFrame);
    void DrawShapes();
    void DrawVectors(float thick);
    void End();

    void SwitchScreen(int sn);
};
