#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

void main()
{ 
	vec4 tex = texture(screenTexture, TexCoords);
	float avg = (tex.r + tex.g + tex.b) / 3;
	color = vec4(avg, avg, avg, tex.a);
}