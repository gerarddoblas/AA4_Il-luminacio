#version 440 core

in vec2  TexCoord;
in vec3  FragNormal;
in vec3  FragPos;

// Textura y tinte base
uniform sampler2D textureSampler;
uniform vec4      tintColor;
uniform int       isUnlit; // 1 si el objeto no recibe luz (emisivo)

// Luz ambiente - cambia con el ciclo dia/noche
uniform vec3  ambientColor;
uniform float ambientIntensity;

// Sol - directional light
uniform vec3  sunDirection;
uniform vec3  sunColor;
uniform float sunIntensity;
uniform float sunActive;

// Luna - directional light
uniform vec3  moonDirection;
uniform vec3  moonColor;
uniform float moonIntensity;
uniform float moonActive;

// Linterna - spotlight
uniform vec3  spotPosition;
uniform vec3  spotDirection;
uniform vec3  spotColor;
uniform float spotIntensity;
uniform float spotInnerCos;
uniform float spotOuterCos;
uniform float spotRange;
uniform int   spotEnabled;

out vec4 fragColor;

// Calcula la contribucion difusa de una luz direccional con minimo del 15%
vec3 CalcDirectional(vec3 dir, vec3 lightColor, float intensity, float isActive)
{
    float diff = max(dot(FragNormal, -normalize(dir)), 0.15);
    return lightColor * intensity * diff * isActive;
}

// Calcula la contribucion del spotlight con cono y atenuacion por distancia
vec3 CalcSpot()
{
    if (spotEnabled == 0) return vec3(0.0);

    vec3  toFrag  = FragPos - spotPosition;
    float dist    = length(toFrag);
    if (dist > spotRange) return vec3(0.0);

    vec3  fragDir = normalize(toFrag);
    float cosA    = dot(fragDir, normalize(spotDirection));

    // Fuera del cono exterior no hay luz
    if (cosA < spotOuterCos) return vec3(0.0);

    // Suavizado entre inner y outer cone
    float epsilon  = spotInnerCos - spotOuterCos;
    float cone     = clamp((cosA - spotOuterCos) / epsilon, 0.0, 1.0);

    // Atenuacion por distancia
    float atten    = 1.0 - clamp(dist / spotRange, 0.0, 1.0);
    atten          = atten * atten; // cuadratica para suavizar

    float diff     = max(dot(FragNormal, -fragDir), 0.0);
    return spotColor * spotIntensity * diff * cone * atten;
}

void main()
{
    vec4 texColor = texture(textureSampler, TexCoord) * tintColor;

    if (isUnlit == 1)
    {
        fragColor = texColor;
        return;
    }

    vec3 ambient  = ambientColor * ambientIntensity;
    vec3 sun      = CalcDirectional(sunDirection,  sunColor,  sunIntensity,  sunActive);
    vec3 moon     = CalcDirectional(moonDirection, moonColor, moonIntensity, moonActive);
    vec3 spot     = CalcSpot();

    vec3 lighting = ambient + sun + moon;
    fragColor     = vec4(texColor.rgb * lighting, texColor.a);
}
