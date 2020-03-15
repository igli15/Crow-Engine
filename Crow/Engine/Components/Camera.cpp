//
// Created by Igli milaqi on 14/03/2020.
//


#include "Camera.h"

const glm::mat4 &Camera::GetProjection()
{
    m_projection = glm::perspective(glm::radians(FOV),aspectRatio, nearClipPlane, farClipPlane);
    return m_projection;
}
