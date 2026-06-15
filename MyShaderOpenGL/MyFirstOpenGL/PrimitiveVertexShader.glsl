#version 440 core

layout(location = 0) in vec3 posicion;
layout(location = 1) in vec3 inNormal;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 scaleMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragNormal;
out vec3 FragPos;

void main()
{
    mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
    vec4 worldPos = model * vec4(posicion, 1.0);

    FragPos = worldPos.xyz;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    FragNormal = normalize(normalMatrix * inNormal);

    gl_Position = projectionMatrix * viewMatrix * worldPos;
}