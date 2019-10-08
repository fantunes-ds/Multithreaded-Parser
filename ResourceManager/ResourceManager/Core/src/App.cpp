#pragma once

#include <iostream>
#include <cstdlib>
#include <chrono>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <Core/Components/PlayerComponent.h>
#include <Core/Components/ModelComponent.h>
#include <Core/Components/CameraComponent.h>
#include <Core/GameManager.h>
#include <Core/Scene.h>
#include <Core/GameObject.h>

#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/Managers/InputManager.h>
#include <Rendering/Managers/ResourceManager.h>
#include <Rendering/LowRenderer/Camera.h>

int main()
{
	auto device = std::make_unique<Rendering::Context::OpenGL::GLFWDevice>(1024, 768);
	std::unique_ptr<Rendering::Managers::Renderer> renderer = std::make_unique<Rendering::Managers::Renderer>();
	renderer->Initialize<Rendering::Context::OpenGL::GLEWDriver>();

	Rendering::Managers::InputManager::InitializeFirstInstance(device->GetWindow());

	Core::GameManager gameManager(renderer.get());
	Rendering::LowRenderer::Camera mainCamera;

    Rendering::Managers::ResourceManager ResourceManager{};

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

    std::shared_ptr<Core::GameObject> lambo = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> lambo2 = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> lambo3 = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> object = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> dagger = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> statue = std::make_shared<Core::GameObject>();
    std::shared_ptr<Core::GameObject> link = std::make_shared<Core::GameObject>();
	Core::Scene scene1{};

	lambo->AddComponent<Core::Components::ModelComponent>("../rsc/meshes/Lambo.obj");
	lambo2->AddComponent<Core::Components::ModelComponent>("../rsc/meshes/Lambo.obj");
	lambo3->AddComponent<Core::Components::ModelComponent>("../rsc/meshes/Lambo.obj");
	object->AddComponent<Core::Components::ModelComponent>("../rsc/meshes/Greatsword.obj");
	dagger->AddComponent<Core::Components::ModelComponent>("../rsc/meshes/Dagger.obj");
	statue->AddComponent<Core::Components::ModelComponent>("../rsc/meshes/Statue.obj");
	link->AddComponent<Core::Components::ModelComponent>("../rsc/meshes/YoungLink.obj");
	glm::vec3 distanceFromPlayer(0.0f, 0.2f, 0.0f);
	object->AddComponent<Core::Components::CameraComponent>(distanceFromPlayer);
    //object->AddTexture("../rsc/textures/Greatsword/MQGreatsword.bmp");

	scene1.AddGameObject(object, "object");
	scene1.AddGameObject(dagger, "dagger");
	scene1.AddGameObject(statue, "statue");
	scene1.AddGameObject(link, "link");
	scene1.AddGameObject(lambo, "lambo");
	scene1.AddGameObject(lambo2, "lambo2");
	scene1.AddGameObject(lambo3, "lambo3");

	gameManager.AddScene(scene1);
	gameManager.SetActiveScene(0);

	glm::vec3 newPos = glm::vec3(0, 0, 0);
	glm::vec3 newPos1 = glm::vec3(-2, 0, 0);
	glm::vec3 newPos2 = glm::vec3(2, 0, 0);
	glm::vec3 newPos3 = glm::vec3(1, 1, 0);
	glm::vec3 newPos4 = glm::vec3(-4, -1, 0);
	glm::vec3 newPos5 = glm::vec3(-4, 0, 0);
	glm::vec3 newPos6 = glm::vec3(-4, 1, 0);
	glm::vec3 rota = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 scale1 = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 scale2 = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 scale3 = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 scale4 = glm::vec3(0.005f, 0.005f, 0.005f);

	gameManager.GetActiveScene().FindGameObject("object")->SetTransform(newPos, rota, scale);
	gameManager.GetActiveScene().FindGameObject("dagger")->SetTransform(newPos1, rota, scale1);
	gameManager.GetActiveScene().FindGameObject("statue")->SetTransform(newPos2, rota, scale2);
	gameManager.GetActiveScene().FindGameObject("link")->SetTransform(newPos3, rota, scale3);
	gameManager.GetActiveScene().FindGameObject("lambo")->SetTransform(newPos4, rota, scale4);
	gameManager.GetActiveScene().FindGameObject("lambo2")->SetTransform(newPos5, rota, scale4);
	gameManager.GetActiveScene().FindGameObject("lambo3")->SetTransform(newPos6, rota, scale4);


	end = std::chrono::system_clock::now();
	auto elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Done creating objects in " << elapsed_seconds << " millisec" << '\n';

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

	return EXIT_SUCCESS;
}
