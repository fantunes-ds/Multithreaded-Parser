#pragma once
#include <Rendering/Managers/Renderer.h>
#include <Core/GameObject.h>
#include <unordered_map>
#include <Rendering/LowRenderer/Camera.h>

namespace Core
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;
		Scene(const Scene& p_other);

		void AddGameObject(std::shared_ptr<GameObject> p_gameObject, const std::string& p_name);
		std::shared_ptr<Core::GameObject> FindGameObject(const std::string& p_name);
		void DrawAll(Rendering::Managers::Renderer& p_renderer);

		void Update();
		void UpdateAllGameObjects();
		void UpdateAllComponents();
		void UpdateAllShaders();
		void RecompileAllShaders();

		std::unordered_map<std::string, std::shared_ptr<GameObject>>& GetAllGameObjects();

	private:
		std::unordered_map<std::string, std::shared_ptr<GameObject>> m_allGameObjects{};
	};
}
