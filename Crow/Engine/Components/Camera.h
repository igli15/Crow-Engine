//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_CAMERA_H
#define CROW_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/projection.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera {


public:
    const glm::mat4& GetProjection() ;

    float FOV = 60.0f;
    float aspectRatio = 4.0f/3.0f;
    float nearClipPlane = 0.1f;
    float farClipPlane = 1000.0f;

private:
    glm::mat4 m_projection;
};


#endif //CROW_CAMERA_H
