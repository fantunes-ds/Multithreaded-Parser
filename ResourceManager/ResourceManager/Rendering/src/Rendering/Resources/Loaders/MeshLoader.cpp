#include <stdafx.h>
#include <Rendering/Resources/Loaders/MeshLoader.h>


bool Rendering::Resources::Loaders::MeshLoader::Destroy(Mesh*& p_meshInstanceReference) noexcept
{
	if (p_meshInstanceReference != nullptr)
	{
		delete p_meshInstanceReference;
		p_meshInstanceReference = nullptr;

		return true;
	}
	return false;
}
