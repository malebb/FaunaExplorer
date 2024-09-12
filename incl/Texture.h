#include <string>

class Texture
{

public:

	Texture(const std::string& t_path);
	void use();

private:

	unsigned int m_id;

};