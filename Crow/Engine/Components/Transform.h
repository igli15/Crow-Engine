//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_TRANSFORM_H
#define CROW_TRANSFORM_H

#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform {

public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;

    const glm::mat4& GetLocalTransform() const;

private:
    glm::mat4 m_localTransform;
};


#endif //CROW_TRANSFORM_H
