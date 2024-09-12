#pragma once

#include "glad/glad.h"

class VBO
{

public:

	VBO(float* t_vertices, GLuint t_size);
	void bind() const;
	void unbind() const;
	void deleteBuf() const;

private:

	GLuint m_id;
};