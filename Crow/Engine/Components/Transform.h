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

    ///Returns the local transformation matrix
    const glm::mat4& GetLocalTransform();

    ///Returns the world transformation matrix
    const glm::mat4& GetWorldTransform();

    ///Translate the transform locally
    ///@param translation translation vector3
    void Translate(const glm::vec3& translation);

    ///Scale the transform locally
    ///@param scale scale vector3
    void Scale(const glm::vec3& scale);

    ///Rotate the transform locally
    ///@param rots rotation quaternion
    void Rotate(const glm::quat& rot);

    void SetLocalPosition(const glm::vec3& pos);
    void SetLocalScale(const glm::vec3& scale);
    void SetLocalRotation(const glm::quat& rotation);

    //void SetWorldPosition(const glm::vec3& pos);

    ///Rotate around an axis by an angle
    ///@param angle the angle in degrees
    ///@param axis vector3 specifing the axis of rotation
    void Rotate(float angle,const glm::vec3& axis);


    inline const glm::quat& getLocalRotation() const {return m_localRotation;}

    inline const glm::vec3& LocalPosition() {return  m_localPosition;};
    glm::vec3 WorldPosition();

    void SetParent(Entity newParentEntity);

    const std::vector<Entity>& GetChildren();
    Entity GetChildAt(int index);
    int GetChildCount();

    ///Marks all the children entities attached to the transform for destruction.
    void DestroyAllChildrenEntities();

    Entity owner = InvalidEntity;

private:

    std::vector<Entity> m_childrens;
    glm::mat4 m_worldTransform = glm::mat4(1.0f);
    glm::mat4 m_localTransform = glm::mat4(1.0f);

    glm::vec3 m_localPosition {0,0,0};
    glm::quat m_localRotation  {1,0,0,0};
    glm::vec3 m_localScale {1,1,1};


    //Transform* m_parentTransform = nullptr;
    World* m_contextWorld;
    Entity parentEntity = InvalidEntity;

    void MarkLocalTransformDirty();
    void MarkWorldTransformDirty();

    bool m_isLocalDirty = true;
    bool m_isWorldDirty = true;

    //void SetWorld(World* world);
};


#endif //CROW_TRANSFORM_H
