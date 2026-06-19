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

	//AMBIENT LIGHT TO SEND TODO:
	glUniform3fv(glGetUniformLocation(shaderToPass, "ambientColor"), 1, glm::value_ptr(ambientColor));
	glUniform1f(glGetUniformLocation(shaderToPass, "ambientIntensity"), ambientIntensity);


	for (int i = 0; i < totalLights; i++)
	{
		std::string lightDirectionName = "lightDirection[" + std::to_string(i) + "]";
		std::string lightIntensityName = "lightIntensity[" + std::to_string(i) + "]";
		std::string lightVisibleName = "lightIsVisible[" + std::to_string(i) + "]";
		std::string lightColorName = "lightColor[" + std::to_string(i) + "]";


		DirectionalLight* lightToSendToShader = directionals[i];

		if (lightToSendToShader->isVisible)
		{
			glUniform3fv(glGetUniformLocation(shaderToPass, lightDirectionName.c_str()), 1, glm::value_ptr(lightToSendToShader->GetForward()));
			glUniform1f(glGetUniformLocation(shaderToPass, lightIntensityName.c_str()), lightToSendToShader->intensity);
			glUniform1f(glGetUniformLocation(shaderToPass, lightVisibleName.c_str()), lightToSendToShader->isVisible);
			glUniform3fv(glGetUniformLocation(shaderToPass, lightColorName.c_str()), 1, glm::value_ptr(lightToSendToShader->color));
		}
	
	}
	short totalFlashLights = flashLight.size();
	for (int i = 0; i < totalFlashLights; i++)
	{

		FlashLight* flashLightToSendToShader = flashLight[i];

		glUniform3fv(glGetUniformLocation(shaderToPass, "flashLightPosition"), 1, glm::value_ptr(flashLightToSendToShader->GetPosition()));
		glUniform3fv(glGetUniformLocation(shaderToPass, "flashLightForward"), 1, glm::value_ptr(flashLightToSendToShader->GetForward()));
		glUniform1f(glGetUniformLocation(shaderToPass, "flashLightInCircle"), flashLightToSendToShader->GetInCircle());
		glUniform1f(glGetUniformLocation(shaderToPass, "flashLightOutCircle"), flashLightToSendToShader->GetOutCircle());
		glUniform1f(glGetUniformLocation(shaderToPass, "flashLightRange"), flashLightToSendToShader->range);
		glUniform1i(glGetUniformLocation(shaderToPass, "flashLightEnabled"), flashLightToSendToShader->enabled);
	}
}
