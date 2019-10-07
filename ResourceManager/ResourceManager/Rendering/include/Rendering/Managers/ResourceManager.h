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

        std::unordered_map<std::string, std::shared_ptr<Resources::Mesh>>&
        GetMeshMap() { return m_meshMap; }

        std::unordered_map<std::string, meshStatus>& GetMeshMapStatus() { return m_meshMapStatus; }

    private:
        std::unordered_map<std::string, std::shared_ptr<Resources::Mesh>> m_meshMap;
        std::unordered_map<std::string, meshStatus> m_meshMapStatus;
        std::unordered_map<std::string, std::pair<std::shared_ptr<Resources::Mesh>, meshStatus>> m_meshMapEState;
        std::vector<std::shared_ptr<Resources::Mesh>> m_meshes{};
        static std::unique_ptr<ResourceManager>       m_instance;
    };
}
