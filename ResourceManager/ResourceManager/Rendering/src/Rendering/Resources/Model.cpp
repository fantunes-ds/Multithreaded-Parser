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
	std::vector<uint32_t> indices;

	std::vector<glm::vec3> positions{};
	std::vector<glm::vec2> uvs{};
	std::vector<glm::vec3> normals{};

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
			positions.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "vt")
		{
			uvs.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "vn")
		{
			normals.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "f")
		{
			for (int i = 0; i < 3; i++)
			{
				glm::vec3 face{ LoadFaces(line, i) };
				indices.emplace_back(static_cast<GLuint>(face.x));
				indices.emplace_back(static_cast<GLuint>(face.y));
				indices.emplace_back(static_cast<GLuint>(face.z));
			}
		}

	}



	/*std::cout << "building object. There are " << positions.size() << " positions, " << uvs.size() << " uvs, " << normals.size() << " normals" << '\n';

	std::vector<uint32_t> vertexIndices;
	for (unsigned int i = 0; i < indices.size(); i += 9)
	{
		vertexIndices.push_back(indices[i]);
		vertexIndices.push_back(indices[i+1]);
		vertexIndices.push_back(indices[i+2]);
	}
    std::vector<uint32_t> textureIndices;
	for (unsigned int i = 3; i < indices.size(); i += 9)
	{
		textureIndices.push_back(indices[i]);
		textureIndices.push_back(indices[i+1]);
		textureIndices.push_back(indices[i+2]);
	}
    std::vector<uint32_t> normalIndices;
	for (unsigned int i = 6; i < indices.size(); i += 9)
	{
		normalIndices.push_back(indices[i]);
		normalIndices.push_back(indices[i+1]);
		normalIndices.push_back(indices[i+2]);
	}
    for (unsigned int i = 0 ; i < vertexIndices.size(); i++)
	{
		std::cout << "Vertex[" << i << "]\n";
		std::cout << "v : " << positions[vertexIndices[i]].x << ' ' << positions[vertexIndices[i]].y << ' ' << positions[vertexIndices[i]].z <<'\n';
		std::cout << "vt : " << uvs[textureIndices[i]].x << ' ' << uvs[textureIndices[i]].y << '\n';
		std::cout << "vn : " << normals[normalIndices[i]].x << ' ' << normals[normalIndices[i]].y << ' ' << normals[normalIndices[i]].z << '\n';

		Geometry::Vertex tempVert{ positions[vertexIndices[i]], uvs[textureIndices[i]], normals[normalIndices[i]] };
		vertices.push_back(tempVert);
	}*/
	std::cout << '\n';

	//m_mesh = std::make_shared<Mesh>(vertices, vertexIndices);
}

glm::vec3 Rendering::Resources::Model::LoadData(const std::string& p_firstWord,
	const std::string& p_line) const
{
	std::istringstream lineStream{ p_line };
	glm::vec3 values{};

	lineStream.ignore(p_firstWord.length());

	std::cout << "Parsed a line starting with " << p_firstWord;
	std::cout << lineStream.str() << '\n';

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

	glm::vec3 vertices{ vertexData[p_offset] - 1.0f, vertexData[p_offset + 3] - 1.0f, vertexData[p_offset + 6] - 1.0f };
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
