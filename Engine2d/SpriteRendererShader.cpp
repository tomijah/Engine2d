#include "SpriteRendererShader.h"
#include "Utils.h"

namespace Engine2d
{
	const char *spriteFrag = MULTI_LINE_STRING(
		#version 330 core\n

		in vec2 UV;
		out vec4 color;
		uniform sampler2D texture1;
		uniform vec4 spriteColor;
		uniform int emptyTexture;

		void main()
		{
			if (emptyTexture == 1) {
				color = spriteColor;
			}
			else {
				vec4 texColor = texture(texture1, UV);
				color = spriteColor * texColor;
			}

		}
	);

	const char *spriteVert = MULTI_LINE_STRING(
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

	SpriteRendererShader::SpriteRendererShader()
	{
		AttachShader(spriteVert, GL_VERTEX_SHADER);
		AttachShader(spriteFrag, GL_FRAGMENT_SHADER);
		Link();
	}
}