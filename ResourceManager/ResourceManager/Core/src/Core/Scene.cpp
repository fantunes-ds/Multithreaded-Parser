#include <Core/Scene.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/LowRenderer/Light.h>
#include <stdafx.h>
#include "Core/Components/ModelComponent.h"


Core::Scene::Scene(const Scene & p_other)
{
	std::cout << "used Scene copy constructor\n";
	m_allGameObjects = p_other.m_allGameObjects;
}

void Core::Scene::AddGameObject(std::shared_ptr<GameObject> p_gameObject, const std::string& p_name)
{
	try
	{
		m_allGameObjects.try_emplace(p_name, p_gameObject);
		//return m_allGameObjects.find(p_name)->second;
	}
	catch (...)
	{
		std::cout << p_name + " is already added to Scene\n";
	}
}

void Core::Scene::DrawAll(Rendering::Managers::Renderer& p_renderer)
{
	if (m_allGameObjects.empty())
		return;

	for (auto& gameObject : m_allGameObjects)
	{
		if (gameObject.second->GetComponent<Components::ModelComponent>() == nullptr)
			continue;

		p_renderer.Draw(*gameObject.second->GetComponent<Components::ModelComponent>()->GetModel());
	}
}

void Core::Scene::Update()
{

	UpdateAllGameObjects();
}


void Core::Scene::UpdateAllGameObjects()
{
	for (auto& gameObject : m_allGameObjects)
	{
		gameObject.second->UpdateAllComponents();
		gameObject.second->UpdateShaders();
	}
}

void Core::Scene::UpdateAllComponents()
{
	for (auto& gameObject : m_allGameObjects)
		gameObject.second->UpdateAllComponents();

}

void Core::Scene::UpdateAllShaders()
{
	for (auto& gameObject : m_allGameObjects)
		gameObject.second->UpdateShaders();
}

void Core::Scene::RecompileAllShaders()
{
	for (auto& gameObject : m_allGameObjects)
		gameObject.second->RecompileShaders();
}

std::shared_ptr<Core::GameObject> Core::Scene::FindGameObject(const std::string& p_name)
{
	if (m_allGameObjects.find(p_name) == m_allGameObjects.end())
	{
		std::cout << "Could not find GameObject: " + p_name + " in Scene\n";
		return nullptr;
	}
	return m_allGameObjects.find(p_name)->second;
}


std::unordered_map<std::string, std::shared_ptr<Core::GameObject>>& Core::Scene::GetAllGameObjects()
{
	return m_allGameObjects;
}


