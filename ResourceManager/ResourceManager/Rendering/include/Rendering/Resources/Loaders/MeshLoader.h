#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>

namespace Rendering::Resources::Loaders
{
	class API_RENDERING MeshLoader
	{
	public:
		MeshLoader() = delete;
		~MeshLoader() = delete;

		//static Mesh* Load(const std::string& p_filePath); // with ASSIMP
		static bool Destroy(Mesh*& p_meshInstanceReference) noexcept;
	};
}
