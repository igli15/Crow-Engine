//
// Created by Igli milaqi on 07/03/2020.
//

#include "ResourceManager.h"
#include "../../Plugins/stb_image.h"
#include "../../Crow.h"
#include "AssetParser.h"

#include "../Rendering/Font.h"

void ResourceManager::AllocateResourceMemory()
{
    m_texturePool.Allocate(100);
    m_modelPool.Allocate(100);
    m_shaderPool.Allocate(20);
    m_fontPool.Allocate(20);
    m_spritePool.Allocate(100);
    m_soundPool.Allocate(20);
    m_soundBufferPool.Allocate(20);
    m_musicPool.Allocate(20);
}

ResourceManager::ResourceManager()
{
    AllocateResourceMemory();
}

Texture *ResourceManager::LoadTexture(const std::string &path, const std::string &name)
{

    auto iterator = m_textures.find(name);

    if(iterator != m_textures.end())
    {
        ENGINE_LOG_ERROR("There is already a texture with name: " + name);
        throw;
    }

    Texture *texture = &m_texturePool.GetNewData();
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load((TEXTURE_PATH + path).data(), &width, &height, &nrChannels, 0);

    if (!data)
    {
        ENGINE_LOG_ERROR("There is no texture in path: " + path);
    }

    texture->data = data;
    texture->width = width;
    texture->height = height;
    texture->nrOfChannels = nrChannels;

    if(nrChannels == 3)
    {
        texture->imageFormat = GL_RGB;
        texture->internalFormat = GL_RGB;
    } else if(nrChannels == 4)
    {
        texture->imageFormat = GL_RGBA;
        texture->internalFormat = GL_RGBA;
    }

    texture->Generate(width,height,data);

    m_textures[name] = texture;

    return texture;
}

Shader* ResourceManager::CreateShader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &name)
{
    auto iterator = m_shaders.find(name);

    if(iterator != m_shaders.end())
    {
        ENGINE_LOG_CRITICAL("There is already a shader with name: " + name);
        throw;
    }

    Shader * shader = &m_shaderPool.GetNewData();//new Shader(SHADER_PATH + vertexPath, SHADER_PATH + fragmentPath);
    shader->LoadShaderFromFile(SHADER_PATH + vertexPath, SHADER_PATH + fragmentPath);
    m_shaders[name] = shader;

    Game::Instance()->renderer->allShaders.push_back(shader);

    return shader;
}

Texture *ResourceManager::GetTexture(const std::string &name)
{
    auto iterator = m_textures.find(name);

    if (iterator == m_textures.end())
    {
        ENGINE_LOG_ERROR("There is no Texture with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

Shader *ResourceManager::GetShader(const std::string &name)
{
    auto iterator = m_shaders.find(name);

    if (iterator == m_shaders.end())
    {
        ENGINE_LOG_ERROR("There is no Shader with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

Model *ResourceManager::LoadModel(const std::string &path, const std::string &name)
{
    Model *model = &(m_modelPool.GetNewData());

    //TODO change this dont put max entities here its an overkill
    model->maxNumberOfModelInstances = MAX_ENTITIES;

    model->LoadModel((MODEL_PATH + path).data());
    model->InstanceBufferMeshes();

    auto iterator = m_models.find(name);

    if (iterator != m_models.end())
    {
        ENGINE_LOG_ERROR("There is already a model with name: " + name);
        throw;
    }
    else
    {
        m_modelIdCounter++;
        model->ID = m_modelIdCounter;
        m_models.insert(iterator,std::make_pair(name,model));
        return model;
    }

    return nullptr;
}

Model *ResourceManager::GetModel(const std::string &name) {

    auto iterator = m_models.find(name);

    if (iterator == m_models.end())
    {
        ENGINE_LOG_ERROR("There is no Model with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

Font *ResourceManager::LoadFont(const std::string &path, const std::string &name)
{
    auto iterator = m_fonts.find(name);

    if (iterator != m_fonts.end())
    {
        ENGINE_LOG_ERROR("There is already a font with name: " + name);
        throw;
    }

    Font *font = &m_fontPool.GetNewData();
    font->Load(FONT_PATH + path,48);

    m_fonts[name] = font;

    return font;
}

sf::SoundBuffer *ResourceManager::LoadSoundBuffer(const std::string& path, const std::string& name)
{
    auto iterator = m_soundBuffers.find(name);

    if (iterator != m_soundBuffers.end())
    {
        ENGINE_LOG_ERROR("There is already a soundbuffer with name: " + name);
        throw;
    }

    sf::SoundBuffer *soundBuffer = &m_soundBufferPool.GetNewData();
    new (soundBuffer) sf::SoundBuffer();
    if(!soundBuffer->loadFromFile(AUDIO_PATH + path))
    {
        ENGINE_LOG_CRITICAL("Sound buffer could not be loaded");
        throw;
    }

    m_soundBuffers[name] = soundBuffer;
    return soundBuffer;
}

sf::Sound *ResourceManager::CreateSound(const std::string& name, sf::SoundBuffer *buffer)
{
    auto iterator = m_sounds.find(name);

    if (iterator != m_sounds.end())
    {
        ENGINE_LOG_ERROR("There is already a sound with name: " + name);
        throw;
    }

    sf::Sound* sound = &m_soundPool.GetNewData();
    new (sound) sf::Sound();
    sound->setBuffer(*buffer);

    m_sounds[name] = sound;

    return sound;
}

sf::Music *ResourceManager::OpenAndCreateMusic(const std::string &path, const std::string &name)
{
    auto iterator = m_musics.find(name);

    if (iterator != m_musics.end())
    {
        ENGINE_LOG_ERROR("There is already a music with name: " + name);
        throw;
    }

    sf::Music* music = &m_musicPool.GetNewData();
    new (music) sf::Music();
    if(!music->openFromFile(AUDIO_PATH + path))
    {
        ENGINE_LOG_CRITICAL("Music could not be loaded");
        throw;
    }

    return music;
}

Font *ResourceManager::GetFont(const std::string &name) {

    auto iterator = m_fonts.find(name);
    if (iterator == m_fonts.end())
    {
        ENGINE_LOG_ERROR("There is no Font with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

const std::map<std::string, Font *> &ResourceManager::InternalGetFontMap()
{
    return m_fonts;
}

Sprite *ResourceManager::CreateSprite(const std::string &name, Texture *texture)
{
    auto iterator = m_sprites.find(name);

    if (iterator != m_sprites.end())
    {
        ENGINE_LOG_ERROR("There is already a sprite with name: " + name);
        throw;
    }

    Sprite* sprite = &m_spritePool.GetNewData();
    sprite->Buffer();

    sprite->texture = texture;
    m_spriteIdCounter++;
    sprite->ID = m_spriteIdCounter;
    m_sprites[name] = sprite;

    return sprite;
}

Sprite *ResourceManager::GetSprite(const std::string &name)
{
    auto iterator = m_sprites.find(name);

    if (iterator == m_sprites.end())
    {
        ENGINE_LOG_ERROR("There is no sprite with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

void ResourceManager::LoadAssetFromAssetsFile(const std::string& filename,size_t maxAssets)
{
    AssetCollection assetCollection = ParseAssetFile((ASSET_PATH + filename).data(),maxAssets);

    for (int i = 0; i <assetCollection.validCount; ++i)
    {
        AssetToken assetToken = assetCollection.assetTokens[i];

        if(strcmp(assetToken.assetType,"texture") == 0)
        {
            LoadTexture(assetToken.assetPath,assetToken.assetName);
        }
        else if (strcmp(assetToken.assetType,"model") == 0)
        {
            LoadModel(assetToken.assetPath,assetToken.assetName);
        }
        /*
        std::cout<<assetToken.assetType<<std::endl;
        std::cout<<assetToken.assetName<<std::endl;
        std::cout<<assetToken.assetPath<<std::endl;
         */
    }
}




