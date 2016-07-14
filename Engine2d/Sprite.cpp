#include "Sprite.h"

namespace Engine2d
{
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
	{
		_texture = texture;
		GLfloat vertices[] = {
			x, height-y, 0.0f, 0.0f,
			x + width, y, 1.0f, 1.0f,
			x,  y, 0.0f, 1.0f,
			x, height-y , 0.0f, 0.0f,
			x + width, height - y, 1.0f, 0.0f,
			x + width, y, 1.0f, 1.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void Sprite::Draw()
	{
		glActiveTexture(GL_TEXTURE0);
		_texture->Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

}