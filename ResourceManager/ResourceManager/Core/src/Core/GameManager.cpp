#include <iostream>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Core/GameManager.h>
#include <Core/GameObject.h>

using namespace Core;

GameManager::GameManager(Rendering::Managers::Renderer * p_renderer)
	: m_rendererRef{ p_renderer }
{
}

GameManager::~GameManager()
{
}

void Core::GameManager::AddGameObjectToScene(const std::string& p_name, std::shared_ptr<GameObject> p_gameObject, const int p_scene)
{
	m_allScenes[p_scene].GetAllGameObjects().try_emplace(p_name, p_gameObject);
}

void Core::GameManager::AddScene(Scene & p_scene)
{
	m_allScenes.push_back(p_scene);
}

void Core::GameManager::SetActiveScene(unsigned int p_activeScene)
{
	if (p_activeScene > m_allScenes.size() - 1)
	{
		std::cout << "Cannot set " << p_activeScene << " as active scene, since total amount of scenes is " << m_allScenes.size() << '\n';
		return;
	}

	m_activeScene = p_activeScene;
}

std::vector<Scene>& Core::GameManager::GetScenes() noexcept
{
	return m_allScenes;
}

Scene & Core::GameManager::GetActiveScene() noexcept
{
	return m_allScenes[m_activeScene];
}

int Core::GameManager::GetActiveSceneNumber() const noexcept
{
	return m_activeScene;
}

void Core::GameManager::HandleEvents()
{
	//todo create members to avoid expensive calls per frame
	Rendering::LowRenderer::Camera::GetInstance()->Move(*Rendering::Managers::InputManager::GetInstance());
	Rendering::LowRenderer::Camera::GetInstance()->LookAround(*Rendering::Managers::InputManager::GetInstance());
	//m_allScenes[m_activeScene].FindGameObject("player")->GetComponent<Components::PlayerComponent>()->Move();
	//GetActiveScene().FindGameObject("player")->GetComponent<Core::Components::PlayerComponent>()->Move();

	// Press the button and update the scene
	if (Rendering::Managers::InputManager::GetInstance()->GetKeyDown(Rendering::Utils::Event<int>::KeyCode::X))
	{
		m_allScenes[m_activeScene].RecompileAllShaders();
	}

	if (Rendering::Managers::InputManager::GetInstance()->GetKeyDown(Rendering::Utils::Event<int>::KeyCode::Z))
	{
		m_rendererRef->IsDrawFilled() ? m_rendererRef->PolygonModeLine() : m_rendererRef->PolygonModeFill();
	}

	Rendering::Managers::InputManager::GetInstance()->UpdateCursorPos();
}

void GameManager::Update()
{
	const double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	m_allScenes[m_activeScene].Update();
}

void GameManager::DrawActiveScene(Rendering::Managers::Renderer& p_renderer)
{
	m_allScenes[m_activeScene].DrawAll(p_renderer);
}


std::unordered_map<std::string, std::shared_ptr<GameObject>>& GameManager::GetGameObjectsInScene(unsigned int p_scene)
{
	if (p_scene > m_allScenes.size() - 1)
	{
		std::cout << "Cannot set " << p_scene << " as active scene, since total amount of scenes is " << m_allScenes.size() << '\n';
	}

	return m_allScenes[p_scene].GetAllGameObjects();
}
