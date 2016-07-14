#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine2d
{
	class Shader
	{
	public:
		Shader(const std::string &name);
		virtual ~Shader();
		void Use();
		void UnUse();
		void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
		void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
		void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
		void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
		void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
		void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
		void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
		void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
		void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
		GLuint Program;
	private:
		static const unsigned int NUM_OF_SHADERS = 3;
		GLuint _shaders[NUM_OF_SHADERS];
	};
}
