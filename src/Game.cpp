#include "Game.h"
#include "Assets.h"
#include "Screen.h"

#include "TestScreen.h"

Game::Game() : m_activeScreen {nullptr}, m_frameCounter {}, m_mouseX {}, m_mouseY {} { }

void Game::Load()
{
    m_assets = new Assets();
    m_assets->Load();

    CreateScreens();

    for(auto& s : m_screens)
    {
        s->Load();
    }
}

void Game::Start()
{
    SwitchScreen(0);
}

void Game::End()
{
    if(m_activeScreen)
        m_activeScreen->Exit();

    for(auto& s : m_screens)
    {
        s->Unload();
        delete s;
    }

    m_assets->Unload();
}

void Game::Render(float thick)
{
    m_assets->Render(thick);
}

void Game::Tick(double deltaTime, double totalTime)
{
    m_frameCounter++;

    OnTick(deltaTime, totalTime);
    m_activeScreen->Tick(deltaTime, totalTime);
}

void Game::DrawBackground()
{
    m_activeScreen->DrawBackground();
}

void Game::DrawPixels(Color* framebuffer, Rectangle* rect, bool* fullFrame)
{
    m_activeScreen->DrawPixels(framebuffer, rect, fullFrame);
}

void Game::DrawShapes()
{
    m_activeScreen->DrawShapes();
}

void Game::DrawVectors(float thick)
{
    m_activeScreen->DrawVectors(thick);
}

void Game::SwitchScreen(int sc)
{
    if(m_activeScreen)
        m_activeScreen->Exit();

    OnSwitchScreen(m_activeScreen ? m_activeScreen->m_no : -1, sc);

    m_activeScreen = m_screens[sc];
    m_screenTime   = GetTime();
    m_activeScreen->Enter();
}