#pragma once

namespace Rendering::Resources
{
    class ParserOBJ
    {
    public:
        ParserOBJ()  = delete;
        ~ParserOBJ() = delete;

        /**
        * @brief Goes through the whole file, analyses it and retrieves raw data
        * @param p_path path for the OBJ file to be Parsed
        * @param p_rawVertexPos reference for the Vertex Positions vector
        * @param p_rawUVs reference for the UV vector
        * @param p_rawNormals reference for the Normals vector
        * @param p_rawIndices reference for the Indices vector
        */
        static bool ReadAndStoreRawData(const std::string&      p_path,
                                        std::vector<glm::vec3>& p_rawVertexPos,
                                        std::vector<glm::vec2>& p_rawUVs,
                                        std::vector<glm::vec3>& p_rawNormals,
                                        std::vector<uint32_t>&  p_rawIndices);

        /**
		* @brief Goes through all retrieved indices and creates vectors for all types of indices
		* @param p_rawVertexIndices reference for the Vertex indices vector
		* @param p_rawUVIndices reference for the UV indices vector
		* @param p_rawNormalIndices reference for the Normals indices vector
		*/
        static void ArrangeIndices(const std::vector<uint32_t>& p_rawIndices,
			                       std::vector<uint32_t>&       p_rawVertexIndices,
			                       std::vector<uint32_t>&       p_rawUVIndices,
			                       std::vector<uint32_t>&       p_rawNormalIndices);

    private:
        
        //reads v, vt and vn lines and arranges their data.
		static glm::vec3 LoadData(const std::string& p_firstWord, const std::string& p_line);
        //reads face lines and arranges their data.
		static glm::vec3 LoadFaces(const std::string& p_line, const int p_offset);
    };
}
