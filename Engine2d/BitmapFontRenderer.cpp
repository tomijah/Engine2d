#include "BitmapFontRenderer.h"
#include "TextureCache.h"
#include <sstream>
#include "FileReader.h"

namespace Engine2d
{
	BitmapFontRenderer::BitmapFontRenderer(ShaderBase * shader, Camera2d * camera)
	{
		_shader = shader;
		_camera = camera;
	}
	BitmapFontRenderer::~BitmapFontRenderer()
	{
	}

	// assume: bitmap 512x512
	void BitmapFontRenderer::Load(const std::string & fontName, float distanceChange)
	{
		distChange = distanceChange;
		std::stringstream bitmapPath;
		bitmapPath << "fonts/" << fontName << ".png";
		TextureCache::preloadTexture(bitmapPath.str().c_str(), fontName, true, false);
		_texture = TextureCache::getTexture(fontName);
		std::stringstream fontPath;
		fontPath << "fonts/" << fontName << ".fnt";
		
		std::ifstream fileStream(fontPath.str());
		std::string lineBuffer;

		if (!fileStream.is_open()) {
			std::cout << "file error: "<< fontPath.str() << std::endl;
			return;
		}

		while (fileStream.good()) {
			std::getline(fileStream, lineBuffer);

			parseLine(lineBuffer);
		}

		fileStream.close();

		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * BUF_SIZE, NULL, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void BitmapFontRenderer::DrawString(const std::string & text, glm::vec2 & position, float scale, glm::vec4 color, float lineHeight)
	{
		int count = 0;
		glm::vec2 carret = glm::vec2(0.0f);
		for (int si = 0; text[si] != 0; si++) {
			GLchar c = text[si];
			Glyph * glyph = &_glyphs[c];
			if (c == ' ') {
				carret.x += glyph->advance + distChange;
				continue;
			}

			if (c == 10) {
				carret.y += lineHeight;
				carret.x = 0;
			}

			buffer[count++] = carret.x + glyph->bottomLeft.x;
			buffer[count++] = carret.y + glyph->bottomLeft.y;
			buffer[count++] = glyph->bottomLeft.z;
			buffer[count++] = glyph->bottomLeft.w;

			buffer[count++] = carret.x + glyph->bottomRight.x;
			buffer[count++] = carret.y + glyph->bottomRight.y;
			buffer[count++] = glyph->bottomRight.z;
			buffer[count++] = glyph->bottomRight.w;

			buffer[count++] = carret.x + glyph->topLeft.x;
			buffer[count++] = carret.y + glyph->topLeft.y;
			buffer[count++] = glyph->topLeft.z;
			buffer[count++] = glyph->topLeft.w;

			buffer[count++] = carret.x + glyph->topRight.x;
			buffer[count++] = carret.y + glyph->topRight.y;
			buffer[count++] = glyph->topRight.z;
			buffer[count++] = glyph->topRight.w;

			carret.x += glyph->advance + distChange;
		}

		glm::mat4 model;
		model = glm::scale(model, glm::vec3(scale));
		_shader->SetMatrix4("model", model);
		_shader->SetVector2f("position", position);
		_shader->SetVector4f("spriteColor", color);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(GLfloat), buffer);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, count / 4);
		glBindVertexArray(0);
	}

	void BitmapFontRenderer::Start()
	{
		_shader->Use();
		glActiveTexture(GL_TEXTURE0);
		_texture->Bind();
		_shader->SetMatrix4("projection", _camera->getProjectionMatrix());
	}

	void BitmapFontRenderer::Stop()
	{
	}

	void BitmapFontRenderer::parseLine(std::string & line)
	{
		if (line.find("char ") == 0) {
			Glyph gl;
			GLfloat x = std::stof(line.substr(16, 3));
			GLfloat y = std::stof(line.substr(23, 3));
			GLfloat width = std::stof(line.substr(34, 3));
			GLfloat height = std::stof(line.substr(46, 3));
			GLfloat offsetX = std::stof(line.substr(59, 3));
			GLfloat offsetY = std::stof(line.substr(72, 3));

			gl.bottomLeft.x = 0.0f + offsetX;
			gl.bottomLeft.y = height + offsetY;
			gl.bottomLeft.z = x / (float)bitmapWidth;
			gl.bottomLeft.w = y / (float)bitmapHeight + height / (float)bitmapHeight;

			gl.bottomRight.x = width + offsetX;
			gl.bottomRight.y = height + offsetY;
			gl.bottomRight.z = x / (float)bitmapWidth + width / (float)bitmapWidth;
			gl.bottomRight.w = y / (float)bitmapHeight + height / (float)bitmapHeight;

			gl.topLeft.x = 0.0f + offsetX;
			gl.topLeft.y = 0.0f + offsetY;
			gl.topLeft.z = x / (float)bitmapWidth;
			gl.topLeft.w = y / (float)bitmapHeight;

			gl.topRight.x = width + offsetX;
			gl.topRight.y = 0.0f + offsetY;
			gl.topRight.z = x / (float)bitmapWidth + width / (float)bitmapWidth;
			gl.topRight.w = y / (float)bitmapHeight;

			gl.advance = std::stof(line.substr(86, 3));

			GLchar ch = std::stoi(line.substr(8, 3));
			_glyphs.insert(std::pair<GLchar, Glyph>(ch, gl));
		}
	}
	
}