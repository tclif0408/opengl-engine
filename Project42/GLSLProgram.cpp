#include "Errors.h"
#include "GLSLProgram.h"

#include <fstream>
#include <vector>

using namespace Proj42;

GLSLProgram::GLSLProgram() :
	_programID(0),
	_vertexShaderID(0),
	_fragmentShaderID(0),
	_numAttributes(0)
{	
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	_programID = glCreateProgram();							// create program and store its id
	
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);		// create vertex shader & store its id
	if (_vertexShaderID == 0)
		fatalError("Couldn't create vertex shader! :(");
		
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);	// create fragment shader & store its id
	if (_fragmentShaderID == 0)
		fatalError("Couldn't create fragment shader! :(");

	// compile shaders
	compileShader(vertexShaderPath, _vertexShaderID);
	compileShader(fragmentShaderPath, _fragmentShaderID);
}

// 'borrowed' from opengl.org wiki
void GLSLProgram::linkShaders()
{	
	// Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		// print the error log
		std::printf("%s\n", &errorLog[0]);
		fatalError("Failed to link shaders. :(");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);

	// you should probably delete them too.
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::compileShader(const std::string & filePath, GLuint id)
{
	// load vertex shader source
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail())
	{
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line))
		fileContents += line + "\n";

	shaderFile.close();

	// compile vertex shader
	const char* sourcePtr = fileContents.c_str();
	glShaderSource(id, 1, &sourcePtr, nullptr);

	glCompileShader(id);

	// check that the vertex shader was compiled successfully
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// maxlen includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// exit with failure
		glDeleteShader(id);						// don't leak the shader
		std::printf("%s\n", &errorLog[0]);		// print error log
		fatalError("Failed to compile shader! :(\nFilepath: " + filePath);
	}
}

void GLSLProgram::addAttribute(const std::string & attribName)
{
	glBindAttribLocation(_programID, _numAttributes++, attribName.c_str());	// increment _numAttributes with postfix operator
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
		glEnableVertexAttribArray(i);
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
		glDisableVertexAttribArray(i);
}

GLint GLSLProgram::getUniformLocation(const std::string & uniformName)
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
		fatalError("Uniform " + uniformName + " not found in shader! D:");
	return location;
}
