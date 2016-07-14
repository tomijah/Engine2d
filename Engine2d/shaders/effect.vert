#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

uniform float time;
out vec2 TexCoords;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f); 
	float strength = 0.01;
	gl_Position.x += cos(time * 10) * strength;        
	gl_Position.y += cos(time * 15) * strength;    
    TexCoords = texCoords;
}  