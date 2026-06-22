# AA3_3DModels-Camera

Edgar Novas, Gerard Doblas, Nil Barrero

Hemos utilizado las siguientes fuentes:

	LearnOpenGL:https://learnopengl.com/Lighting/Multiple-lights
		
		De la pagina official de OpenGL, hemos revisado el apartado de luces, en donde, se comenta el como gestionar varias luces y el como mantener una estructura para que la legibilidad de este sea limpia.

	Kronnos:https://community.khronos.org/t/passing-array-of-vec3-to-fragment-shader/74450/8
		De la siguiente pagina "Kronnos" hemos revisado el como poder pasar las variables por el for del shader, en el comentario 10.
		Dejamos el ejemplo que da la persona que responde:
			
			for(int i = 0; i < 9; ++i)
        		{
            			std::string text{"pointPosition["};
            			text += std::to_string(i) + "]";
            			glUniform3f(glGetUniformLocation(floorShader.Program, text),
                        		pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
        		}
			/*
			your code:
 			for(int i = 0; i < 9; ++i)
        		{
            			glUniform3f(glGetUniformLocation(floorShader.Program, "pointPositions[i]"),
                        		pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
        		}

			*/	

Uso de la IA para:

Revisión de magic numbers y optimización de código.

Posiciones de los distintos elementos en el mapa y revisar código.

Codigo hecho con IA: (Sigue por aquí Nil)


Prompt:

Estoy reutilizando el código para hacer que la escala y la rotación sea aleatoria, puedes ayudarme a optimizar esto en mi clase Utils.h y .cpp sin que tenga que hacer copycat?

Respuesta:
float RandomRange(float min, float max) { return min + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min); }


Prompot 2nd:

Puedes ajustar la posición de los GameObjects al tamaño del Ground?

Respuesta:

const glm::vec3 SPAWN_POINTS[] =
{
    // Fila cercana  (Z: -4 a -6)
    glm::vec3(-7.0f, -0.8f,  -4.0f),
    glm::vec3( 0.0f, -0.8f,  -4.0f),
    glm::vec3( 7.0f, -0.8f,  -4.0f),
    glm::vec3(-4.0f, -0.8f,  -6.0f),
    glm::vec3( 4.0f, -0.8f,  -6.0f),
    // Fila media  (Z: -7 a -9)
    glm::vec3(-8.0f, -0.8f,  -7.0f),
    glm::vec3(-3.0f, -0.8f,  -8.0f),
    glm::vec3( 0.0f, -0.8f,  -9.0f),
    glm::vec3( 3.0f, -0.8f,  -8.0f),
    glm::vec3( 8.0f, -0.8f,  -7.0f),
    // Fila lejana  (Z: -10 a -12)
    glm::vec3(-8.0f, -0.8f, -10.0f),
    glm::vec3(-5.0f, -0.8f, -11.0f),
    glm::vec3( 0.0f, -0.8f, -12.0f),
    glm::vec3( 5.0f, -0.8f, -11.0f),
    glm::vec3( 8.0f, -0.8f, -10.0f),
    // Extremos del suelo  (Z: -12)
    glm::vec3(-8.0f, -0.8f, -12.0f),
    glm::vec3(-4.0f, -0.8f, -12.0f),
    glm::vec3( 0.0f, -0.8f, -12.0f),
    glm::vec3( 4.0f, -0.8f, -12.0f),
    glm::vec3( 8.0f, -0.8f, -12.0f),
    glm::vec3( 0.0f, -0.8f,  6.0f), // Punto delante de la camara
};
constexpr short NUM_SPAWN_POINTS = 21;
