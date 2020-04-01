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
    return m_localTransform;
}

void Transform::Translate(const glm::vec3 &translation)
{
    m_localTransform = glm::translate(m_localTransform,translation);
}

void Transform::Scale(const glm::vec3& scale)
{
    m_localTransform = glm::scale(m_localTransform,scale);
}

void Transform::Rotate(const glm::quat &rot)
{
    m_localTransform *= glm::toMat4(rot);
}

void Transform::SetLocalPosition(const glm::vec3 &pos)
{
    m_localTransform[3] = glm::vec4(pos, 1);
}

void Transform::SetScale(const glm::vec3& scale)
{
    m_localTransform[0] = glm::normalize(m_localTransform[0]) *scale.x;
    m_localTransform[1] = glm::normalize(m_localTransform[1]) *scale.y;
    m_localTransform[2] = glm::normalize(m_localTransform[2]) *scale.z;
}

void Transform::Rotate(float angle, const glm::vec3 &axis)
{
    m_localTransform = glm::rotate(m_localTransform,glm::radians(angle),axis);
}

glm::vec3 Transform::LocalPosition()
{
    return glm::vec3(m_localTransform[3]);
}

const glm::mat4 &Transform::GetWorldTransform()
{
    if(m_parentTransform == nullptr) return m_localTransform;

    m_worldTransform = m_parentTransform->GetWorldTransform() * m_localTransform;

    return m_worldTransform;
}

void Transform::SetParent(Transform *transform)
{
    if(m_parentTransform != nullptr)
    {
        m_parentTransform->m_childrens.erase(std::find(m_childrens.begin(),m_childrens.end(),owner));
    }

    m_parentTransform = transform;

    if(transform!= nullptr) {

        transform->m_childrens.push_back(this->owner);
    }
}

void Transform::DestroyAllChildrenEntities() 
{
    for (int i = 0; i < m_childrens.size(); ++i)
    {
        m_contextWorld->DestroyEntity(m_childrens[i]);
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


