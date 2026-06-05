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
