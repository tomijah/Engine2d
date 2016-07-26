#pragma once
#include <iostream>
#include "ShaderBase.h"
#include "Texture.h"
#include "Camera2d.h"
#include <glm/glm.hpp>
#include <map>
#include <GL/glew.h>

namespace Engine2d
{
	struct Glyph {
		glm::vec4 bottomLeft;
		glm::vec4 bottomRight;
		glm::vec4 topLeft;
		glm::vec4 topRight;
		float advance;
	};

	class BitmapFontRenderer
	{
	public:
		BitmapFontRenderer(ShaderBase * shader, Camera2d * camera);
		~BitmapFontRenderer();
		void Load(const std::string &fontName, float distanceChange = 0.0f);
		void DrawString(const std::string &text, glm::vec2 &position, float scale = 1, glm::vec4 color = glm::vec4(1.0f), float lineHeight = 0);
		void Start();
		void Stop();
	private:
		ShaderBase * _shader;
		Camera2d * _camera;
		Texture * _texture;
		void parseLine(std::string &line);
		GLuint _vao, _vbo;
		std::map<GLchar, Glyph> _glyphs;
		static const int BUF_SIZE = 1000;
		static const int bitmapWidth = 512;
		static const int bitmapHeight = 512;
		float distChange = 0.0f;
		GLfloat buffer[BUF_SIZE];
	};
}