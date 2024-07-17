#pragma once

#include <string>

#include "glad/glad.h"

class Shader
{
public:
	Shader(const std::string& t_vertexPath, const std::string& t_fragmentPath);
	void use() const;
	void deleteProgram() const;

private:
	GLuint m_id;
};