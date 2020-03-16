//
// Created by Igli milaqi on 14/03/2020.
//

#include "Transform.h"

#include "glm/gtx/vector_query.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

#include "glm/gtc/quaternion.hpp"
#include "../Debug/Debug.h"

const glm::mat4& Transform::GetLocalTransform()
{
    return m_localTransform;
}

void Transform::Translate(const glm::vec3 &translation)
{
    m_localTransform = glm::translate(m_localTransform,translation);
}

void Transform::Scale(glm::vec3 scale)
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

void Transform::SetScale(glm::vec3 scale)
{
    m_localTransform[0] = glm::normalize(m_localTransform[0]) *scale.x;
    m_localTransform[1] = glm::normalize(m_localTransform[1]) *scale.y;
    m_localTransform[2] = glm::normalize(m_localTransform[2]) *scale.z;
}

