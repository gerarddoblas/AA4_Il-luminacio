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

Codigo hecho con IA: 

PREGUNTA:
oye el LightManager.h y cpp mira este es el .h
#include <vector>
#include "DirectionalLight.h"
#include "FlashLight.h"


#define LM LightManager::GetInstance()



class LightManager
{
public:
    static LightManager* GetInstance()
    {
        static LightManager instance;
        return &instance;
    }

	std::vector<DirectionalLight> directionals;
	std::vector<FlashLight> flashLight;





};

RESPUESTA:
Bien, existe. Hay un problema importante en el .h que tienes ahora:

El problema: vector de objetos vs vector de punteros
cpp
std::vector<DirectionalLight> directionals;   // ❌ copia objetos
std::vector<FlashLight> flashLight;           // ❌ copia objetos
Si guardas los objetos por valor, cuando hagas directionals.push_back(sun) estarías copiando el sol, no guardando el que tienes en la escena. Los cambios que haga UpdateDayNight (mover la posición, cambiar visibilidad...) no se verían reflejados.
Necesitas punteros:
cpp
std::vector<DirectionalLight*> directionals;  // ✅ apunta al original
std::vector<FlashLight*> flashLight;          // ✅ apunta al original

Lo que le falta al .h
El LightManager tiene las listas pero no tiene ningún método para:
Añadir luces (AddDirectional, AddFlashLight)
Aplicar las luces a un shader (ApplyLights(GLuint shaderProgram))
El #pragma once al principio

Pregunta clave antes de que escribas ApplyLights
¿Qué tiene que hacer ese método exactamente? Para cada DirectionalLight* de la lista, tiene que mandar al shader:
Su dirección (GetForward())
Su color (color)
Su intensidad (intensity)
Si está activa o no (isVisible)


PREGUNTA:

got it vale que sobra y que falta en main scene y el light manager






RESPUESTA

MainScene.h
Sobra:
#include "DayNightCycle.h" — ya no existe
Falta:
float angleDeg = 0.0f; — la usas en UpdateDayNight pero no está declarada
#include "LightManager.h" — para poder usar LM

MainScene.cpp
Sobra (líneas 37-46):
Todo el bloque de dayNightCycle — ya no existe esa variable en el .h
Bug importante en UpdateDayNight: Tienes esto:
cpp
glm::vec3 ambientColor;   // ← variable LOCAL, nueva
float ambientIntensity;   // ← variable LOCAL, nueva
Estás creando variables locales nuevas con el mismo nombre que los miembros de la clase. Los miembros nunca se actualizan, por eso el glClearColor de Update() siempre usa el valor inicial. Solución: quita esas dos declaraciones locales y asigna directamente a this->ambientColor y this->ambientIntensity.
Falta:
Llamar a UpdateDayNight(dt) desde Update() — la función existe pero nunca se invoca
En OnEnter(), después de crear sun y moon: LM->AddDirectional(sun) y LM->AddDirectional(moon)

LightManager
Falta el método principal:
ApplyLights(GLuint shaderProgram) — sin esto el LightManager no hace nada útil todavía

¿Por cuál empiezas? Te recomiendo primero limpiar el MainScene (los bugs son bloqueantes) y luego atacar ApplyLights.


PREGUNTA:
Paso las luces y me dan errores de iluminacion aunque con el for se supone que mando 2 no?
RESPUESTA:
El contrato entre C++ y el shader
En la Opción A, el shader tiene arrays de tamaño fijo para recibir las luces, y desde C++ los rellenas con un bucle.
Para tus 2 direccionales necesitas decidir:
¿Cuántas direccionales soporta el shader como máximo?
Como tienes exactamente 2 (sol y luna), puedes poner MAX_DIRECTIONALS = 2 en vez de 8

Lo que necesitas en cada sitio
En el shader GLSL tienes que declarar:
Un array de direcciones: uniform vec3 dirLightDir[2]
Un array de colores: uniform vec3 dirLightColor[2]
Un array de intensidades: uniform float dirLightIntensity[2]
Un array de activas/no activas: uniform float dirLightActive[2]
El número de luces reales: uniform int numDirectionals
Y en el main() del shader, un bucle que itera numDirectionals y acumula el resultado de cada luz.
En LightManager::ApplyLights(GLuint shaderProgram) tienes que:
Iterar el vector directionals
Para cada una, mandar sus datos al array del shader con glUniform3fv(..., index, ...) — fíjate que glUniform para arrays tiene una forma especial
Mandar también numDirectionals con glUniform1i
PARA HACERLO ME HE BASADO EN ESTE COMENTARIO 9 DE ESTA PAGINA
community.khronos.org/t/passing-array-of-vec3-to-fragment-shader/74450/10

Y ESTA
https://opentk.net/learn/chapter2/6-multiple-lights.html



PREGUNTA:
  Puedes cambiar los nombres de las variables en el shader en el TextureFragmentShader.glsl por las variables que he puesto en el Light Manager? Solo haz eso nada mas


RESPUESTA:
He añadido las variables con los arrays exactamente con los mismos nombres que pusiste en el C++ (totalDirectionals, lightDirection, lightColor, lightIntensity, lightIsVisible).
He eliminado las de sol y luna por separado.
He juntado el cálculo de las luces direccionales en un único bucle for que acumula el resultado en la variable directionalLights. (Ah, y le puse un max(..., 0.0) al dot para evitar colores negativos cuando la luz da por detrás, que siempre viene bien).
Con esto, el TextureFragmentShader ya está listo para recibir los datos de tu LightManager. ¿Hay algún otro sitio en el que tengas problemas para conectar esto?


PREGUNTA:
Le he dado al play y ahora el sol esta dentro de la luna y el cube ni se ve, puedes mirar que pasa en los archivos que pase?


Veo tres problemas. Te los explico:

Problema 1 — Sol y luna en el mismo sitio
UpdateDayNight(dt) nunca se llama desde Update(). Por eso el sol y la luna jamás se mueven de la posición (0, 0, 0). Los dos objetos visuales están en el origen, uno encima del otro.
Lo que tienes que hacer tú: añadir UpdateDayNight(dt) dentro de MainScene::Update().

Problema 2 — El cubo no se ve
El PrimitiveFragmentShader.glsl todavía tiene los uniforms viejos (sunDirection, moonDirection...) — hay que actualizarlo igual que hice con el TextureFragmentShader. ¿Quieres que lo actualice también?

Problema 3 — LightManager vacío
En OnEnter() creas sun y moon pero nunca los registras en el LightManager. Por eso totalDirectionals = 0 y el shader calcula con 0 luces — solo ambient.
Lo que tienes que hacer tú: justo después de crear sun y moon en OnEnter(), añadir:
cpp
LM->AddDirectionalLight(sun);
LM->AddDirectionalLight(moon);


PREGUNTA:
La cosa es que no se porque ahora se ve distinto de antes, antes los personajes estaban encima del suelo ahora estan volando o el suelo esta muy bajo


RESPUESTA:
El motivo por el que los personajes parecen estar "volando" es puro cálculo matemático de las coordenadas que tienes puestas:
El suelo se crea en la altura Y = -1.2f
Los personajes se están creando en la altura Y = -0.8f
Hay exactamente 0.4f unidades de distancia entre los pies de los personajes y el suelo. Siempre han estado volando, pero como antes los shaders o la iluminación estaban rotos, visualmente no te dabas cuenta o el suelo negro lo disimulaba.
Para que no vuelen, en MainScene.cpp tienes que igualar las alturas. Por ejemplo, pon el suelo a la misma altura que los spawns:
cpp
const float FLOOR_Y = -0.8f; // Antes era -1.2f
¿Por qué sigue sin verse el suelo?
Hay dos motivos por los que el cubo (el suelo) puede ser invisible o verse completamente negro:
Si no le cambiaste el shader: Me pediste "sino lo hace ponle ese (el Texture)". ¡El cubo NO PUEDE usar el TextureFragmentShader! Ese shader necesita una textura y coordenadas UV. Tu cubo solo tiene geometría básica (vértices y normales). Si le pones el shader de texturas y no le pasas una textura, OpenGL lo dibuja completamente negro o invisible. Tienes que asegurarte de que Cube.cpp usa los PrimitiveVertexShader y PrimitiveFragmentShader.
La luz ambiente está desconectada: En MainScene::UpdateDayNight estás calculando el color del amanecer, mediodía, noche... pero lo estás guardando en variables locales y nunca se lo envías al LightManager.
Para arreglar la iluminación de toda la escena, añade esto al final de tu LightManager.h:
cpp
public:
   void SetAmbient(glm::vec3 color, float intensity) {
       ambientColor = color;
       ambientIntensity = intensity;
   }
Y al final de MainScene::UpdateDayNight() (justo antes de la llave de cierre }), añade esto para que el manager reciba el cambio de día y noche:
cpp
   // Guardamos en la escena para el sky
   this->ambientColor = ambientColor;
   this->ambientIntensity = ambientIntensity;
   // Y se lo pasamos al LightManager para que ilumine los modelos y el suelo
   LM->SetAmbient(ambientColor, ambientIntensity);
Prueba a hacer estos 3 cambios (el FLOOR_Y, confirmar los shaders del cubo a Primitive, y pasarle el ambient al LightManager). ¡Ya deberías ver el suelo verde y la luz cambiando de color!


PREGUNTA:
Puedes mirar porque la luz de la luna no se aplica? O almenos no lo parece
RESPUESTA:
¡Muy buena pillada! Resulta que tenías un bug invisible en el LightManager.cpp.
Mira cómo estaba tu código:
cpp
if (lightToSendToShader->isVisible)
{
   // ...
   glUniform1f(..., lightToSendToShader->isVisible);
   // ...
}
¿Ves la trampa mortal ahí?
Si la luz está visible (isVisible == true), entra al if y le dice al shader lightIsVisible = 1.0. Perfecto.
Pero cuando la luna o el sol se esconden por debajo del suelo, su isVisible pasa a ser false.
Como es false, no entra al if. ¡Y por tanto nunca le dice al shader que la luz se ha apagado!
Para el shader, la última noticia que tuvo fue "la luz 0 está visible" y se queda eternamente calculando esa luz (incluso desde debajo del suelo) bloqueando el efecto real de la luna y el sol alternándose.
Acabo de arreglarte el archivo LightManager.cpp simplemente sacando la variable lightIsVisible fuera del if para que siempre actualice su estado (sea 1.0 o 0.0):
cpp
glUniform1f(glGetUniformLocation(shaderToPass, lightVisibleName.c_str()), lightToSendToShader->isVisible ? 1.0f : 0.0f);
if (lightToSendToShader->isVisible)
{
   // Mandamos el resto de datos solo si hace falta
}


PREGUNTA:
Porque ahora la luz de la luna y el sol no se mueven, no se que pasa o hay poco sol o no se puedes mirarlo? pero la luz no se mueve, parece estatica, rectifico la luz del sol si se nota pero la de la luina no
RESPUESTA:
¡Acabo de encontrar el porqué y te lo he arreglado! Eran dos bugs matemáticos que tenías en tu código de MainScene.cpp:
El cielo nunca se hacía de noche: Aunque estabas calculando los colores del cielo (colorNight, colorDay), se los pasabas al LightManager pero nunca actualizabas las variables de la propia escena (this->ambientColor). Como resultado, el fondo de la pantalla siempre era el azul clarito de día. Si el cielo es azul claro, la tenue luz de la luna (que también es azul) pasa totalmente desapercibida y parece que no hay luna.
Las horas estaban desincronizadas: Estabas usando sin(angulos) en vez de cos(angulos). Esto hacía que cuando el sol estaba en lo más alto (mediodía matemático), el código se creía que era el atardecer, y cuando era medianoche se creía que era el amanecer. Las luces y los colores iban totalmente a destiempo.
He ajustado el UpdateDayNight cambiando el sin por un cos, ajustando los rangos del if, y añadiendo las dos líneas finales para que el color de fondo (glClearColor) se oscurezca de verdad cuando el sol se esconde.
Dale al play ahora. Vas a ver cómo el cielo pasa de azul brillante a naranja y luego a un azul muy oscuro. Cuando esté oscuro, la luz de la luna (que va rotando lentamente porque le hemos puesto 60 segundos por vuelta) iluminará el suelo de color azul. ¡Se ve genial!


PREGUNTA
He quitado el LightData  y el DayNightCycle y ahora me esta dando error y no puedo darle play porque la Main Scene usa el LightData puedes quitarlo? 

ANTES (Lo que te daba error)
Antes, la propia Escena tenía que buscar manualmente a todos los objetos luz (haciendo conversiones dynamic_cast), rellenar un paquete de datos llamado LightData y pelearse con ello.
cpp
void Scene::Render()
{
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glm::mat4 projectionMatrix = camera->GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);
	LightData lights;
	lights.ambientColor = ambientColor;
	lights.ambientIntensity = ambientIntensity;
	for (GameObject* o : objects)
	{
		DirectionalLight* dl = dynamic_cast<DirectionalLight*>(o);
		if (dl)
		{
			if (dl->tag == "sun")
			{
				lights.sunDirection = dl->GetForward();
				lights.sunColor = dl->color;
				lights.sunIntensity = dl->intensity;
				lights.sunActive = dl->isVisible ? 1.0f : 0.0f;
			}
			else if (dl->tag == "moon")
			{
				lights.moonDirection = dl->GetForward();
				lights.moonColor = dl->color;
				lights.moonIntensity = dl->intensity;
				lights.moonActive = dl->isVisible ? 1.0f : 0.0f;
			}
		}
	}
	FlashLight* sl = camera->flashlight;
	if (sl)
	{
		lights.flashLightPosition = sl->GetTransform()->position;
		lights.flashLightForward = sl->GetForward();
		lights.flashLightInCircle = sl->GetInCircle();
		lights.flashLightOutCircle = sl->GetOutCircle();
		lights.flashLightRange = sl->range;
		lights.flashLightEnabled = sl->enabled ? 1 : 0;
	}
	for (GameObject* o : objects) {
		if (o != nullptr && o->isVisible) {
			o->Render(viewMatrix, projectionMatrix);
		}
	}
}

AHORA (El código actual)
Con la llegada del LightManager, la escena ya no necesita saber si existe el sol, la luna o las linternas. El LightManager es el que almacena las luces cuando se crean y se encarga de enviarlas a la gráfica. La función de la escena vuelve a ser simplemente "Dibuja a los objetos en la pantalla usando la cámara". Fíjate qué limpieza:
cpp
void Scene::Render()
{
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glm::mat4 projectionMatrix = camera->GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);
	for (GameObject* o : objects) {
		if (o != nullptr && o->isVisible) {
			o->Render(viewMatrix, projectionMatrix);
		}
	}
}
Ese bloque gigante del medio intentaba crear un LightData que tú ya habías borrado con buen criterio, y por eso OpenGL te decía "No sé qué es esto". Al borrarlo, todo vuelve a encajar con tu nueva arquitectura.



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
