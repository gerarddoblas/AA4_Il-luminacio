#include "LightManager.h"

void LightManager::AddDirectionalLight(DirectionalLight* dl)
{
	directionals.push_back(dl);
}

void LightManager::AddFlashLight(FlashLight* fl)
{
	flashLight.push_back(fl);
}

void LightManager::ApplyLightsRender(GLuint shaderToPass)
{
	short totalLights = directionals.size();
	glUniform1i(glGetUniformLocation(shaderToPass, "totalDirectionals"), totalLights);

	//ambient light
	glUniform3fv(glGetUniformLocation(shaderToPass, "ambientColor"), 1, glm::value_ptr(ambientColor));
	glUniform1f(glGetUniformLocation(shaderToPass, "ambientIntensity"), ambientIntensity);


	for (int i = 0; i < totalLights; i++)
	{
		std::string lightDirectionName = "lightDirection[" + std::to_string(i) + "]";
		std::string lightIntensityName = "lightIntensity[" + std::to_string(i) + "]";
		std::string lightVisibleName = "lightIsVisible[" + std::to_string(i) + "]";
		std::string lightColorName = "lightColor[" + std::to_string(i) + "]";


		DirectionalLight* lightToSendToShader = directionals[i];

		glUniform1f(glGetUniformLocation(shaderToPass, lightVisibleName.c_str()), lightToSendToShader->isVisible ? 1.0f : 0.0f);

		if (lightToSendToShader->isVisible)
		{
			glUniform3fv(glGetUniformLocation(shaderToPass, lightDirectionName.c_str()), 1, glm::value_ptr(lightToSendToShader->GetForward()));
			glUniform1f(glGetUniformLocation(shaderToPass, lightIntensityName.c_str()), lightToSendToShader->intensity);
			glUniform3fv(glGetUniformLocation(shaderToPass, lightColorName.c_str()), 1, glm::value_ptr(lightToSendToShader->color));
		}
	
	}
	short totalFlashLights = flashLight.size();
	glUniform1i(glGetUniformLocation(shaderToPass, "totalFlashLights"), totalFlashLights);

	for (int i = 0; i < totalFlashLights; i++)
	{

		std::string flashLightPositionName = "flashLightPosition[" + std::to_string(i) + "]";
		std::string flashLightForwardName = "flashLightForward[" + std::to_string(i) + "]";
		std::string flashLightInCircleName = "flashLightInCircle[" + std::to_string(i) + "]";
		std::string flashLightOutCircleName = "flashLightOutCircle[" + std::to_string(i) + "]";
		std::string flashLightRangeName = "flashLightRange[" + std::to_string(i) + "]";
		std::string flashLightEnabledName = "flashLightEnabled[" + std::to_string(i) + "]";
		

		FlashLight* flashLightToSendToShader = flashLight[i];

		glUniform1f(glGetUniformLocation(shaderToPass, flashLightEnabledName.c_str()), flashLightToSendToShader->isVisible ? 1.0f : 0.0f);

		if (flashLightToSendToShader->isVisible)
		{

			glUniform3fv(glGetUniformLocation(shaderToPass, flashLightPositionName.c_str()), 1, glm::value_ptr(flashLightToSendToShader->GetPosition()));
			glUniform3fv(glGetUniformLocation(shaderToPass, flashLightForwardName.c_str()), 1, glm::value_ptr(flashLightToSendToShader->GetForward()));
			glUniform1f(glGetUniformLocation(shaderToPass, "flashLightInCircle"), flashLightToSendToShader->GetInCircle());
			glUniform1f(glGetUniformLocation(shaderToPass, "flashLightOutCircle"), flashLightToSendToShader->GetOutCircle());
			glUniform1f(glGetUniformLocation(shaderToPass, "flashLightRange"), flashLightToSendToShader->range);
			glUniform1i(glGetUniformLocation(shaderToPass, "flashLightEnabled"), flashLightToSendToShader->enabled);
		}
		
	}
}

void LightManager::SetAmbient(glm::vec3 colorLight, float intensityAmbien)
{
	ambientColor = colorLight;
	ambientIntensity = intensityAmbien;
}
