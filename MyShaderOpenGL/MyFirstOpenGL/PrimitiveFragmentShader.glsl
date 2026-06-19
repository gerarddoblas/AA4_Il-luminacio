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

//Linterna
uniform vec3 flashLightPosition;
uniform vec3 flashLightForward;
uniform float flashLightInCircle;
uniform float flashLightOutCircle;
uniform float flashLightRange;
uniform int flashLightEnabled;

out vec4 fragColor;

vec3 CalcDirectional(vec3 dir, vec3 lightColor, float intensity, float isActive)
{
    float diff = max(dot(FragNormal, -normalize(dir)), 0.15);
    return lightColor * intensity * diff * isActive;
}

vec3 CalcFlashLight()
{
    if (flashLightEnabled == 0) return vec3(0.0);

    vec3 toFrag = FragPos - flashLightPosition;
    float dist = length(toFrag);
    if (dist > flashLightRange) return vec3(0.0);

    vec3 fragDir = normalize(toFrag);
    float cosA = dot(fragDir, normalize(flashLightForward));

    float intensity = 0.0;
    if (cosA > flashLightInCircle)
    {
        intensity = 1.0;
    }
    else if (cosA > flashLightOutCircle)
    {
        intensity = 0.5;
    }
    else
    {
        return vec3(0.0);
    }

    float diff = max(dot(FragNormal, -fragDir), 0.0);
    return vec3(diff * intensity);
}

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

    vec3 spot = CalcFlashLight();

    vec3 lighting = ambient + directionalLights + spot;
    fragColor = vec4(baseColor * lighting, 1.0);
}
