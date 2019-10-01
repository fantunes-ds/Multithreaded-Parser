#include <stdafx.h>
#include <Rendering/Resources/ParserOBJ.h>
#include <fstream>
#include <sstream>

bool Rendering::Resources::ParserOBJ::ReadAndStoreRawData(const std::string& p_path,
    std::vector<glm::vec3>& p_rawVertexPos, std::vector<glm::vec2>& p_rawUVs,
    std::vector<glm::vec3>& p_rawNormals, std::vector<uint32_t>& p_rawIndices)
{
	std::ifstream file{ p_path };
	if (!file)
	{
		std::cout << "[MODEL] No obj.file at this path : " <<
			p_path << "\nPlease make sure you typed the address correctly\n";
		return false;
	}

	std::string line;

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
			p_rawVertexPos.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "vt")
		{
			p_rawUVs.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "vn")
		{
			p_rawNormals.push_back(LoadData(firstWord.str(), line));
		}

		else if (firstWord.str() == "f")
		{
			for (int i = 0; i < 3; i++)
			{
				glm::vec3 face{ LoadFaces(line, i) };
				p_rawIndices.emplace_back(static_cast<GLuint>(face.x));
				p_rawIndices.emplace_back(static_cast<GLuint>(face.y));
				p_rawIndices.emplace_back(static_cast<GLuint>(face.z));
			}
		}

	}
	if (!p_rawVertexPos.empty() && !p_rawUVs.empty() && !p_rawNormals.empty())
		return true;
}

void Rendering::Resources::ParserOBJ::ArrangeIndices(
	const std::vector<uint32_t>& p_rawIndices,
    std::vector<uint32_t>& p_rawVertexIndices,
    std::vector<uint32_t>& p_rawUVIndices,
    std::vector<uint32_t>& p_rawNormalIndices)
{
	for (unsigned int i = 0; i < p_rawIndices.size(); i += 9)
	{
		p_rawVertexIndices.push_back(p_rawIndices[i]);
		p_rawVertexIndices.push_back(p_rawIndices[i + 1]);
		p_rawVertexIndices.push_back(p_rawIndices[i + 2]);

	    p_rawUVIndices.push_back(p_rawIndices[3 + i]);
		p_rawUVIndices.push_back(p_rawIndices[3 + i + 1]);
		p_rawUVIndices.push_back(p_rawIndices[3 + i + 2]);

	    p_rawNormalIndices.push_back(p_rawIndices[6 + i]);
		p_rawNormalIndices.push_back(p_rawIndices[6 + i + 1]);
		p_rawNormalIndices.push_back(p_rawIndices[6 + i + 2]);
	}
}

glm::vec3 Rendering::Resources::ParserOBJ::LoadData(const std::string& p_firstWord,
    const std::string& p_line)
{
	std::istringstream lineStream{ p_line };
	glm::vec3 values{};

	lineStream.ignore(p_firstWord.length());

	lineStream >> values.x >> values.y >> values.z;
	return values;
}

glm::vec3 Rendering::Resources::ParserOBJ::LoadFaces(const std::string& p_line,
    const int p_offset)
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

	return vertices;
}
