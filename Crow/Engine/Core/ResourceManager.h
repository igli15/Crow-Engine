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
#include "../Feather/Pool.h"

#include "Game.h"
#include "Renderer.h"
#include "../Rendering/Font.h"
#include "../Rendering/Sprite.h"
#include "SFML/Audio.hpp"

///ResourceManager class is used to Load and Get all the assets.
///This class is a singleton and can be accessed only through the game class instance.
///The asset path should be relative meaning, each assets Has it's own folder directory. When loading an assets user should provide only the relative path from the folder.
///e.g if a Texture is to be loaded, instead of writing path like "Crow/Textures/Texture.png" you should just write "Texture.png" and place the asset in the texture folder.
class ResourceManager {

private:
    std::map<std::string,Texture*> m_textures;
    std::map<std::string,Shader*> m_shaders;
    std::map<std::string,Model*> m_models;
    std::map<std::string,AbstractMaterial*> m_materials;
    std::map<std::string,Font*> m_fonts;
    std::map<std::string,Sprite*> m_sprites;
    std::map<std::string,sf::Sound*> m_sounds;
    std::map<std::string,sf::SoundBuffer*> m_soundBuffers;

    Pool<Texture> m_texturePool;
    Pool<Shader> m_shaderPool;
    Pool<Model> m_modelPool;
    Pool<Font> m_fontPool;
    Pool<Sprite> m_spritePool;
    Pool<sf::SoundBuffer> m_soundBufferPool;
    Pool<sf::Sound> m_soundPool;

    int m_modelIdCounter = 0;
    int m_spriteIdCounter = 0;
    int m_materialIdCounter = 0;

public:

    ResourceManager();
    void AllocateResourceMemory();

    ///Loads a texture.
    ///@param path  texture's relative path.
    ///@param name the unique name which will be assigned to the texture.
    ///@return a ptr to the just loaded texture.
    Texture* LoadTexture(const std::string& path,const std::string& name);

    ///Creates a shader asset by compiling both vertex and fragment shader files.
    ///@param vertexPath  vertex shader's relative path.
    ///@param fragmentPath  fragment shader's relative path.
    ///@param name the unique name which will be assigned to the shader.
    ///@return a ptr to the just created shader.
    Shader* CreateShader(const std::string& vertexPath,const std::string& fragmentPath,const std::string& name);

    ///Loads a Model.
    ///@param path  models's relative path
    ///@param name the unique name which will be assigned to the model.
    ///@return a ptr to the just loaded model.
    Model* LoadModel(const std::string& path,const std::string& name);

    ///Loads a Font.
    ///@param path  font's relative path.
    ///@param name the unique name which will be assigned to this font.
    ///@return a ptr to the just loaded font.
    Font* LoadFont(const std::string& path,const std::string& name);

    sf::SoundBuffer* LoadSoundBuffer(const std::string path,const std::string name);
    sf::Sound* CreateSound(const std::string name,sf::SoundBuffer* buffer);

    ///Creates a sprite asset.
    ///@param name the unique name which will be assigned to the sprite.
    ///@param texture a ptr to the texture that will be used for the sprite.
    ///@return a ptr to the just created sprite.
    Sprite* CreateSprite(const std::string& name,Texture* texture);

    ///Get a Texture asset with a name.
    ///@param name the name of the texture.
    ///@return a ptr to the the texture assets. It will return nullptr if no texture with that name was found.
    Texture* GetTexture(const std::string& name);

    ///Get a Shader asset with a name.
    ///@param name the name of the Shader.
    ///@return a ptr to the the Shader assets. It will return nullptr if no Shader with that name was found.
    Shader* GetShader(const std::string& name);

    ///Get a Texture asset with a name.
    ///@param name the name of the texture.
    ///@return a ptr to the the texture assets. It will return nullptr if no texture with that name was found.
    Model* GetModel(const std::string& name);

    ///Get a Font asset with a name.
    ///@param name the name of the Font.
    ///@return a ptr to the the Font assets. It will return nullptr if no Font with that name was found.
    Font* GetFont(const std::string& name);

    ///Get a Sprite asset with a name.
    ///@param name the name of the Sprite.
    ///@return a ptr to the the Sprite assets. It will return nullptr if no Sprite with that name was found.
    Sprite* GetSprite(const std::string& name);


    ///Creates a material asset of a specific material type "T".
    ///@param matName the unique name which will be assigned to the material.
    ///@return a ptr to the just created material.
    template <typename T>
    T* CreateMaterial(const std::string& matName)
    {
        auto iterator = m_materials.find(matName);

        if(iterator != m_materials.end())
        {
            ENGINE_LOG_ERROR("There is already a material with name: " + matName);
            throw;
        }

        T* material = new T();

        material->name = matName;
        material->ID = ++m_materialIdCounter;

        m_materials[matName] = material;

        Game::Instance()->renderer->allMaterials.push_back(material);
        Game::Instance()->renderer->materialMap[material->ID] = material;

        return material;
    }

    ///Get a Material asset of a specified type "T" with a name.
    ///@param matName the name of the Material.
    ///@return a ptr to the the Material assets. It will return nullptr if no Material with that name was found.
    template <typename T>
    T* GetMaterial(const std::string& matName)
    {
        if(m_materials.find(matName) == m_materials.end())
        {
            ENGINE_LOG_WARNING("There is no Material with name: " + matName);
            return  nullptr;
        }

        return static_cast<T*>(m_materials[matName]);
    }

    ///Get the font map.
    ///Used internally by the font rendering system.
    const std::map<std::string,Font*>& InternalGetFontMap();

    void LoadAssetFromAssetsFile(const std::string& filename,size_t maxNrOfAssets = 100);
};


#endif //CROW_RESOURCELOADER_H
