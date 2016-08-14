#include "CircleShader.h"

namespace Engine2d {
	const char *circleVert = MULTI_LINE_STRING(
		#version 330 core\n

		layout(location = 0) in vec2 position;
		layout(location = 1) in vec2 uv;
		uniform mat4 model;
		uniform vec4 uvTransform;
		uniform mat4 projection;
		out vec2 fragPosition;
		out vec2 UV;

		void main() {
			gl_Position = projection * model * vec4(position.xy, 0.0, 1.0);
			fragPosition = position;
			UV = (uv * uvTransform.zw) + uvTransform.xy;
		}
	);

	const char *circleFrag = MULTI_LINE_STRING(
		#version 330 core\n

		out vec4 color;
		uniform sampler2D texture1;
		uniform vec4 spriteColor;
		uniform int emptyTexture;
		in vec2 fragPosition;
		in vec2 UV;

		void main()
		{
			float dist = distance(vec2(0.5f, 0.5f), fragPosition);
			float delta = fwidth(dist);
			float alpha = smoothstep(0.5f - delta, 0.5f, dist);
			color = spriteColor * vec4(1, 1, 1, 1 - alpha);

			if (emptyTexture == 1) {
				color = spriteColor * vec4(1, 1, 1, 1 - alpha);
			}
			else {
				vec4 texColor = texture(texture1, UV);
				color = spriteColor * vec4(1, 1, 1, 1 - alpha) * texColor;
			}
		}
	);



	CircleShader::CircleShader()
	{
		AttachShader(circleVert, GL_VERTEX_SHADER);
		AttachShader(circleFrag, GL_FRAGMENT_SHADER);
		Link();
	}

}