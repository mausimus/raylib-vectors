#include "Screen.h"

Screen::Screen(int no, TestGame* game) : m_game {game}, m_no {no}
{
    m_mouseCursor.AddLine(-0.15f, -0.15f, 0.15f, 0.15f);
    m_mouseCursor.AddLine(-0.15f, 0.15f, 0.15f, -0.15f);
}

Screen::~Screen() { }

void Screen::DrawVectors(float thick)
{
    m_vectorBatch.Thick(thick);
    m_vectorBatch.Begin();

    DrawVectors();

    m_vectorBatch.DrawObject(&m_mouseCursor, (Vector2) {m_game->m_mouseX, m_game->m_mouseY}, 0, WHITE);
    m_vectorBatch.End();
}

// hAlign/vAlign state which corner (x,y) represent: (-1,-1) = top/left, (1,1) = bottom/right
void Screen::DrawText(const std::string& text, float x, float y, Color c, int hAlign, int vAlign)
{
    if(hAlign == 0 || hAlign == 1)
    {
        float tw = 0;
        for(auto ch : text)
        {
            auto vo = m_game->m_assets->GetChar(ch);
            tw += vo->_width + CHAR_KERNING;
        }
        tw -= CHAR_KERNING; // last char
        if(hAlign == 0)
            x -= tw / 2;
        else
            x -= tw;
    }

    if(vAlign == -1)
        y += CHAR_HEIGHT / 2;
    else if(vAlign == 1)
        y -= CHAR_HEIGHT / 2;

    for(auto ch : text)
    {
        auto vo = m_game->m_assets->GetChar(ch);
        m_vectorBatch.DrawObject(vo, (Vector2) {x + (vo->_width / 2), y + CHAR_HEIGHT / 2}, 0.0f, c);
        x += vo->_width + CHAR_KERNING;
    }
}