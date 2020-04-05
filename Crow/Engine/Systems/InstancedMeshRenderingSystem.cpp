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


    /*
    //TODO maybe render normally just find away to change the vbo here and draw instance arrays!

    auto entities = world->EntitiesWith<Transform,InstancedMeshInfo>();

    Entity cameraEntity = world->EntitiesWith<Camera>()[0];
    Transform& cameraTransform = world->GetComponent<Transform>(cameraEntity);
    Camera& camera=  world->GetComponent<Camera>(cameraEntity);

    glm::mat4 camInverseMat = glm::inverse(cameraTransform.GetWorldTransform());

    m_modelMap.clear();

    for (int i = 0; i < entities.size() ; ++i)
    {
        InstancedMeshInfo& meshInfo = world->GetComponent<InstancedMeshInfo>(entities[i]);
        Transform& transform = world->GetComponent<Transform>(entities[i]);

        m_modelMap[meshInfo.model->ID].push_back(transform.GetWorldTransform());
    }


    for (int i = 0; i < entities.size() ; ++i)
    {

        InstancedMeshInfo& meshInfo = world->GetComponent<InstancedMeshInfo>(entities[i]);


        if(glCheckError() != 0) throw;
        //ENGINE_LOG(m_modelMap[meshInfo.model->ID].size());
        meshInfo.model->BindModelBuffer(m_modelMap[meshInfo.model->ID]);
        meshInfo.material->RenderInstanced(meshInfo.model,(int)m_modelMap[meshInfo.model->ID].size(),camInverseMat,camera.GetProjection()
                ,cameraTransform.WorldPosition(),world);
    }

    InstancedMeshInfo& meshInfo = world->GetComponent<InstancedMeshInfo>(entities[0]);
    if(glCheckError() != 0) throw;
    meshInfo.model->InstanceRenderMeshes(10000);
    if(glCheckError() != 0) throw;

     */
}

void InstancedMeshRenderingSystem::OnMeshInfoAdded(ComponentAddedEvent<InstancedMeshInfo> *event)
{
    event->component->model->InstanceBufferMeshes();
}

void InstancedMeshRenderingSystem::OnEntityDestroyed(OnEntityDestroyedEvent *event)
{

}
