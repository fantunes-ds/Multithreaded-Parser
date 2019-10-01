#pragma once
#include <vector>
#include <memory>
#include <Rendering/Resources/Model.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/Managers/InputManager.h>
#include <Core/Scene.h>
#include "Rendering/Context/IDevice.h"

namespace Core
{
	class GameManager
	{
	public:
		explicit GameManager(Rendering::Managers::Renderer * p_renderer);
		~GameManager();

		void AddGameObjectToScene(const std::string & p_name, std::shared_ptr<GameObject> p_gameObject, const int p_scene);
		void AddScene(Scene& p_scene);

		template<typename T>
		static void AddComponentToGameObject(GameObject & p_object, T p_component)
		{
			p_object.AddComponent(p_component);
		}

		void HandleEvents();
		void Update();

		void DrawActiveScene(Rendering::Managers::Renderer& p_renderer);

		void SetActiveScene(unsigned int p_activeScene);

		std::vector<Scene>& GetScenes() noexcept;
		Scene& GetActiveScene() noexcept;
		int GetActiveSceneNumber() const noexcept;
		std::unordered_map<std::string, std::shared_ptr<Core::GameObject>>& GetGameObjectsInScene(unsigned int p_scene);

	private:
		int m_activeScene{};
		double deltaTime = 0.0;
		double lastFrame = 0.0;
		Rendering::Context::IDevice* m_device{};
		std::vector<Scene> m_allScenes;
		Rendering::Managers::Renderer * m_rendererRef;
	};
}
