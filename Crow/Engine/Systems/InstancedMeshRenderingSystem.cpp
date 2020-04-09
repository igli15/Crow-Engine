//
// Created by Igli milaqi on 04/04/2020.
//

#include "InstancedMeshRenderingSystem.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void InstancedMeshRenderingSystem::OnCreate() {
    System::OnCreate();

    EventQueue::Instance().Subscribe(this, &InstancedMeshRenderingSystem::OnMeshInfoAdded);
    EventQueue::Instance().Subscribe(this, &InstancedMeshRenderingSystem::OnEntityDestroyed);
}

void InstancedMeshRenderingSystem::Render() {
    System::Render();

    auto entities = world->EntitiesWith<Transform,InstancedMeshInfo>();

    Entity cameraEntity = world->EntitiesWith<Camera>()[0];
    Transform& cameraTransform = world->GetComponent<Transform>(cameraEntity);
    Camera& camera=  world->GetComponent<Camera>(cameraEntity);

    glm::mat4 camInverseMat = glm::inverse(cameraTransform.GetWorldTransform());
    glm::mat4 projection = camera.GetProjection();
    
    for (auto pair: m_instancedModelMap)
    {
        pair.second.modelMatrices->clear();
    }

    for (int i = 0; i < entities.size() ; ++i)
    {
        InstancedMeshInfo& meshInfo = world->GetComponent<InstancedMeshInfo>(entities[i]);
        Transform& transform = world->GetComponent<Transform>(entities[i]);

        m_instancedModelMap[meshInfo.model->ID].modelMatrices->push_back(transform.GetWorldTransform());

        //Buffer the uniforms to the shader
        //The first parameter is useless here since the model mat for instanced models will be buffered after the loop

        meshInfo.material->BufferUniforms(glm::mat4(1),camInverseMat,projection,cameraTransform.WorldPosition(),world);
    }

    for (auto pair: m_instancedModelMap)
    {
        //Buffer the all model matrices VBO to the shader
        pair.second.model->BindModelBuffer(*pair.second.modelMatrices);
        //Draw in one call all the models
        pair.second.model->InstanceRenderMeshes(pair.second.modelMatrices->size());
    }

}

void InstancedMeshRenderingSystem::OnMeshInfoAdded(ComponentAddedEvent<InstancedMeshInfo> *event)
{
    event->component->model->InstanceBufferMeshes();

    int ID = event->component->model->ID;
    auto iterator = m_instancedModelMap.find(ID);

    if(iterator == m_instancedModelMap.end())
    {
        ENGINE_LOG(ID);
        InstancedModelData data {event->component->model,new std::vector<glm::mat4>()};
        m_instancedModelMap.insert(iterator,std::make_pair(ID,data));
    }
}

void InstancedMeshRenderingSystem::OnEntityDestroyed(OnEntityDestroyedEvent *event)
{

}
