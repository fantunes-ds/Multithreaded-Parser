#include <stdafx.h>

#include <fstream>
#include <sstream>

#include <Rendering/Resources/Model.h>
#include <Rendering/Geometry/Vertex.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include "Rendering/LowRenderer/Camera.h"


Rendering::Resources::Model::Model(const std::string& p_path) noexcept
{
	LoadModel(p_path);
	LoadShader();
}

Rendering::Resources::Model::Model(const std::string& p_modelPath,
	const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	LoadModel(p_modelPath);
	LoadShader(p_vertexFilepath.c_str(), p_fragmentFilepath);
}

Rendering::Resources::Model::Model(const Model& p_other) noexcept
{
	m_directory = p_other.m_directory;
	m_mesh = p_other.m_mesh;
	m_shader = p_other.m_shader;
}

void Rendering::Resources::Model::AddTexture(const std::string& p_texturePath) const
{
	m_mesh->AddTexture(p_texturePath);
}

void Rendering::Resources::Model::LoadModel(const std::string& p_path) noexcept
{

	//std::ifstream file{ p_path };
	//if (!file)
	//{
	//	std::cout << "[MODEL] No obj.file at this path : " <<
	//		p_path << "\nPlease make sure you typed the address correctly\n";
	//	return;
	//}

 //   std::string line;

	//std::vector<Geometry::Vertex> vertices;
	//std::vector<uint32_t> indices;

 //   glm::vec3 positions{};
	//glm::vec2 uvs{};
	//glm::vec3 normals{};

	//while (std::getline(file, line))
	//{
	//	bool isGeometry = false;
	//	std::stringstream firstWord{};
 //       
	//	for (char c : line)
	//	{
	//		if (c != ' ')
	//			firstWord << c;
	//		else
	//			break;
	//	}

	//	if (firstWord.str() == "v")
	//	{
	//		isGeometry = true;
 //           positions = LoadData(firstWord.str(), line);
	//	}

	//	else if (firstWord.str() == "vt")
	//	{
	//		uvs = LoadData(firstWord.str(), line);
	//	}

	//	else if (firstWord.str() == "vn")
	//	{
	//		normals = LoadData(firstWord.str(), line);
	//	}

	//	else if (firstWord.str() == "f")
	//	{
	//		glm::vec3 face {LoadFaces(line)};
	//		indices.emplace_back(static_cast<GLuint>(face.x));
	//		indices.emplace_back(static_cast<GLuint>(face.y));
	//		indices.emplace_back(static_cast<GLuint>(face.z));
	//	}

 //       if(isGeometry)
 //       {
	//		Geometry::Vertex tempVert{ positions, uvs, normals };
	//		vertices.push_back(tempVert);
 //       }
	//}
	//std::cout << '\n';

	//Create a new mesh and add it to the vector

	std::ifstream file{ p_path };
	if (!file)
	{
		std::cout << "[MODEL] No obj.file at this path : " <<
			p_path << "\nPlease make sure you typed the address correctly\n";
		return;
	}

	std::string line;

	std::vector<Geometry::Vertex> vertices;
	std::vector<uint32_t> rawIndices;

	std::vector<glm::vec3> rawVertPos{};
	std::vector<glm::vec2> rawUVs{};
	std::vector<glm::vec3> rawNormals{};

	while (std::getline(file, line))
	{
		std::stringstream firstWord{};

		for (char c : line)
		{
			if (c != ' ')
				firstWord << c;
			else
				break;
		}

		if (firstWord.str() == "v")
		{
			rawVertPos.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "vt")
		{
			rawUVs.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "vn")
		{
			rawNormals.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "f")
		{
			for (int i = 0; i < 3; i++)
			{
				glm::vec3 face{ LoadFaces(line, i) };
				rawIndices.emplace_back(static_cast<GLuint>(face.x));
				rawIndices.emplace_back(static_cast<GLuint>(face.y));
				rawIndices.emplace_back(static_cast<GLuint>(face.z));
			}
		}

	}



	std::cout << "building object. There are " << rawVertPos.size() << " positions, " << rawUVs.size() << " uvs, " << rawNormals.size() << " normals" << '\n';

	std::vector<uint32_t> rawVertexIndices;
	std::vector<uint32_t> realVertexIndices;
	for (unsigned int i = 0; i < rawIndices.size(); i += 9)
	{
		rawVertexIndices.push_back(rawIndices[i]);
		rawVertexIndices.push_back(rawIndices[i+1]);
		rawVertexIndices.push_back(rawIndices[i+2]);
		realVertexIndices.push_back(rawIndices[i] - 1);
		realVertexIndices.push_back(rawIndices[i + 1] - 1);
		realVertexIndices.push_back(rawIndices[i + 2] - 1);
	}
    std::vector<uint32_t> rawUVIndices;
	for (unsigned int i = 3; i < rawIndices.size(); i += 9)
	{
		rawUVIndices.push_back(rawIndices[i]);
		rawUVIndices.push_back(rawIndices[i+1]);
		rawUVIndices.push_back(rawIndices[i+2]);
	}
    std::vector<uint32_t> rawNormalIndices;
	for (unsigned int i = 6; i < rawIndices.size(); i += 9)
	{
		rawNormalIndices.push_back(rawIndices[i]);
		rawNormalIndices.push_back(rawIndices[i+1]);
		rawNormalIndices.push_back(rawIndices[i+2]);
	}
 //   for (unsigned int i = 0 ; i < vertexIndices.size(); i++)
	//{
	//	std::cout << "Vertex[" << i << "]\n";
	//	std::cout << "v : " << positions[vertexIndices[i]].x << ' ' << positions[vertexIndices[i]].y << ' ' << positions[vertexIndices[i]].z <<'\n';
	//	std::cout << "vt : " << uvs[textureIndices[i]].x << ' ' << uvs[textureIndices[i]].y << '\n';
	//	std::cout << "vn : " << normals[normalIndices[i]].x << ' ' << normals[normalIndices[i]].y << ' ' << normals[normalIndices[i]].z << '\n';

	//	/*Geometry::Vertex tempVert{ positions[vertexIndices[i]], uvs[textureIndices[i]], normals[normalIndices[i]] };
	//	vertices.push_back(tempVert);*/
	//}
	std::cout << '\n';

	for (unsigned int i = 0; i < rawVertexIndices.size(); i++)
	{
		Geometry::Vertex tempvert{ rawVertPos[rawVertexIndices[i] - 1], rawUVs[rawUVIndices[i] - 1], rawNormals[rawNormalIndices[i] - 1] };
		vertices.push_back(tempvert);
	}

	std::vector<uint32_t> realIndices;
	for (unsigned int i = 0; i < rawIndices.size(); i++)
		realIndices.push_back(rawIndices[i] - 1);

	std::vector<uint32_t> fakePosIndices;
	for (int i = 0; i < rawIndices.size(); i++)
		fakePosIndices.push_back(i);



	/*for (unsigned int i = 0; i < rawVertPos.size(); i++) 
	{
		unsigned int vertexIndex = rawVertexIndices[i];
		glm::vec3 vertex = rawVertPos[vertexIndex - 1];
		unsigned int texIndex = rawTextureIndices[i];
		glm::vec2 tex = rawUVs[texIndex - 1];
		unsigned int nmIndex = rawNormalIndices[i];
		glm::vec3 nm = rawNormals[nmIndex - 1];

		vertices.emplace_back(rawVertPos[i], tex, nm);
	}*/

	m_mesh = std::make_shared<Mesh>(vertices, fakePosIndices);
}

glm::vec3 Rendering::Resources::Model::LoadData(const std::string& p_firstWord,
	const std::string& p_line) const
{
	std::istringstream lineStream{ p_line };
	glm::vec3 values{};

	lineStream.ignore(p_firstWord.length());

	/*std::cout << "Parsed a line starting with " << p_firstWord;
	std::cout << lineStream.str() << '\n';*/

	lineStream >> values.x >> values.y >> values.z;
	return values;
}

glm::vec3 Rendering::Resources::Model::LoadFaces(const std::string& p_line, const int p_offset)
{
	std::stringstream noDelimStr;

	for (size_t i = 2; i < p_line.size(); ++i)
	{
		if (p_line[i] != '/')
			noDelimStr << p_line[i];
		else if (p_line[i] == '/' && p_line[i + 1] == '/')
			noDelimStr << " 0";
		else
			noDelimStr << ' ';
	}

	std::istringstream data{ noDelimStr.str() };

	std::vector<GLfloat> vertexData{};
	float p;
	while (data >> p)
		vertexData.push_back(p);

	glm::vec3 vertices{ vertexData[p_offset] , vertexData[p_offset + 3] , vertexData[p_offset + 6] };
	/*std::cout << "Face indices : "
		<< std::to_string(vertices.x) + ' '
		<< std::to_string(vertices.y) + ' '
		<< std::to_string(vertices.z);*/

	return vertices;
}

//glm::vec3 Rendering::Resources::Model::LoadFaces(const std::string& p_line)
//{
//	std::stringstream noDelimStr;
//
//	for (size_t i = 2; i < p_line.size(); ++i)
//	{
//		if (p_line[i] != '/')
//			noDelimStr << p_line[i];
//		else if (p_line[i] == '/' && p_line[i + 1] == '/')
//			noDelimStr << " 0";
//		else
//			noDelimStr << ' ';
//	}
//
//	std::istringstream data{ noDelimStr.str() };
//
//	std::vector<GLfloat> vertexData{};
//	float p;
//	while (data >> p)
//		vertexData.push_back(p);
//
//	glm::vec3 vertices{ vertexData[0] - 1.0f, vertexData[3] - 1.0f, vertexData[6] - 1.0f };
//	/*std::cout << "Face indices : "
//		<< std::to_string(vertices.x) + ' '
//		<< std::to_string(vertices.y) + ' '
//		<< std::to_string(vertices.z);*/
//
//	return vertices;
//}

void Rendering::Resources::Model::LoadShader(const std::string& p_vertexFilepath,
	const std::string& p_fragmentFilepath) noexcept
{
	m_shader = std::make_shared<Shader>(*Loaders::ShaderLoader::
		Load(p_vertexFilepath, p_fragmentFilepath));
}

void Rendering::Resources::Model::Bind() const noexcept
{
	m_mesh->Bind();
	m_shader->Bind();
}

void Rendering::Resources::Model::Unbind() const noexcept
{
	m_mesh->Unbind();
	m_shader->Unbind();
}
