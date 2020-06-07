//
// Created by Igli milaqi on 09/03/2020.
//

#ifndef CROW_MODEL_H
#define CROW_MODEL_H



#include "Mesh.h"

class aiNode;
class aiScene;
class aiMesh;

class Model {

public:
    bool operator==(Model& other) const
    {
        return ID == other.ID;
    }

    void Draw();

    std::vector<Mesh> m_meshes;

    std::string directory;

    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node,const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh,const aiScene* scene);

    void InstanceBufferMeshes();
    void InstanceRenderMeshes(int amount);
    void BindModelBuffer(const std::vector<glm::mat4>& models);
    int ID = -1;

    int maxNumberOfModelInstances = 10000;
};


#endif //CROW_MODEL_H
