#version 330 core

in vec2 UV;
in float ttl;
out vec4 color;
uniform sampler2D texture1;
uniform vec3 spriteColor;
uniform float maxTtl;

void main()
{
	vec4 texColor = texture(texture1, UV);
    color = vec4(spriteColor, ttl / maxTtl) * texColor;
} 