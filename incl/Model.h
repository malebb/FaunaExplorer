#pragma once

#include <string>

#include "Mesh.h"
#include "Shader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
class Model
{

public:

	Model(const std::string& t_path);
	void draw(Shader& t_shader);
	void processNode(aiNode* t_node, const aiScene* t_scene);
	Mesh processMesh(aiMesh* t_mesh, const aiScene* t_scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* t_material, aiTextureType t_type, const std::string& t_typeName);

private:

	std::vector<Mesh> m_meshes;

	void loadModel(const std::string& t_path);

};