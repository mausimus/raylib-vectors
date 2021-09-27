#include "TestScreen.h"
#include "VectorBatch.h"
#include "rlgl.h"

int x  = screenWidth / 2;
int y  = screenHeight / 2;
int _x = 0;

Texture2D cloudsTexture;
Font      font;
Sound     fxOgg;

VectorObject* rect;
VectorObject* tri;
VectorObject* circ;
VectorObject* map;

TestScreen::TestScreen(int no, TestGame* game) : Screen(no, game) { }

void TestScreen::Load()
{
    cloudsTexture = LoadTexture("resources/clouds.png");
    fxOgg         = LoadSound("resources/sound.ogg");

    rect         = VectorObject::Rectangle(0.5f, 0.6f);
    tri          = VectorObject::Triangle(0.4f, 0.3f);
    circ         = VectorObject::Circle(0.1f);
    tri->_solid  = true;
    rect->_solid = false;

    map = m_game->m_assets->Map();
}

void TestScreen::Enter() { }

void TestScreen::Exit() { }

void TestScreen::Unload()
{
    UnloadTexture(cloudsTexture);
    UnloadFont(font);
}

void TestScreen::Tick(double deltaTime, double totalTime)
{
    int vx = 0;
    int vy = 0;
    if(IsKeyPressed(KEY_M))
        PlaySoundMulti(fxOgg);
    if(IsKeyDown(KEY_UP))
        vy--;
    if(IsKeyDown(KEY_DOWN))
        vy++;
    if(IsKeyDown(KEY_LEFT))
        vx--;
    if(IsKeyDown(KEY_RIGHT))
        vx++;
    x += vx;
    y += vy;

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        x = m_game->m_mouseX;
        y = m_game->m_mouseY;
    }
}

void TestScreen::DrawBackground()
{
    //DrawTexturePro(cloudsTexture, (Rectangle){0,0,cloudsTexture.width,cloudsTexture.height}, (Rectangle){0,0,screenWidth,screenHeight}, (Vector2){0,0}, 0, WHITE);
}

void TestScreen::DrawPixels(Color* framebuffer, Rectangle* rect, bool* fullFrame)
{
    /*
    *fullFrame = false;
    rect->y = 190.0f;
    rect->height = 50.0f;
    rect->x = 0.0f;
    rect->width = screenWidth;
    framebuffer[_x++] = GREEN;
    */
}

void TestScreen::DrawShapes() { }

void TestScreen::DrawVectors()
{
    auto time = (float)sin(GetTime() / 4);
    m_vectorBatch.DrawObject(rect, (Vector2) {0, 0}, time * 180, LIME);
    m_vectorBatch.DrawObject(tri, (Vector2) {-0.5f, 0}, time * 180, YELLOW);
    m_vectorBatch.DrawObject(circ, (Vector2) {0.5f, -0.5f}, 0, PINK);

    m_vectorBatch.DrawObject(map, (Vector2) {0, 0}, time * 20, RAYWHITE);

    DrawText("RAYLIB VECTORS", -1.7f, -0.8f, RAYWHITE);

    DrawText("ABCDEFGHIJKLMNOPQRSTUVXYZ0123456789.,;:!@#$%^&*()-=+_/?<>[]{}\\`", -1.0f, 0.5f, GREEN);
}
