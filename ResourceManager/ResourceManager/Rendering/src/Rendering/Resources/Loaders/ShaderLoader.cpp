#include <stdafx.h>

#include <Rendering/Resources/Loaders/ShaderLoader.h>

Rendering::Resources::Shader* Rendering::Resources::Loaders::ShaderLoader::Load(const std::string& p_vertexFilePath, const std::string& p_fragFilePath) noexcept
{
	return new Shader(p_vertexFilePath, p_fragFilePath);
}

bool Rendering::Resources::Loaders::ShaderLoader::Destroy(Shader*& p_shaderInstanceReference) noexcept
{
	if (p_shaderInstanceReference != nullptr)
	{
		delete p_shaderInstanceReference;
		p_shaderInstanceReference = nullptr;

		return true;
	}
	return false;
}
