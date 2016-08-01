#include "SdfShapeShader.h"

namespace Engine2d 
{
	const char *sdfVert = MULTI_LINE_STRING(
		#version 330 core\n

		layout(location = 0) in vec2 position;
		layout(location = 1) in vec2 uv;
		uniform mat4 model;
		uniform vec4 uvTransform;
		uniform mat4 projection;
		out vec2 UV;

		void main() {
			gl_Position = projection * model * vec4(position.xy, 0.0, 1.0);
			UV = (uv * uvTransform.zw) + uvTransform.xy;
		}
	);

	const char *sdfFrag = MULTI_LINE_STRING(
		#version 330 core\n

		in vec2 UV;
		out vec4 color;
		uniform sampler2D texture1;
		uniform vec4 spriteColor;
		uniform bool emptyTexture;
		const float width = 0.9;
		const float edge = 0.01;

		void main()
		{
			vec4 texColor = texture(texture1, UV);
			float dist = 1.0 - texColor.a;
			float alpha = 1.0 - smoothstep(width, width + edge, dist);
			color = spriteColor * vec4(texColor.rgb, alpha);
		}
	);


	SdfShapeShader::SdfShapeShader()
	{
		AttachShader(sdfVert, GL_VERTEX_SHADER);
		AttachShader(sdfFrag, GL_FRAGMENT_SHADER);
		Link();
	}
}