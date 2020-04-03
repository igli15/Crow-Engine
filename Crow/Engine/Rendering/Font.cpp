//
// Created by Igli milaqi on 03/04/2020.
//

#include "Font.h"
#include "../Debug/Debug.h"
#include "../Core/Game.h"
#include "../../Crow.h"

Font::Font(const std::string &path, unsigned int pFontSize) : m_fontSize(pFontSize)
{
    m_fontFace = new FT_Face();
    if (FT_New_Face(*(Game::Instance()->ftLibrary),path.data(), 0, m_fontFace))
    {
        ENGINE_LOG_ERROR("Could Not Load Font");
    }

    FT_Set_Pixel_Sizes(*m_fontFace, 0, pFontSize);
}

void Font::SetFontSize(unsigned int newSize)
{
    m_fontSize = newSize;
    FT_Set_Pixel_Sizes(*m_fontFace, 0, newSize);
}
