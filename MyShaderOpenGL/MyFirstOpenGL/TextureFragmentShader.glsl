#version 440 core

in vec2 TexCoord;

uniform sampler2D textureSampler;
uniform vec4 tintColor;

out vec4 fragColor;

void main()
{
	vec4 texColor = texture(textureSampler, TexCoord);
	fragColor = texColor * tintColor;
}
