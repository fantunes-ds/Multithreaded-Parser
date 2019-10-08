#include <stdafx.h>

#include <fstream>
#include <sstream>

#include <Rendering/Resources/ParserOBJ.h>

bool Rendering::Resources::ParserOBJ::ReadAndStoreRawData(const std::string&& p_path,
    std::vector<glm::vec3>& p_rawVertexPos, std::vector<glm::vec2>& p_rawUVs,
    std::vector<glm::vec3>& p_rawNormals, std::vector<uint32_t>& p_rawIndices)
{
    std::ifstream file{p_path};
    if (!file)
    {
        std::cout << "[MODEL] No obj.file at this path : " <<
                p_path << "\nPlease make sure you typed the address correctly\n";
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.substr(0,2) == "v ")
        {
            p_rawVertexPos.push_back(LoadData(line));
        }

        else if (line.substr(0,2) == "vt")
        {
            p_rawUVs.emplace_back(LoadData(line));
        }

        else if (line.substr(0,2) == "vn")
        {
            p_rawNormals.push_back(LoadData(line));
        }

		else if (line.substr(0, 2) == "f ")
		{
			LoadFaces(line, p_rawIndices);
		}
    }
	if (!p_rawVertexPos.empty() && !p_rawUVs.empty() && !p_rawNormals.empty())
		return true;
	else
		return false;
}


glm::vec3 Rendering::Resources::ParserOBJ::LoadData(const std::string& p_line)
{
	glm::vec<3, float> values{};

    //format is v or vt or vn and the three data relative to it
	std::string format{ p_line.substr(0,2) };
	format.append("%f %f %f");
    sscanf_s(p_line.c_str(),format.c_str(), &values.x, &values.y, &values.z);

	return values;
}

void Rendering::Resources::ParserOBJ::LoadFaces(const std::string& p_line, std::vector<uint32_t>& p_rawIndices)
{
	GLuint data1{ 0 },  data2{ 0 },  data3{ 0 },
           data4{ 0 },  data5{ 0 },  data6{ 0 },
           data7{ 0 },  data8{ 0 },  data9{ 0 },
           data10{ 0 }, data11{ 0 }, data12{ 0 };

    //sscan_f will fill only what he finds -> if he finds 9 data, he will fill 9 data, if he finds 12, he will fill 12.
    const unsigned int count = sscanf_s(p_line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", 
		                                                                &data1, &data2, &data3,
		                                                                &data4, &data5, &data6,
		                                                                &data7, &data8, &data9,
		                                                                &data10, &data11, &data12);

    //if face is a triangle
	if (count >= 9)
	{
		p_rawIndices.emplace_back(data1); p_rawIndices.emplace_back(data4); p_rawIndices.emplace_back(data7);
        p_rawIndices.emplace_back(data2); p_rawIndices.emplace_back(data5);	p_rawIndices.emplace_back(data8);
		p_rawIndices.emplace_back(data3); p_rawIndices.emplace_back(data6);	p_rawIndices.emplace_back(data9);
	}
    //if face is a quad, we add one triangle with the new point
	if (count >= 12)
	{
		p_rawIndices.emplace_back(data7); p_rawIndices.emplace_back(data10); p_rawIndices.emplace_back(data1);
		p_rawIndices.emplace_back(data8); p_rawIndices.emplace_back(data11); p_rawIndices.emplace_back(data2);
		p_rawIndices.emplace_back(data9); p_rawIndices.emplace_back(data12); p_rawIndices.emplace_back(data3);
    }
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
