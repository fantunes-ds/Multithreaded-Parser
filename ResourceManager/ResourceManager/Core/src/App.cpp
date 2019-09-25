#pragma once

#include <iostream>
#include <cstdlib>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <Core/Components/PlayerComponent.h>
#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/InputManager.h>
#include <Core/Scene.h>
#include <Core/GameManager.h>
#include <Core/Components/ModelComponent.h>
#include <Core/Components/CameraComponent.h>

int main()
{
	std::cout << "Hello World!\n";

	//TestGoodRendering();

	auto device = std::make_unique<Rendering::Context::OpenGL::GLFWDevice>(1024, 768);
	std::unique_ptr<Rendering::Managers::Renderer> renderer = std::make_unique<Rendering::Managers::Renderer>();
	renderer->Initialize<Rendering::Context::OpenGL::GLEWDriver>();

	Rendering::Managers::InputManager::InitializeFirstInstance(device->GetWindow());

	Core::GameManager gameManager(renderer.get());
	Rendering::LowRenderer::Camera mainCamera;

	std::shared_ptr<Core::GameObject> object1 = std::make_shared<Core::GameObject>();
	std::shared_ptr<Core::GameObject> car = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> player = std::make_shared<Core::GameObject>();
	Core::Scene scene1{};

	object1->AddComponent<Core::Components::ModelComponent>("../rsc/models/mannequin.fbx");
	car->AddComponent<Core::Components::ModelComponent>("../rsc/models/standard_car.fbx");
	player->AddComponent<Core::Components::ModelComponent>("../rsc/models/statue.obj");
	glm::vec3 distanceFromPlayer(0.0f, 0.2f, 0.0f);
	player->AddComponent<Core::Components::CameraComponent>(distanceFromPlayer);

	player->AddComponent<Core::Components::ModelComponent>("../rsc/models/mannequin.fbx");
	player->AddTexture("../rsc/textures/brick.png");

	scene1.AddGameObject(object1, "object1");
	scene1.AddGameObject(car, "car");
	scene1.AddGameObject(player, "player");

	gameManager.AddScene(scene1);
	gameManager.SetActiveScene(0);

	glm::vec3 newPos = glm::vec3(-1.0f, 0, 0);
	glm::vec3 rota = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);

	glm::vec3 newPos2 = glm::vec3(1.0f, 0, 0);
	glm::vec3 rota2 = glm::vec3(0, 0, 36);
	glm::vec3 scale2 = glm::vec3(0.005f, 0.005f, 0.005f);

	glm::vec3 newPos3 = glm::vec3(0.0f, 0, 3.0f);
	glm::vec3 rota3 = glm::vec3(0, 0, 0);
	glm::vec3 scale3 = glm::vec3(0.005f, 0.005f, 0.005f);

	gameManager.GetActiveScene().FindGameObject("object1")->SetTransform(newPos, rota, scale);
	gameManager.GetActiveScene().FindGameObject("car")->SetTransform(newPos2, rota2, scale2);
	gameManager.GetActiveScene().FindGameObject("player")->SetTransform(newPos3, rota3, scale3);

	Core::Components::PlayerComponent& playerComp = *player->GetComponent<Core::Components::PlayerComponent>();

	while (!device->ShouldClose())
	{
		device->RefreshEvent();
		renderer->Clear();

		// ##### Game logic #####
		gameManager.HandleEvents();

		// ##### Update #####
		gameManager.Update();


		// ##### Drawing #####
		gameManager.DrawActiveScene(*renderer);
		device->Render();
	}

	//assert(Rendering::Resources::Loaders::MeshLoader::Destroy(mesh));

	return EXIT_SUCCESS;
}
