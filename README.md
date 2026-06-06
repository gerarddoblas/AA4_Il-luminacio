# AA4_Il-luminacio

Uso de la IA:

A sido utilizada para ayudar a solventar errores de codigo relacionados con el movimiento de la camara.
Se a utilizado para revisar y mejorar codigo relasionado con el movimiento de la camara.
A ayudado con la rotacion y movimiento de la camara (principalmente aportando las formulas).
A propuesto utilizar la variable "bool firstMouseRead" para evitar posibles problemas (y se ha decidido utilizarlo).

Codigo de la IA:
bool firstMouseRead = true;
if(firstMouseRead)
{
    prevMouseX = mouseX;
    prevMouseY = mouseY;
    firstMouseRead = false;
}

 if (IM->GetKey(GLFW_KEY_W, HOLD) || IM->GetKey(GLFW_KEY_W, DOWN))
     transform->position += forward * moveSpeed * dt;
...

glm::vec3 Camera::GetForward() const
{
    glm::vec3 forward;
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(forward);
}

Tambien se ha utilizado los LLM para la siguiente tool


Prompt:

Estoy reutilizando el código para hacer que la escala y la rotación sea aleatoria, puedes ayudarme a optimizar esto en mi clase Utils.h y .cpp?

float RandomRange(float min, float max) { return min + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min); }

I poder evitar replicar código.
