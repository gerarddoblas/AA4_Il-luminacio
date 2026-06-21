#version 440 core

in vec3 FragNormal;
in vec3 FragPos;

//Color base del cubo
uniform vec3 baseColor;

//Luz ambiente
uniform vec3 ambientColor;
uniform float ambientIntensity;

#define MAX_DIRECTIONALS 2
uniform int totalDirectionals;
uniform vec3 lightDirection[MAX_DIRECTIONALS];
uniform vec3 lightColor[MAX_DIRECTIONALS];
uniform float lightIntensity[MAX_DIRECTIONALS];
uniform float lightIsVisible[MAX_DIRECTIONALS];

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
    for(int i = 0; i < totalFlashLights; i++)
    {
        if (flashLightEnabled[i] == 1)
        {
            vec3 directionFrag = FragPos - flashLightPosition[i];
            float dist = length(directionFrag);

            if (dist < flashLightRange[i])
            {
                vec3 normalizedFragDirection = normalize(directionFrag);
                float centerDistance = dot(normalizedFragDirection, normalize(flashLightForward[i]));

                float intensity = 0.0;
                if (centerDistance > flashLightInCircle[i])
                {
                    intensity = 1.0;
                }
                else if (centerDistance > flashLightOutCircle[i])
                {
                    intensity = 0.5;
                }
                else
                {
                    intensity = 0.0;
                }

                float amountLightImpact = dot(FragNormal, normalizedFragDirection * -1.0);
                flashLight += vec3(amountLightImpact * intensity);
            }
        }
    }

    vec3 lighting = ambient + directionalLights + flashLight;
    fragColor = vec4(baseColor * lighting, 1.0);
}
