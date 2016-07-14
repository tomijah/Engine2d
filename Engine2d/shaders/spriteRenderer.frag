#version 330 core

in vec2 UV;
out vec4 color;
uniform sampler2D texture1;
uniform vec4 spriteColor;

void main()
{
	vec4 texColor = texture(texture1, UV);
    color = spriteColor * texColor;
} 