#pragma once

#include <string>

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{

public:

	Shader(const std::string& t_vertexPath, const std::string& t_fragmentPath);
	void use() const;
	void deleteProgram() const;
	void setMat4(const std::string& t_name, glm::mat4& t_mat);
	void setInt(const std::string& t_name, GLint t_value);

private:

	GLuint m_id;
};