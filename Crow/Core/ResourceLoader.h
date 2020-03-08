//
// Created by Igli milaqi on 07/03/2020.
//

#ifndef CROW_RESOURCELOADER_H
#define CROW_RESOURCELOADER_H

#include <map>
#include "../Rendering/Texture.h"

class ResourceLoader {

private:
    std::map<std::string,Texture*> m_textures;

public:
    Texture& LoadTexture(const std::string& path,const std::string& name);


};


#endif //CROW_RESOURCELOADER_H
