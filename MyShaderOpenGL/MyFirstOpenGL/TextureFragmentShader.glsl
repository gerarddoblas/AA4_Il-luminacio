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

//Sun
uniform vec3 sunDirection;
uniform vec3 sunColor;
uniform float sunIntensity;
uniform float sunActive;

//Luna
uniform vec3 moonDirection;
uniform vec3 moonColor;
uniform float moonIntensity;
uniform float moonActive;

//FlashLight
uniform vec3 flashLightPosition;
uniform vec3 flashLightForward;
uniform float flashLightInCircle;
uniform float flashLightOutCircle;
uniform float flashLightRange;
uniform int flashLightEnabled;

out vec4 fragColor;


void main()
{
    vec4 texColor = texture(textureSampler, TexCoord) * tintColor;

    vec3 ambient = ambientColor * ambientIntensity;

    vec3 sun = vec3(0.0);
    if(sunActive > 0.0)
    {
        float amountLight = dot(FragNormal, normalize(sunDirection *-1));
        sun = sunColor * sunIntensity * amountLight;
    }

    vec3 moon = vec3(0.0);
    if(moonActive > 0.0)
    {
        float amountLight = dot(FragNormal, normalize(moonDirection * -1));
        moon = moonColor * moonIntensity * amountLight;
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

    vec3 lighting = ambient + sun + moon + flashLight;
    fragColor = vec4(texColor.rgb * lighting, texColor.a);
}
