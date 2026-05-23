#include "ModelObject.h"


ModelObject::ModelObject(const std::string& modelPath, const std::string& texturePath)
{
	// Cargamos modelo
	Model modelParaCargarOBJ = LoadOBJModel(modelPath);
	//Lo pongo asi porque es un puntero model
	model = new Model(modelParaCargarOBJ); 

	// Cargamos la textura con stb image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLenum format = GL_RGB;
		if (nrChannels == 4) format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Failed to load texture: " << texturePath << std::endl;
	}

	//Shaders para texturas
	RenderManager::ShaderProgram shaderStruct;
	shaderStruct.vertexShader = RM->LoadVertexShader("TextureVertexShader.glsl");
	shaderStruct.fragmentShader = RM->LoadFragmentShader("TextureFragmentShader.glsl");
	shaderProgram = RM->CreateProgram(shaderStruct);
}

ModelObject::~ModelObject()
{
	glDeleteTextures(1, &textureID);
	delete model;
}

void ModelObject::Update(float dt) {}

void ModelObject::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	if (!isVisible) return;

	glUseProgram(shaderProgram);

	// Transform 
	glm::mat4 modelMat = transform->GetModelMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Tint del Color
	glUniform4fv(glGetUniformLocation(shaderProgram, "tintColor"), 1, glm::value_ptr(tintColor));

	// Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);

	// Renderizo modelo
	model->Render();

	glUseProgram(0);
}
