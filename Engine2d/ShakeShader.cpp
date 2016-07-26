#include "ShakeShader.h"

namespace Engine2d
{
	const char *shakeVert = MULTI_LINE_STRING(
		#version 330 core\n
		layout(location = 0) in vec2 position;
		layout(location = 1) in vec2 texCoords;

		uniform float time;
		out vec2 TexCoords;

		void main()
		{
			gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
			float strength = 0.02;
			gl_Position.x += cos(time * 10) * strength;
			gl_Position.y += cos(time * 15) * strength;
			TexCoords = texCoords;
		}
	);

	const char *shakeFrag = MULTI_LINE_STRING(
		#version 330 core\n
		in vec2 TexCoords;
		out vec4 color;

		uniform sampler2D screenTexture;

		void main()
		{
			color = texture(screenTexture, TexCoords);
		}
	);

	ShakeShader::ShakeShader()
	{
		AttachShader(shakeVert, GL_VERTEX_SHADER);
		AttachShader(shakeFrag, GL_FRAGMENT_SHADER);
		Link();
	}
}