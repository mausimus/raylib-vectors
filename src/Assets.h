#pragma once

#include "stdafx.h"
#include "VectorBatch.h"

constexpr float CHAR_SCALE = 0.0025f;
constexpr int CHAR_RAW_MIDPOINT = 9;
constexpr float CHAR_KERNING = 0.01f;
constexpr float CHAR_MIDPOINT = CHAR_RAW_MIDPOINT * CHAR_KERNING;

class Assets
{
public:
    VectorObject* GetChar(char c);
    VectorObject* Map();

    Assets();
    void Load();
    void Unload();

private:
    void GenerateChars();
    void AddChar(char c, VectorObject* vo);

    std::map<char, VectorObject*> _chars;
};
