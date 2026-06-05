#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm.hpp>

Model::Model(const std::vector<float>& vertexs, const std::vector<float>& uvs, const std::vector<float>& normals) {
    
    //Almaceno la cantidad de vertices que habra
    this->numVertexs = vertexs.size() / 3;

    //Generamos VAO/VBO
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->uvVBO);
    glGenBuffers(1, &this->normalVBO);
    //Defino el VAO creado como activo
    glBindVertexArray(this->VAO);

    //Defino el VBO de las posiciones como activo, le paso los datos y lo configuro
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(float), vertexs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Defino el VBO de las UVs como activo, le paso los datos y lo configuro
    glBindBuffer(GL_ARRAY_BUFFER, this->uvVBO);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    //Defino el VBO de normales como activo, le paso los datos y lo configuro
    glBindBuffer(GL_ARRAY_BUFFER, this->normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Activamos los tres atributos
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //Desvinculamos VAO y VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  


}

void Model::Render() const {

    //Vinculo su VAO para ser usado
    glBindVertexArray(this->VAO);

    // Dibujamos
    glDrawArrays(GL_TRIANGLES, 0, this->numVertexs);

    //Desvinculamos VAO
    glBindVertexArray(0);

}

//Funcion que leera un .obj y devolvera un modelo para poder ser renderizado
Model LoadOBJModel(const std::string& filePath) {

	//Verifico archivo y si no puedo abrirlo cierro aplicativo
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "No se ha podido abrir el archivo: " << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Variables lectura fichero
	std::string line;
	std::stringstream ss;
	std::string prefix;
	glm::vec3 tmpVec3;
	glm::vec2 tmpVec2;

	//Variables elemento modelo
	std::vector<float> vertexs;
	std::vector<float> vertexNormal;
	std::vector<float> textureCoordinates;

	//Variables temporales para algoritmos de sort
	std::vector<float> tmpVertexs;
	std::vector<float> tmpNormals;
	std::vector<float> tmpTextureCoordinates;

	//Recorremos archivo linea por linea
	while (std::getline(file, line)) {

		//Por cada linea reviso el prefijo del archivo que me indica que estoy analizando
		ss.clear();
		ss.str(line);
		ss >> prefix;

		//Estoy leyendo un vertice
		if (prefix == "v") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector de vertices los valores
			tmpVertexs.push_back(tmpVec3.x);
			tmpVertexs.push_back(tmpVec3.y);
			tmpVertexs.push_back(tmpVec3.z);
		}

		//Estoy leyendo una UV (texture coordinate)
		else if (prefix == "vt") {

			//Las UVs son siempre imagenes 2D asi que uso el tmpvec2 para almacenarlas
			ss >> tmpVec2.x >> tmpVec2.y;

			//Almaceno en mi vector temporal las UVs
			tmpTextureCoordinates.push_back(tmpVec2.x);
			tmpTextureCoordinates.push_back(tmpVec2.y);

		}

		//Estoy leyendo una normal
		else if (prefix == "vn") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector temporal de normales las normales
			tmpNormals.push_back(tmpVec3.x);
			tmpNormals.push_back(tmpVec3.y);
			tmpNormals.push_back(tmpVec3.z);

		}

		//Estoy leyendo una cara
		else if (prefix == "f") {

			std::string token;
			std::vector<std::string> faceTokens;
			while (ss >> token) {
				faceTokens.push_back(token);
			}

			// Triangulacion de poligonos (Triangle Fan)
			for (size_t i = 1; i + 1 < faceTokens.size(); i++) {
				std::string tokensToParse[3] = { faceTokens[0], faceTokens[i], faceTokens[i + 1] };

				for (int j = 0; j < 3; j++) {
					std::stringstream tokenStream(tokensToParse[j]);
					std::string vStr, vtStr, vnStr;

					std::getline(tokenStream, vStr, '/');
					std::getline(tokenStream, vtStr, '/');
					std::getline(tokenStream, vnStr, '/');

					int vIdx = vStr.empty() ? -1 : std::stoi(vStr) - 1;
					int vtIdx = vtStr.empty() ? -1 : std::stoi(vtStr) - 1;
					int vnIdx = vnStr.empty() ? -1 : std::stoi(vnStr) - 1;

					// Push Vertex
					if (vIdx >= 0 && vIdx * 3 + 2 < tmpVertexs.size()) {
						vertexs.push_back(tmpVertexs[vIdx * 3]);
						vertexs.push_back(tmpVertexs[vIdx * 3 + 1]);
						vertexs.push_back(tmpVertexs[vIdx * 3 + 2]);
					} else {
						vertexs.push_back(0.0f); vertexs.push_back(0.0f); vertexs.push_back(0.0f);
					}

					// Push UV
					if (vtIdx >= 0 && vtIdx * 2 + 1 < tmpTextureCoordinates.size()) {
						textureCoordinates.push_back(tmpTextureCoordinates[vtIdx * 2]);
						textureCoordinates.push_back(tmpTextureCoordinates[vtIdx * 2 + 1]);
					} else {
						textureCoordinates.push_back(0.0f); textureCoordinates.push_back(0.0f);
					}

					// Push Normal
					if (vnIdx >= 0 && vnIdx * 3 + 2 < tmpNormals.size()) {
						vertexNormal.push_back(tmpNormals[vnIdx * 3]);
						vertexNormal.push_back(tmpNormals[vnIdx * 3 + 1]);
						vertexNormal.push_back(tmpNormals[vnIdx * 3 + 2]);
					} else {
						// Si no hay normal, asignamos una por defecto
						vertexNormal.push_back(0.0f);
						vertexNormal.push_back(0.0f);
						vertexNormal.push_back(1.0f);
					}
				}
			}
		}
	}
	return Model(vertexs, textureCoordinates, vertexNormal);
}
