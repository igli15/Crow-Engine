//
// Created by Igli milaqi on 14/03/2020.
//

#include "Transform.h"

#include "glm/gtx/vector_query.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

#include "glm/gtc/quaternion.hpp"
#include "../Debug/Debug.h"
#include "../Feather/World.h"


const glm::mat4& Transform::GetLocalTransform()
{

    if(m_isLocalDirty)
    {
        m_localTransform = glm::translate(glm::mat4(1.0f),m_localPosition) * glm::toMat4(m_localRotation)
                           * glm::scale(glm::mat4(1.0f),m_localScale);

        m_isLocalDirty = false;
    }
    return m_localTransform;
}

void Transform::Translate(const glm::vec3 &translation)
{
    //m_localTransform = glm::translate(m_localTransform,translation);
    m_localPosition += translation;
    MarkLocalTransformDirty();
}

void Transform::Scale(const glm::vec3& scale)
{
    //m_localTransform = glm::scale(m_localTransform,scale);
    m_localScale *= scale;
    MarkLocalTransformDirty();
}

void Transform::Rotate(const glm::quat &rot)
{
    //m_localTransform *= glm::toMat4(rot);
    m_localRotation = rot * m_localRotation;
    MarkLocalTransformDirty();
}

void Transform::SetLocalPosition(const glm::vec3 &pos)
{
    //m_localTransform[3] = glm::vec4(pos, 1);
    m_localPosition = pos;
    MarkLocalTransformDirty();
}

void Transform::SetLocalScale(const glm::vec3& scale)
{
    m_localScale = scale;
    MarkLocalTransformDirty();
}

void Transform::SetLocalRotation(const glm::quat &rotation)
{
    m_localRotation = rotation;
    MarkLocalTransformDirty();
}

void Transform::Rotate(float angle, const glm::vec3 &axis)
{
    Rotate(glm::angleAxis(glm::radians(angle), glm::normalize(axis)));
    // m_localTransform = glm::rotate(m_localTransform,glm::radians(angle),axis);
}

glm::vec3 Transform::LocalPosition()
{
    return glm::vec3(m_localTransform[3]);
}

const glm::mat4 &Transform::GetWorldTransform()
{
    if(m_isWorldDirty)
    {
        if (parentEntity == InvalidEntity)
        {
            m_worldTransform = GetLocalTransform();
        } else
        {
            Transform& t = m_contextWorld->GetComponent<Transform>(parentEntity);
            m_worldTransform = t.GetWorldTransform() * GetLocalTransform();
        }

        m_isWorldDirty = false;
    }

    return m_worldTransform;
}

void Transform::SetParent(Entity newParentEntity)
{
    if(parentEntity != InvalidEntity)
    {
        Transform& t = m_contextWorld->GetComponent<Transform>(parentEntity);
        t.m_childrens.erase(std::find(m_childrens.begin(),m_childrens.end(),owner));
    }

    parentEntity = newParentEntity;

    if(newParentEntity != InvalidEntity)
    {
        Transform& t = m_contextWorld->GetComponent<Transform>(newParentEntity);
        t.m_childrens.push_back(this->owner);
    }
}

void Transform::DestroyAllChildrenEntities()
{
    for (int i = 0; i < m_childrens.size(); ++i)
    {
        m_contextWorld->InternalDestroyEntity(m_childrens[i]);
    }
}

int Transform::GetChildCount()
{
    return m_childrens.size();
}

glm::vec3 Transform::WorldPosition()
{
    return glm::vec3(GetWorldTransform()[3]);
}

void Transform::MarkLocalTransformDirty()
{
    m_isLocalDirty = true;

    MarkWorldTransformDirty();
}

void Transform::MarkWorldTransformDirty()
{
    m_isWorldDirty = true;

    for (int i = 0; i < m_childrens.size(); ++i)
    {
        Transform& transform = m_contextWorld->GetComponent<Transform>(m_childrens[i]);
        transform.MarkWorldTransformDirty();
    }
}

