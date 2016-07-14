#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
uniform mat4 model;
uniform vec4 uvTransform;
uniform mat4 projection;
out vec2 UV;

void main() {
    gl_Position = projection * model * vec4(position.xy, 0.0, 1.0);
	UV = (uv * uvTransform.zw) + uvTransform.xy ;
}
