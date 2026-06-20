#version 440 core

in vec2 TexCoord;
in vec3 FragNormal;
in vec3 FragPos;

//Texture
uniform sampler2D textureSampler;
uniform vec4 tintColor;

//Ambient
uniform vec3 ambientColor;
uniform float ambientIntensity;

//Directional Lights
#define MAXIMUM_DIRECTIONALIGHTS 2
uniform int totalDirectionals;
uniform vec3 lightDirection[MAXIMUM_DIRECTIONALIGHTS];
uniform vec3 lightColor[MAXIMUM_DIRECTIONALIGHTS];
uniform float lightIntensity[MAXIMUM_DIRECTIONALIGHTS];
uniform float lightIsVisible[MAXIMUM_DIRECTIONALIGHTS];

//FlashLight
#define MAXIMUM_FLASHLIGHTS 2
uniform int totalFlashLights;
uniform vec3 flashLightPosition[MAXIMUM_FLASHLIGHTS];
uniform vec3 flashLightForward[MAXIMUM_FLASHLIGHTS];
uniform float flashLightInCircle[MAXIMUM_FLASHLIGHTS];
uniform float flashLightOutCircle[MAXIMUM_FLASHLIGHTS];
uniform float flashLightRange[MAXIMUM_FLASHLIGHTS];
uniform int flashLightEnabled[MAXIMUM_FLASHLIGHTS];

out vec4 fragColor;


void main()
{
    vec4 texColor = texture(textureSampler, TexCoord) * tintColor;

    vec3 ambient = ambientColor * ambientIntensity;

    vec3 directionalLights = vec3(0.0);
    for(int i = 0; i < totalDirectionals; i++)
    {
        if(lightIsVisible[i] > 0.0)
        {
            float amountLight = max(dot(FragNormal, normalize(lightDirection[i] * -1.0)), 0.0);
            directionalLights += lightColor[i] * lightIntensity[i] * amountLight;
        }
    }

    vec3 flashLight = vec3(0.0);
    if (flashLightEnabled == 1)
    {
        vec3 directionFrag = FragPos - flashLightPosition;
        float dist = length(directionFrag);

        if (dist < flashLightRange)
        {
            vec3 normalizedFragDirection = normalize(directionFrag);
            float centerDistance = dot(normalizedFragDirection, normalize(flashLightForward));

            float intensity = 0.0;
            if (centerDistance > flashLightInCircle)
            {
                intensity = 1.0;
            }
            else if (centerDistance > flashLightOutCircle)
            {
                intensity = 0.5;
            }
            else
            {
                intensity = 0.0;
            }

            float amountLightImpact = dot(FragNormal, normalizedFragDirection * -1);
            flashLight = vec3(amountLightImpact * intensity);
        }
    }

    vec3 lighting = ambient + directionalLights + flashLight;
    fragColor = vec4(texColor.rgb * lighting, texColor.a);
}
