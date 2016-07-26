#include "GrayScaleShader.h"

namespace Engine2d
{
	const char *grayVert = MULTI_LINE_STRING(
		#version 330 core\n
		layout(location = 0) in vec2 position;
		layout(location = 1) in vec2 texCoords;

		uniform float time;
		out vec2 TexCoords;

		void main()
		{
			gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
			TexCoords = texCoords;
		}
	);

	const char *grayFrag = MULTI_LINE_STRING(
		#version 330 core\n
		in vec2 TexCoords;
		out vec4 color;

		uniform sampler2D screenTexture;

		void main()
		{
			vec4 tex = texture(screenTexture, TexCoords);
			float avg = (tex.r + tex.g + tex.b) / 3;
			color = vec4(avg, avg, avg, tex.a);
		}
	);

	GrayScaleShader::GrayScaleShader()
	{
		AttachShader(grayVert, GL_VERTEX_SHADER);
		AttachShader(grayFrag, GL_FRAGMENT_SHADER);
		Link();
	}
}