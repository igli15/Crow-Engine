//
// Created by Igli milaqi on 07/03/2020.
//

#ifndef CROW_RESOURCELOADER_H
#define CROW_RESOURCELOADER_H

#include <map>
#include "../Rendering/Texture.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Model.h"

class ResourceManager {

private:
    std::map<std::string,Texture*> m_textures;
    std::map<std::string,Shader*> m_shaders;
    std::map<std::string,Model*> m_models;

public:
    Texture* LoadTexture(const std::string& path,const std::string& name);
    Shader* CreateShader(const std::string& vertexPath,const std::string& fragmentPath,const std::string& name);
    Model* LoadModel(const std::string& path,const std::string& name);

    Texture* GetTexture(const std::string& name);
    Shader* GetShader(const std::string& name);
    Model* GetModel(const std::string& name);
};


#endif //CROW_RESOURCELOADER_H
