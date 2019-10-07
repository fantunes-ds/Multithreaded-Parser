#pragma once

#include <vector>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Managers/InputManager.h>

namespace Rendering::Resources
{
    class ResourceManager
    {
    public:
        enum class meshStatus
		{
		    NONE,
            LOADING,
            LOADED
		};

        void                                     AddMesh(const std::string& p_path);
        static std::unique_ptr<ResourceManager>& GetInstance();
        void                                     RemoveMesh();
		std::unordered_map<std::string, std::shared_ptr<Mesh>>& GetMeshMap() { return m_meshMap; }
		std::unordered_map<std::string, meshStatus>& GetMeshMapQueue() { return m_meshMapQueue; }

    private:
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshMap;
        std::unordered_map<std::string, meshStatus> m_meshMapQueue;
        std::vector<std::shared_ptr<Mesh>>                     m_meshes{};
        static std::unique_ptr<ResourceManager>                m_instance;
    };
}
