#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& t_vertices,
	const std::vector<Texture>& t_textures,
	const std::vector<unsigned int>& t_indices) : m_vertices(t_vertices),
												m_textures(t_textures),
												m_indices(t_indices)
{
	setupMesh();
}

void Mesh::setupMesh()
{
	m_VAO.bind();

	VBO m_VBO(&m_vertices[0], m_vertices.size() * sizeof(Vertex));
	EBO m_EBO(&m_indices[0], m_indices.size() * sizeof(unsigned int));
	m_EBO.bind();
	m_VAO.linkVBO(m_VBO);

	m_VAO.unbind();
	m_VBO.unbind();
}

void Mesh::draw(Shader& t_shader)
{

	unsigned int diffuseNb = 1;
	unsigned int specularNb = 1;

	for (unsigned int i = 0; i < m_textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string name;
		const std::string& type = m_textures[i].getType();
		if (type == "texture_diffuse")
			name = type + std::to_string(diffuseNb++);
		else if (type == "texture_specular")
			name = type + std::to_string(specularNb++);
		t_shader.setInt(name, i);
		m_textures[i].use();
	}
	m_VAO.bind();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}
