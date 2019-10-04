#pragma once

#include <vector>
#include <glm/glm.hpp>

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
        * @return bool will be true if all vectors were filled with at least one information.
        */
        static bool ReadAndStoreRawData(const std::string&&      p_path,
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

        enum GeometryState
        {
            TRIANGLES = 2,
            QUAD = 3,
            POLY = 5,
            OTHER = 0
        };

        //Determines whether we have a triangle or a quad/poly
		static unsigned int AnalyseFaceComposition(const std::string& p_line);
        //reads v, vt and vn lines and arranges their data.
		static glm::vec3 LoadData(const std::string& p_firstWord, const std::string& p_line);
        //reads face lines and arranges their data.
		static glm::vec3 LoadTriangulatedFaces(const std::string& p_line, const int p_offset);
        //takes a Quad and makes it into a Triangle.
		static std::pair<glm::vec3, glm::vec3> TriangulateQuad(const std::string& p_line, const int p_offset);
    };
}
