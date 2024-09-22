#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &m_id);
}

void VAO::bind() const
{
    glBindVertexArray(m_id);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}

void VAO::linkVBO(VBO& t_vbo) const
{
    t_vbo.bind();

    // vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // textures coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    t_vbo.unbind();
}

void VAO::deleteBuf() const
{
    glDeleteBuffers(1, &m_id);
}