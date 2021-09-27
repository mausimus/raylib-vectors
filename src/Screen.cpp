#include "Screen.h"

Screen::Screen(int no, TestGame* game) : m_game {game}, m_no {no}
{
    m_mouseCursor.AddLine(-0.015f, -0.015f, 0.015f, 0.015f);
    m_mouseCursor.AddLine(-0.015f, 0.015f, 0.015f, -0.015f);
}

Screen::~Screen() { }

void Screen::DrawVectors(float thick)
{
    m_vectorBatch.Thick(thick);
    m_vectorBatch.Begin();

    DrawVectors();

    m_vectorBatch.DrawObject(&m_mouseCursor, (Vector2){m_game->m_mouseX, m_game->m_mouseY}, 0, WHITE);
    m_vectorBatch.End();
}

void Screen::DrawText(const std::string& text, float x, float y, Color c)
{
    for(auto ch : text)
    {
        auto vo = m_game->m_assets->GetChar(ch);
        m_vectorBatch.DrawObject(vo, (Vector2) {x + (vo->_width / 2), y + CHAR_MIDPOINT}, 0.0f, c);
        x += vo->_width + CHAR_KERNING;
    }
}