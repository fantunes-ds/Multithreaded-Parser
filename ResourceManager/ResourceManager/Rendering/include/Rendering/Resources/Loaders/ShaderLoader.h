#pragma once

#include <Rendering/Export.h>

#include <Rendering/Resources/Shader.h>

namespace Rendering::Resources::Loaders 
{
	class API_RENDERING ShaderLoader
	{
	public:
		ShaderLoader() = delete;
		~ShaderLoader() = delete;

		static Shader* Load(const std::string& p_vertexFilePath, const std::string& p_fragFilePath) noexcept;
		static bool Destroy(Shader*& p_shaderInstanceReference) noexcept;
	};
}
