#include "Model.h"

#include <iostream>

Model::Model(const std::string& t_path)
{
	loadModel(t_path);
}

void Model::loadModel(const std::string& t_path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(t_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error: Assimp : " << importer.GetErrorString() << std::endl;
		return;
	}
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* t_node, const aiScene * t_scene)
{

	for (unsigned int i = 0; i < t_node->mNumMeshes; ++i)
	{
		aiMesh* mesh = t_scene->mMeshes[t_node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, t_scene));
	}

	for (unsigned int i = 0; i < t_node->mNumChildren; ++i)
	{
		processNode(t_node->mChildren[i], t_scene);
	}
}

Mesh Model::processMesh(aiMesh* t_mesh, const aiScene* t_scene)
{
	std::vector<Vertex>			vertices;
	std::vector<Texture>		textures;
	std::vector<unsigned int>	indices;

	// vertices
	for (unsigned int i = 0; i < t_mesh->mNumVertices; ++i)
	{
		Vertex vertex;

		vertex.position.x = t_mesh->mVertices[i].x;
		vertex.position.y = t_mesh->mVertices[i].y;
		vertex.position.z = t_mesh->mVertices[i].z;

		if (t_mesh->HasNormals())
		{
			vertex.normal.x = t_mesh->mNormals[i].x;
			vertex.normal.y = t_mesh->mNormals[i].y;
			vertex.normal.z = t_mesh->mNormals[i].z;
		}

		if (t_mesh->mTextureCoords[0])
		{
			vertex.textureCoord.x = t_mesh->mTextureCoords[0][i].x;
			vertex.textureCoord.y = t_mesh->mTextureCoords[0][i].y;
		}
		else
			vertex.textureCoord = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}

	// indices
	for (unsigned int i = 0; i < t_mesh->mNumFaces; ++i)
	{
		for (unsigned int j = 0; j < t_mesh->mFaces[i].mNumIndices; ++j)
		{
			indices.push_back(t_mesh->mFaces[i].mIndices[j]);
		}
	}

	if (t_mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = t_scene->mMaterials[t_mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, textures, indices);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* t_material, aiTextureType t_type, const std::string& t_typeName)
{
	std::vector<Texture> textures;

	unsigned int numTex = t_material->GetTextureCount(t_type);

	for (unsigned int i = 0; i < t_material->GetTextureCount(t_type); ++i)
	{
		aiString path;
		t_material->GetTexture(t_type, i, &path);
		Texture texture(path.C_Str(), t_typeName);
		textures.push_back(texture);
	}
	return textures;
}

void Model::draw(Shader& t_shader)
{
	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].draw(t_shader);
	}
}