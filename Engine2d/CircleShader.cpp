#include "CircleShader.h"

namespace Engine2d {
	const char *circleVert = MULTI_LINE_STRING(
		#version 330 core\n

		layout(location = 0) in vec2 position;
		layout(location = 1) in vec2 uv;
		uniform mat4 model;
		uniform mat4 projection;
		out vec2 fragPosition;

		void main() {
			gl_Position = projection * model * vec4(position.xy, 0.0, 1.0);
			fragPosition = position;
		}
	);

	const char *circleFrag = MULTI_LINE_STRING(
		#version 330 core\n

		out vec4 color;
		uniform vec4 spriteColor;
		in vec2 fragPosition;

		void main()
		{
			float dist = distance(vec2(0.5f, 0.5f), fragPosition);
			float delta = fwidth(dist);
			float alpha = smoothstep(0.5f - delta, 0.5f, dist);
			color = spriteColor * vec4(1, 1, 1, 1 - alpha);
		}
	);



	CircleShader::CircleShader()
	{
		AttachShader(circleVert, GL_VERTEX_SHADER);
		AttachShader(circleFrag, GL_FRAGMENT_SHADER);
		Link();
	}

}