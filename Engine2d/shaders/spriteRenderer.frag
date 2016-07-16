#version 330 core

in vec2 UV;
out vec4 color;
uniform sampler2D texture1;
uniform vec4 spriteColor;
uniform int emptyTexture;

void main()
{
	if(emptyTexture == 1){
		color = spriteColor;
	} else{
		vec4 texColor = texture(texture1, UV);
		color = spriteColor * texColor;
	}
	
} 