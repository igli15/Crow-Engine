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
    const glm::mat4& GetLocalTransform();
    void Translate(const glm::vec3& translation);
    void Scale(const glm::vec3& scale);
    void Rotate(const glm::quat& rot);

    void SetLocalPosition(const glm::vec3& pos);
    void SetScale(const glm::vec3& scale);
    void Rotate(float angle,const glm::vec3& axis);
    glm::vec3 LocalPosition();

private:
    glm::mat4 m_localTransform = glm::mat4(1.0f);

    glm::vec3 position = glm::vec3(0,0,0);
    glm::vec3 scale = glm::vec3(1,1,1);
    glm::quat rotation = {1, 0, 0, 0};
};


#endif //CROW_TRANSFORM_H
