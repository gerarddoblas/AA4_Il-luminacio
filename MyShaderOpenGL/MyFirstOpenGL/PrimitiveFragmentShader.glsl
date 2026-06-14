#version 440 core

in vec3 FragNormal;
in vec3 FragPos;

//Color base del cubo
uniform vec3 baseColor;

//Luz ambiente
uniform vec3 ambientColor;
uniform float ambientIntensity;

//Sol
uniform vec3 sunDirection;
uniform vec3 sunColor;
uniform float sunIntensity;
uniform float sunActive;

//Luna
uniform vec3 moonDirection;
uniform vec3 moonColor;
uniform float moonIntensity;
uniform float moonActive;

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
    vec3 sun = CalcDirectional(sunDirection,  sunColor,  sunIntensity,  sunActive);
    vec3 moon = CalcDirectional(moonDirection, moonColor, moonIntensity, moonActive);
    vec3 spot = CalcFlashLight();

    vec3 lighting = ambient + sun + moon;
    fragColor = vec4(baseColor * lighting, 1.0);
}
