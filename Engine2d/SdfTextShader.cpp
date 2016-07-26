#include "SdfTextShader.h"
#include "Utils.h"

namespace Engine2d
{
	const char *textVert = MULTI_LINE_STRING(
		#version 330 core\n

		layout(location = 0) in vec2 modelPos;
		layout(location = 1) in vec2 uv;
		uniform mat4 projection;
		uniform mat4 model;
		uniform vec2 position;
		out vec2 UV;

		void main() {
			gl_Position = projection * ((model * vec4(modelPos.xy, 0.0, 1.0)) + position);
			UV = uv;
		}
	);

	const char *textFrag = MULTI_LINE_STRING(
		#version 330 core\n

		in vec2 UV;
		out vec4 color;
		uniform sampler2D fontAtlas;
		uniform vec4 spriteColor;
		const float width = 0.5;
		const float edge = 0.15;

		void main()
		{
			vec4 texColor = texture(fontAtlas, UV);
			float dist = 1.0 - texColor.a;
			float alpha = 1.0 - smoothstep(width, width + edge, dist);
			color = spriteColor * vec4(1.0, 1.0, 1.0, alpha);
		}
	);

	SdfTextShader::SdfTextShader()
	{
		AttachShader(textVert, GL_VERTEX_SHADER);
		AttachShader(textFrag, GL_FRAGMENT_SHADER);
		Link();
	}
}