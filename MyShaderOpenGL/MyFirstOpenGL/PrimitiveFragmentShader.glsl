#version 440 core

in vec3 FragNormal;
in vec3 FragPos;

// Color base del cubo
uniform vec3 baseColor;

// Luz ambiente
uniform vec3  ambientColor;
uniform float ambientIntensity;

// Sol
uniform vec3  sunDirection;
uniform vec3  sunColor;
uniform float sunIntensity;
uniform float sunActive;

// Luna
uniform vec3  moonDirection;
uniform vec3  moonColor;
uniform float moonIntensity;
uniform float moonActive;

// Linterna
uniform vec3  spotPosition;
uniform vec3  spotDirection;
uniform vec3  spotColor;
uniform float spotIntensity;
uniform float spotInnerCos;
uniform float spotOuterCos;
uniform float spotRange;
uniform int   spotEnabled;

out vec4 fragColor;

vec3 CalcDirectional(vec3 dir, vec3 lightColor, float intensity, float isActive)
{
    float diff = max(dot(FragNormal, -normalize(dir)), 0.15);
    return lightColor * intensity * diff * isActive;
}

vec3 CalcSpot()
{
    if (spotEnabled == 0) return vec3(0.0);

    vec3  toFrag = FragPos - spotPosition;
    float dist   = length(toFrag);
    if (dist > spotRange) return vec3(0.0);

    vec3  fragDir = normalize(toFrag);
    float cosA    = dot(fragDir, normalize(spotDirection));

    if (cosA < spotOuterCos) return vec3(0.0);

    float epsilon = spotInnerCos - spotOuterCos;
    float cone    = clamp((cosA - spotOuterCos) / epsilon, 0.0, 1.0);
    float atten   = 1.0 - clamp(dist / spotRange, 0.0, 1.0);
    atten         = atten * atten;

    float diff    = max(dot(FragNormal, -fragDir), 0.0);
    return spotColor * spotIntensity * diff * cone * atten;
}

void main()
{
    vec3 ambient  = ambientColor * ambientIntensity;
    vec3 sun      = CalcDirectional(sunDirection,  sunColor,  sunIntensity,  sunActive);
    vec3 moon     = CalcDirectional(moonDirection, moonColor, moonIntensity, moonActive);
    vec3 spot     = CalcSpot();

    vec3 lighting = ambient + sun + moon;
    fragColor     = vec4(baseColor * lighting, 1.0);
}
