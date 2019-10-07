#pragma once

#include <string>
#include <memory>

#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/Shader.h>

#include <Rendering/Export.h>

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

        void Bind() const noexcept;
        void Unbind() const noexcept;

        void RetryLoadModel() noexcept;
    private:
        std::string             m_directory;
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<Mesh>   m_mesh;
		std::string m_meshPath;

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
