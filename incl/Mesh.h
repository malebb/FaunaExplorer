#pragma once

#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

struct Vertex
{
	glm::vec3		position;
	glm::vec3		normal;
	glm::vec2		textureCoord;
};

class Mesh
{

public:

	Mesh(const std::vector<Vertex>& t_vertices,
		const std::vector<Texture>& t_textures,
		const std::vector<unsigned int>& t_indices);
	void draw(Shader& t_shader);

private:

	std::vector<Vertex>			m_vertices;
	std::vector<Texture>		m_textures;
	std::vector<unsigned int>	m_indices;

	VAO							m_VAO;
	VBO							m_VBO;
	EBO							m_EBO;

	void setupMesh();
};