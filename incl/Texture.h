#pragma once

#include <string>

class Texture
{

public:

	Texture(const std::string& t_path, const std::string& t_type);
	void use();
	const std::string& getType() const;
    unsigned int getId() const;

private:

	unsigned int m_id;
	std::string m_type;
};