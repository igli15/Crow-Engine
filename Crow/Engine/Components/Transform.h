//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_TRANSFORM_H
#define CROW_TRANSFORM_H

#include "glm/glm.hpp"
#include "../Feather/Types.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

class World;
struct Transform {

    friend class TransformHierarchySystem;

public:

    const glm::mat4& GetLocalTransform();
    const glm::mat4& GetWorldTransform();

    void Translate(const glm::vec3& translation);
    void Scale(const glm::vec3& scale);
    void Rotate(const glm::quat& rot);

    void SetLocalPosition(const glm::vec3& pos);
    void SetScale(const glm::vec3& scale);
    void Rotate(float angle,const glm::vec3& axis);
    glm::vec3 LocalPosition();

    //TODO Implement these
    void SetParent(Transform* transform);
    void AddChild(Entity entity);
    void RemoveChild(Entity entity);

    void DestroyAllChildrenEntities();

private:
    std::vector<Entity> m_childrens;
    glm::mat4 m_worldTransform = glm::mat4(1.0f);
    glm::mat4 m_localTransform = glm::mat4(1.0f);

    Transform* m_parentTransform = nullptr;
    World* m_contextWorld;
    Entity owner;

    //void SetWorld(World* world);
};


#endif //CROW_TRANSFORM_H
