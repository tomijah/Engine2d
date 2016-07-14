#include "Shader.h"
#include "FileReader.h"
#include <vector>

namespace Engine2d
{
	GLuint CreateShader(const std::string& code, GLenum shaderType);

	Shader::Shader(const std::string &name)
	{
		std::string vertex;
		std::string fragment;
		//std::string geo;
		FileReader::readTextFile(name + ".vert", vertex);
		FileReader::readTextFile(name + ".frag", fragment);
	//	FileReader::readTextFile(name + ".geom", geo);
		Program = glCreateProgram();
		_shaders[0] = CreateShader(vertex, GL_VERTEX_SHADER); 
		_shaders[1] = CreateShader(fragment, GL_FRAGMENT_SHADER);
	//	_shaders[2] = CreateShader(fragment, GL_GEOMETRY_SHADER);

		glAttachShader(Program, _shaders[0]);
		glAttachShader(Program, _shaders[1]);
		//glAttachShader(Program, _shaders[2]);

		glLinkProgram(Program);

		glDetachShader(Program, _shaders[0]);
		glDetachShader(Program, _shaders[1]);
	//	glDetachShader(Program, _shaders[2]);

		glDeleteShader(_shaders[0]);
		glDeleteShader(_shaders[1]);
	//	glDeleteShader(_shaders[2]);
	}

	Shader::~Shader()
	{
		glDeleteProgram(Program);
	}

	void Shader::Use()
	{
		glUseProgram(Program);
	}

	void Shader::UnUse()
	{
		glUseProgram(0);
	}

	void Shader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform1f(glGetUniformLocation(this->Program, name), value);
	}
	void Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform1i(glGetUniformLocation(this->Program, name), value);
	}
	void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform2f(glGetUniformLocation(this->Program, name), x, y);
	}
	void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform2f(glGetUniformLocation(this->Program, name), value.x, value.y);
	}
	void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform3f(glGetUniformLocation(this->Program, name), x, y, z);
	}
	void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform3f(glGetUniformLocation(this->Program, name), value.x, value.y, value.z);
	}
	void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform4f(glGetUniformLocation(this->Program, name), x, y, z, w);
	}
	void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniform4f(glGetUniformLocation(this->Program, name), value.x, value.y, value.z, value.w);
	}
	void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
	{
		if (useShader)
			this->Use();
		glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}



	static	GLuint CreateShader(const std::string& code, GLenum shaderType) {
		
		GLuint id = glCreateShader(shaderType);
		const GLchar* source[1];
		source[0] = code.c_str();

		glShaderSource(id, 1, source, nullptr);

		glCompileShader(id);
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
			glDeleteShader(id);
			std::cerr << &(errorLog[0]) << std::endl;
		}

		return id;
	}
}