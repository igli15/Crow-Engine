//
// Created by Igli milaqi on 03/04/2020.
//

#ifndef CROW_FONT_H
#define CROW_FONT_H

#include "freetype2/ft2build.h"
#include FT_FREETYPE_H
#include <string>

class Font {

public:
    explicit Font(const std::string& path,unsigned int fontSize = 48);
    void SetFontSize(unsigned int newSize);
private:
    unsigned int m_fontSize = 48;
    FT_Face* m_fontFace;
};


#endif //CROW_FONT_H
