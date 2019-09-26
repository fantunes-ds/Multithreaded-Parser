#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Shader.h>
#include <string>
#include <memory>

namespace Rendering::Resources
{
    class API_RENDERING Model
    {
    public:
        Model() noexcept = default;
        Model(const std::string& p_path) noexcept;
        Model(const std::string& p_modelPath,
              const std::string& p_vertexFilepath,
              const std::string& p_fragmentFilepath) noexcept;

        Model(const Model& p_other) noexcept;

		void AddTexture(const std::string & p_texturePath) const;

        std::shared_ptr<Mesh>& GetMesh() noexcept { return m_mesh; }

        std::shared_ptr<Shader>& GetShader() noexcept { return m_shader; }

		std::shared_ptr<Texture>& GetTexture() noexcept { return m_mesh->GetTexture(); };

		glm::vec3 LoadData(const std::string& p_firstWord, const std::string& p_line) const;
		glm::vec3 LoadFaces(const std::string& p_line, const int p_offset);

        void Bind() const noexcept;
        void Unbind() const noexcept;

    private:
        std::string             m_directory;
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<Mesh>   m_mesh;

        /*  Functions   */
        void LoadModel(const std::string& path) noexcept;

        /**
         * @brief Method who can load a shader. If no parameters are send, it loads both the default vertex and fragment shader.
         * @param p_vertexFilepath : Vertex Shader to load.
         * @param p_fragmentFilepath : Fragment Shader to load.
        **/
        void LoadShader(
            const std::string& p_vertexFilepath =
                    "../rsc/shaders/defaultShader.vert",
            const std::string& p_fragmentFilepath =
                    "../rsc/shaders/defaultShader.frag") noexcept;
    };
}
