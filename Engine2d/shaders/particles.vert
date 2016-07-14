#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 particle;
uniform mat4 model;
uniform mat4 projection;
out vec2 UV;
out float ttl;

void main() {
    gl_Position = projection * vec4(position.xy + particle.xy, 0.0, 1.0);
	UV = uv;
	ttl = particle.z;
}
