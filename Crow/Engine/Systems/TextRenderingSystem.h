//
// Created by Igli milaqi on 03/04/2020.
//

#ifndef CROW_TEXTRENDERINGSYSTEM_H
#define CROW_TEXTRENDERINGSYSTEM_H


#include <map>
#include "../Feather/System.h"
#include "glm/glm.hpp"
#include "../Rendering/Font.h"

class Text;
class Transform;
class Shader;

class TextRenderingSystem : public System {

public:
    void Init() override;
    void Render() override;

private:
    void BufferAllTextComponents();
    void RenderText(Text* text,float x, float y);
    Shader* m_shader;
    GLuint VAO, VBO;
};


#endif //CROW_TEXTRENDERINGSYSTEM_H
