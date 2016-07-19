#pragma once
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

namespace Engine2d 
{
	// from http://learnopengl.com/

	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
		GLuint Advance;     // Horizontal offset to advance to next glyph
	};


	// A renderer class for rendering text displayed by a font loaded using the 
	// FreeType library. A single font is loaded, processed into a list of Character
	// items for later rendering.
	class TextRenderer
	{
	public:
		// Holds a list of pre-compiled Characters
		std::map<GLchar, Character> Characters;
		// Shader used for text rendering
		Shader TextShader;
		// Constructor
		TextRenderer(GLuint width, GLuint height);
		// Pre-compiles a list of characters from the given font
		void Load(std::string font, GLuint fontSize);
		// Renders a string of text using the precompiled list of characters
		void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color = glm::vec4(1.0f));
	private:
		// Render state
		GLuint VAO, VBO;
	};
}