//
// Created by Igli milaqi on 03/04/2020.
//

#include "../Core/Game.h"
#include "Font.h"
#include "../Debug/Debug.h"
#include "../../Crow.h"


void Font::SetFontSize(unsigned int newSize)
{
    m_fontSize = newSize;
    FT_Set_Pixel_Sizes(*m_fontFace, 0, newSize);
}

void Font::Load(const std::string &path, unsigned int pFontSize)
{
    m_charactersMap = std::map<GLchar,Character>{};
    m_fontFace = new FT_Face();
    m_fontSize = pFontSize;
    FT_Library lib = *(Game::Instance()->ftLibrary);
    if (FT_New_Face(lib,path.data(), 0, m_fontFace))
    {
        ENGINE_LOG_ERROR("Could Not Load Font");
    }

    FT_Set_Pixel_Sizes(*m_fontFace, 0, m_fontSize);
}
