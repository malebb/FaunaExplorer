#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& t_vertexPath, const std::string& t_fragmentPath)
{
	// vertex shader
	std::fstream vertexFile(t_vertexPath);
	if (!vertexFile.is_open())
		std::cerr << "Error: vertex shader file could not be opened" << std::endl;
	std::stringstream vertexSS;
	vertexSS << vertexFile.rdbuf();
	std::string vertexSource = vertexSS.str();

	const char* vertexCode = vertexSource.c_str();
	const int vertexLength = vertexSource.length();

	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexCode, &vertexLength);

	int compilationSuccess = 0;
	char log[512];

	glCompileShader(vertexShaderId);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compilationSuccess);
	if (!compilationSuccess)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, log);
		std::cerr << "vertex shader compilation failed :" << log << std::endl;
	}

	// fragment shader
	std::fstream fragmentFile(t_fragmentPath);
	if (!fragmentFile.is_open())
		std::cerr << "Error: fragment shader file could not be opened" << std::endl;
	std::stringstream fragmentSS;
	fragmentSS << fragmentFile.rdbuf();
	std::string fragmentSource = fragmentSS.str();

	const char* fragmentCode = fragmentSource.c_str();
	const int fragmentLength = fragmentSource.length();

	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentCode, &fragmentLength);

	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &compilationSuccess);
	if (!compilationSuccess)
	{
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, log);
		std::cerr << "fragment shader compilation failed :" << log << std::endl;
	}

	// program
	m_id = glCreateProgram();

	glAttachShader(m_id, vertexShaderId);
	glAttachShader(m_id, fragmentShaderId);

	glLinkProgram(m_id);
	int linkSucceed = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &linkSucceed);
	if (!linkSucceed)
	{
		glGetProgramInfoLog(m_id, 512, NULL, log);
		std::cerr << "program link failed :" << log << std::endl;
	}
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

void Shader::use() const
{
	glUseProgram(m_id);
}

void Shader::deleteProgram() const
{
	glDeleteProgram(m_id);
}

void Shader::setMat4(const std::string& t_name, glm::mat4& t_mat)
{
	GLint location = glGetUniformLocation(m_id, t_name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(t_mat));
}

void Shader::setInt(const std::string& t_name, GLint t_value)
{
	GLint location = glGetUniformLocation(m_id, t_name.c_str());
	glUniform1i(location, t_value);
}