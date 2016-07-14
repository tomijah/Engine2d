#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

vec4 textureColor(){
	return texture(screenTexture, TexCoords);
}

void main()
{ 
	color = textureColor();
}