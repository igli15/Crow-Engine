//
// Created by Igli milaqi on 14/03/2020.
//

#include "Transform.h"

#include "glm/gtx/vector_query.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

#include "glm/gtc/quaternion.hpp"

const glm::mat4& Transform::GetLocalTransform() const
{
    glm::translate(m_localTransform,position);
    m_localTransform * glm::toMat4(rotation);
    glm::scale(m_localTransform,scale);
    return m_localTransform;
}
