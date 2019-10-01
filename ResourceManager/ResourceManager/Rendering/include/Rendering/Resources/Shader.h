#pragma once

#include <string_view>
#include <Rendering/Export.h>
#include <unordered_map>
#include <Rendering/LowRenderer/Light.h>


namespace Rendering::Resources
{
    class API_RENDERING Shader
    {
    public:

        Shader() = delete;

        /** 
         * Use this constructor for a custom shader.
         * @param p_vertexFilepath
         * @param p_fragmentFilepath
         */
        Shader(const std::string& p_vertexFilepath,
               const std::string& p_fragmentFilepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;
		void SetUniform3f(const std::string& p_name, const float p_v0, const float p_v1, const float p_v2);
       
    	// utility uniform functions
        void SetBool(const std::string& p_name, const bool p_value) const;
        void SetInt(const std::string& p_name, const int p_value) const;
        void SetFloat(const std::string& p_name, const float p_value) const;
        void SetUniform4f(const std::string& p_name, const float p_v0,
                          const float        p_v1, const float   p_v2,
                          const float        p_v3);

		void SetUniformMatrix4fv(const std::string& p_name, const glm::mat4& p_matrix);

		void RecompileShader();

    private:
        [[nodiscard]] GLuint CompileShader(const GLuint           p_type,
                                           const std::string& p_source) const;

        int GetUniformLocation(const std::string& p_name);

        [[nodiscard]] std::string ShaderProgramSource(
            const std::string_view& p_filepath) const;

        GLuint m_id{0u};
		std::string m_sourceVertexShader;
		std::string m_sourceFragmentShader;
		std::unordered_map<std::string, GLint> m_uniformLocationCache;
    };
}
