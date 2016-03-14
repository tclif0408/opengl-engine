#pragma once

#include <string>

#include <GL/glew.h>

namespace Proj42
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		void linkShaders();
		void addAttribute(const std::string& attribName);
		void use();
		void unuse();
		GLint getUniformLocation(const std::string& uniformName);

	private:
		void compileShader(const std::string& filePath, GLuint id);

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		int _numAttributes;
	};
};
