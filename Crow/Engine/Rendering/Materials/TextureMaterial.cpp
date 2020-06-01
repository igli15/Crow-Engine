//
// Created by Igli milaqi on 14/04/2020.
//

#include "TextureMaterial.h"
#include "../../Components/Light.h"
#include "../../Components/Transform.h"
#include "../../Core/Game.h"
#include "../../Core/ResourceManager.h"

TextureMaterial::TextureMaterial() : AbstractMaterial("textureShader")
{
    Initialize();
}

void TextureMaterial::Initialize()
{

    m_resourceManager = Game::Instance()->resourceManager;

    m_whiteTexture = m_resourceManager->GetTexture("whiteTexture");
    m_blackTexture = m_resourceManager->GetTexture("blackTexture");

    m_uViewMatrix = m_shader->GetUniformLocation("view");
    m_uProjectionMatrix = m_shader->GetUniformLocation("projection");

    m_uDiffuseTexture = m_shader->GetUniformLocation("material.diffuseTexture");
    m_uSpecularTexture = m_shader->GetUniformLocation("material.specularTexture");
    m_uEmissionTexture = m_shader->GetUniformLocation("material.emissionTexture");

    m_uMainColor = m_shader->GetUniformLocation("material.mainColor");
    m_uSpecularColor = m_shader->GetUniformLocation("material.specularColor");
    m_uAmbientIntensity = m_shader->GetUniformLocation("material.ambientIntensity");
    m_uShininess = m_shader->GetUniformLocation("material.shininess");

    m_uViewPos = m_shader->GetUniformLocation("viewPos");

    m_uActiveDirLights =  m_shader->GetUniformLocation("activeDirLights");
    m_uActivePointLights =  m_shader->GetUniformLocation("activePointLights");
    m_uActiveSpotLights =  m_shader->GetUniformLocation("activeSpotLights");

    m_uEmissionScale = m_shader->GetUniformLocation("material.emissionScale");

    std::string dirUniformString;
    for (int i = 0; i < m_dirLightsUniforms.size(); ++i)
    {
        dirUniformString = "dirLights[" + std::to_string(i) + "]";

        m_dirLightsUniforms[i].m_uLightColor = m_shader->GetUniformLocation(dirUniformString +".color");
        m_dirLightsUniforms[i].m_uLightDir = m_shader->GetUniformLocation(dirUniformString + ".direction");
        m_dirLightsUniforms[i].m_uLightIntensity = m_shader->GetUniformLocation(dirUniformString + ".intensity");
    }

    std::string pointUniformString;
    for (int i = 0; i < m_pointLightsUniforms.size(); ++i)
    {
        pointUniformString = "pointLights[" + std::to_string(i) + "]";

        m_pointLightsUniforms[i].m_uLightColor = m_shader->GetUniformLocation(pointUniformString +".color");
        m_pointLightsUniforms[i].m_uLightPosition = m_shader->GetUniformLocation(pointUniformString + ".position");

        m_pointLightsUniforms[i].m_uLightConstant = m_shader->GetUniformLocation(pointUniformString + ".constant");
        m_pointLightsUniforms[i].m_uLightLinear = m_shader->GetUniformLocation(pointUniformString + ".linear");
        m_pointLightsUniforms[i].m_uLightQuadratic = m_shader->GetUniformLocation(pointUniformString + ".quadratic");

        m_pointLightsUniforms[i].m_uLightIntensity = m_shader->GetUniformLocation(pointUniformString + ".intensity");

    }

    std::string spotUniformString;
    for (int i = 0; i < m_spotLightsUniforms.size(); ++i)
    {
        spotUniformString = "spotLights[" + std::to_string(i) + "]";

        m_spotLightsUniforms[i].m_uLightColor = m_shader->GetUniformLocation(spotUniformString +".color");
        m_spotLightsUniforms[i].m_uLightPosition = m_shader->GetUniformLocation(spotUniformString + ".position");
        m_spotLightsUniforms[i].m_uLightDirection = m_shader->GetUniformLocation(spotUniformString + ".direction");

        m_spotLightsUniforms[i].m_uLightCutoff = m_shader->GetUniformLocation(spotUniformString + ".cutoff");
        m_spotLightsUniforms[i].m_uLightOuterCutoff = m_shader->GetUniformLocation(spotUniformString + ".outerCutoff");

        m_spotLightsUniforms[i].m_uLightConstant = m_shader->GetUniformLocation(spotUniformString + ".constant");
        m_spotLightsUniforms[i].m_uLightLinear = m_shader->GetUniformLocation(spotUniformString + ".linear");
        m_spotLightsUniforms[i].m_uLightQuadratic = m_shader->GetUniformLocation(spotUniformString + ".quadratic");

        m_spotLightsUniforms[i].m_uLightIntensity = m_shader->GetUniformLocation(spotUniformString + ".intensity");
    }

    m_uFogDensity = m_shader->GetUniformLocation("fogDensity");
    m_uFogGradient = m_shader->GetUniformLocation("fogGradient");
}

void TextureMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                           const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    m_shader->bufferedThisFrame = true;

    auto lightEntities = world->EntitiesWith<Light,Transform>();

    int activeDirLights = 0;
    int activePointLights = 0;
    int activeSpotLights = 0;

    for (int i = 0; i < lightEntities.size(); ++i)
    {
        auto lightComponent = world->GetComponent<Light>(lightEntities[i]);
        auto lightTransform = world->GetComponent<Transform>(lightEntities[i]);

        if(lightComponent.type == lightComponent.DIRECTIONAL)
        {
            glUniform3fv(m_dirLightsUniforms[activeDirLights].m_uLightColor, 1, glm::value_ptr(lightComponent.color));
            glUniform3fv(m_dirLightsUniforms[activeDirLights].m_uLightDir, 1, glm::value_ptr(lightTransform.GetWorldTransform()[2]));

            glUniform1f(m_dirLightsUniforms[activeDirLights].m_uLightIntensity,lightComponent.intensity);

            activeDirLights +=1;
        }
        else if(lightComponent.type == lightComponent.POINT)
        {

            glUniform3fv(m_pointLightsUniforms[activePointLights].m_uLightColor, 1, glm::value_ptr(lightComponent.color));

            glUniform3fv(m_pointLightsUniforms[activePointLights].m_uLightPosition, 1, glm::value_ptr(lightTransform.WorldPosition()));

            glUniform1f(m_pointLightsUniforms[activePointLights].m_uLightConstant,lightComponent.constant);
            glUniform1f(m_pointLightsUniforms[activePointLights].m_uLightLinear,lightComponent.linear);
            glUniform1f(m_pointLightsUniforms[activePointLights].m_uLightQuadratic,lightComponent.quadratic);

            glUniform1f(m_pointLightsUniforms[activePointLights].m_uLightIntensity,lightComponent.intensity);

            activePointLights +=1;
        }
        else if(lightComponent.type == lightComponent.SPOT)
        {

            glUniform3fv(m_spotLightsUniforms[activeSpotLights].m_uLightColor, 1, glm::value_ptr(lightComponent.color));
            glUniform3fv(m_spotLightsUniforms[activeSpotLights].m_uLightDirection, 1, glm::value_ptr(lightTransform.GetWorldTransform()[2]));
            glUniform3fv(m_spotLightsUniforms[activeSpotLights].m_uLightPosition, 1, glm::value_ptr(lightTransform.WorldPosition()));

            glUniform1f(m_spotLightsUniforms[activeSpotLights].m_uLightCutoff,lightComponent.cutoff);
            glUniform1f(m_spotLightsUniforms[activeSpotLights].m_uLightOuterCutoff,lightComponent.outerCutoff);

            glUniform1f(m_spotLightsUniforms[activeSpotLights].m_uLightConstant,lightComponent.constant);
            glUniform1f(m_spotLightsUniforms[activeSpotLights].m_uLightLinear,lightComponent.linear);
            glUniform1f(m_spotLightsUniforms[activeSpotLights].m_uLightQuadratic,lightComponent.quadratic);

            glUniform1f(m_spotLightsUniforms[activeSpotLights].m_uLightIntensity,lightComponent.intensity);

            activeSpotLights +=1;
        }
    }

    glUniform1i(m_uActiveDirLights,activeDirLights);
    glUniform1i(m_uActivePointLights,activePointLights);
    glUniform1i(m_uActiveSpotLights,activeSpotLights);

    glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
    glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));

    glUniform3fv(m_uViewPos,1,glm::value_ptr(viewPos));

    glUniform1f(m_uFogDensity,Game::Instance()->fogData.fogDensity);
    glUniform1f(m_uFogGradient,Game::Instance()->fogData.fogGradient);
}

void TextureMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    if(diffuseTexture != nullptr)
    {
        glActiveTexture(GL_TEXTURE0);
        //bind the texture to the current active slot
        glBindTexture(GL_TEXTURE_2D, diffuseTexture->ID);
        //tell the shader the texture slot for the diffuse texture is slot 0
        glUniform1i(m_uDiffuseTexture, 0);
    }
    else
    {
        glActiveTexture(GL_TEXTURE0);
        //bind the texture to the current active slot
        glBindTexture(GL_TEXTURE_2D, m_whiteTexture->ID);
        glUniform1i(m_uDiffuseTexture, 0);
    }

    if(specularTexture != nullptr)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularTexture->ID);
        glUniform1i(m_uSpecularTexture, 1);
    }
    else
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_blackTexture->ID);
        glUniform1i(m_uSpecularTexture, 1);
    }

    if(emissionTexture != nullptr)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, emissionTexture->ID);
        glUniform1i(m_uEmissionTexture, 2);
    }
    else
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_blackTexture->ID);
        glUniform1i(m_uEmissionTexture, 2);
    }


    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));
    glUniform3fv(m_uSpecularColor,1,glm::value_ptr(specularColor));
    glUniform1f(m_uAmbientIntensity,ambientIntensity);
    glUniform1f(m_uShininess,shininess);
    glUniform1f(m_uEmissionScale,emissionScale);

    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));
}
