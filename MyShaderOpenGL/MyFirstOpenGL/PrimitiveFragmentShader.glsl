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
uniform float flashLightInnerCos;
uniform float flashLigthExterCos;
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

    if (cosA < flashLigthExterCos) return vec3(0.0);

    float epsilon = flashLightInnerCos - flashLigthExterCos;
    float cone = clamp((cosA - flashLigthExterCos) / epsilon, 0.0, 1.0);
    float atten = 1.0 - clamp(dist / flashLightRange, 0.0, 1.0);
    atten = atten * atten;

    float diff = max(dot(FragNormal, -fragDir), 0.0);
    return vec3(diff * cone * atten);
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
