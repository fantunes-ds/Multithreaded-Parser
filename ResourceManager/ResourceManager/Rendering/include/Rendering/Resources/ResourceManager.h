#pragma once

#include <vector>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Managers/InputManager.h>

namespace Rendering::Resources
{
    class ResourceManager
    {
    public:

        void                                     AddMesh(const std::string& p_path);
        static std::unique_ptr<ResourceManager>& GetInstance();
        void                                     RemoveMesh();
		std::unordered_map<std::string, std::shared_ptr<Mesh>>& GetMeshMap() { return m_meshMap; }


    private:
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshMap;
        std::vector<std::shared_ptr<Mesh>>                     m_meshes{};
        static std::unique_ptr<ResourceManager>                m_instance;
    };
}
