#pragma once
#include <vector>
#include "DirectionalLight.h"
#include "FlashLight.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>


#define LM LightManager::GetInstance()



class LightManager
{
public:
    static LightManager* GetInstance()
    {
        static LightManager instance;
        return &instance;
    }

	std::vector<DirectionalLight*> directionals;
	std::vector<FlashLight*> flashLight;

    void AddDirectionalLight(DirectionalLight* dl);
    void AddFlashLight(FlashLight* fl);
    void ApplyLightsRender(GLuint shaderToPass);

private:
    float ambientIntensity = 0.3f;
    glm::vec3 ambientColor = glm::vec3(1.0f);

};

