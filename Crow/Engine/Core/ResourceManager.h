//
// Created by Igli milaqi on 07/03/2020.
//

#ifndef CROW_RESOURCELOADER_H
#define CROW_RESOURCELOADER_H

#include <map>
#include "../Rendering/Texture.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Model.h"
#include "../Rendering/AbstractMaterial.h"

class Font;

class ResourceManager {

private:
    std::map<std::string,Texture*> m_textures;
    std::map<std::string,Shader*> m_shaders;
    std::map<std::string,Model*> m_models;
    std::map<std::string,AbstractMaterial*> m_materials;
    std::map<std::string,Font*> m_fonts;

public:
    Texture* LoadTexture(const std::string& path,const std::string& name);
    Shader* CreateShader(const std::string& vertexPath,const std::string& fragmentPath,const std::string& name);
    Model* LoadModel(const std::string& path,const std::string& name);
    Font* LoadFont(const std::string& path,const std::string& name);

    Texture* GetTexture(const std::string& name);
    Shader* GetShader(const std::string& name);
    Model* GetModel(const std::string& name);
    Font* GetFont(const std::string& name);

    template <typename T>
    T* CreateMaterial(const std::string& matName)
    {
        T* material = new T();
        m_materials[matName] = material;
        return material;
    }

    template <typename T>
    T* GetMaterial(const std::string& matName)
    {
        if(m_materials.find(matName) == m_materials.end())
        {
            ENGINE_LOG_ERROR("There is no Material with that name!");
        }

        return static_cast<T*>(m_materials[matName]);
    }
};


#endif //CROW_RESOURCELOADER_H
