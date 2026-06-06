#pragma once
#include "GameObject.h"
#include "Model.h"
#include "RenderManager.h"
#include <stb_image.h>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <string>

class ModelObject : public GameObject
{
public:
	ModelObject(const std::string& modelPath, const std::string& texturePath);
	~ModelObject() override;

	void Update(float dt) override;
	void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const LightData& lights) override;

	void SetTintColor(const glm::vec4& color) { tintColor = color; }
	void SetUnlit(bool unlit) { isUnlit = unlit; }

private:
	Model* model = nullptr;
	GLuint textureID = 0;
	glm::vec4 tintColor = glm::vec4(1.0f); //Blanco by default
	bool isUnlit = false;
	GLuint shaderProgram = 0;
};
