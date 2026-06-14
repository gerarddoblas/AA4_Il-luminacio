#version 440 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 TexCoord;
out vec3 FragNormal;
out vec3 FragPos;

void main()
{
    vec4 worldPos = modelMatrix * vec4(inPosition, 1.0);
    FragPos = worldPos.xyz;

    
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    FragNormal = normalize(normalMatrix * inNormal);

    TexCoord = vec2(inTexCoord.x, 1.0 - inTexCoord.y);
    gl_Position = projectionMatrix * viewMatrix * worldPos;
}
