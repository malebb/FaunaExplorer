#include "Texture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include <iostream>
#include <filesystem>

Texture::Texture(const std::string& t_path)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width;
	int height;
	int nbChannel;
	unsigned char* data = stbi_load(t_path.c_str(), &width, &height, &nbChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Error: failed to load texture : " << t_path << std::endl;
	}
	stbi_image_free(data);
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}