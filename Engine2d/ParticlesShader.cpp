#include "ParticlesShader.h"

namespace Engine2d
{
	const char *particlesVert = MULTI_LINE_STRING(
		#version 330 core\n
		layout(location = 0) in vec2 position;
		layout(location = 1) in vec2 uv;
		layout(location = 2) in vec3 particle;
		uniform mat4 model;
		uniform mat4 projection;
		out vec2 UV;
		out float ttl;

		void main() {
			gl_Position = projection * vec4(position.xy + particle.xy, 0.0, 1.0);
			UV = uv;
			ttl = particle.z;
		}
	);

	const char *particlesFrag = MULTI_LINE_STRING(
		#version 330 core\n
		in vec2 UV;
		in float ttl;
		out vec4 color;
		uniform sampler2D texture1;
		uniform vec3 spriteColor;
		uniform float maxTtl;

		void main()
		{
			vec4 texColor = texture(texture1, UV);
			color = vec4(spriteColor, ttl / maxTtl) * texColor;
		}
	);

	ParticlesShader::ParticlesShader()
	{
		AttachShader(particlesVert, GL_VERTEX_SHADER);
		AttachShader(particlesFrag, GL_FRAGMENT_SHADER);
		Link();
	}
}