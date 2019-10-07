#pragma once

#include <vector>

#include <Rendering/Export.h>

#include <Rendering/Resources/Mesh.h>
#include <Rendering/Managers/InputManager.h>

namespace Rendering::Managers
{
    class API_RENDERING ResourceManager
    {
    public:
        enum class meshStatus
        {
            NONE = 0,
            LOADING = 1,
            LOADED = 2
        };

        void                                     AddMesh(const std::string& p_path);
        static std::unique_ptr<ResourceManager>& GetInstance();
        void                                     RemoveMesh();

		std::unordered_map<std::string, std::pair<std::shared_ptr<Resources::Mesh>, meshStatus>>& GetMeshMap() { return m_meshMap; }

    private:
        std::unordered_map<std::string, std::pair<std::shared_ptr<Resources::Mesh>, meshStatus>> m_meshMap;
        std::vector<std::shared_ptr<Resources::Mesh>> m_meshes{};
        static std::unique_ptr<ResourceManager>       m_instance;
    };
}
