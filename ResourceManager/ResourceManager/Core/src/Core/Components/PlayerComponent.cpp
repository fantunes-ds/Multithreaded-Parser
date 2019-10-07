#define GLM_SWIZZLE
#include <gl/glew.h>
#include <iostream>

#include <Core/Components/PlayerComponent.h>
#include <Core/GameObject.h>


Core::Components::PlayerComponent::PlayerComponent(Core::GameObject& p_gameObject) : m_gameObject { p_gameObject }
{
	m_health = 100;
	m_state = PLAYERSTATE::IS_JUMPING;
}

Core::Components::PlayerComponent::PlayerComponent(const PlayerComponent & p_other) : m_gameObject { p_other.m_gameObject }
{
	m_health = p_other.m_health;
	m_state = p_other.m_state;
}

int Core::Components::PlayerComponent::GetHealth() const
{
	return m_health;
}

Core::Components::PLAYERSTATE Core::Components::PlayerComponent::GetState() const
{
	return m_state;
}

const std::string Core::Components::PlayerComponent::GetType() const
{
	return { "PlayerComponent" };
}

void Core::Components::PlayerComponent::Move()
{
	Rendering::Managers::InputManager* inputManager = &*Rendering::Managers::InputManager::GetInstance();

	// Need deltaTime here
	if (Rendering::Managers::InputManager::GetInstance()->GetKey(Rendering::Utils::Event<int>::KeyCode::W))
	{
		glm::vec3 moveBy = Rendering::LowRenderer::Camera::GetInstance()->GetForward() * 
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed();
		m_gameObject.TranslateBy(moveBy);
	}
	if (inputManager->GetKey(Rendering::Utils::Event<int>::KeyCode::S))
	{
		glm::vec3 moveBy = Rendering::LowRenderer::Camera::GetInstance()->GetBack() *
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed();
		m_gameObject.TranslateBy(moveBy);
	}
	if (inputManager->GetKey(Rendering::Utils::Event<int>::KeyCode::A))
	{
		glm::vec3 moveBy = -Rendering::LowRenderer::Camera::GetInstance()->GetRight() *
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed();
		m_gameObject.TranslateBy(moveBy);
	}
	if (inputManager->GetKey(Rendering::Utils::Event<int>::KeyCode::D))
	{
		glm::vec3 moveBy = Rendering::LowRenderer::Camera::GetInstance()->GetRight() *
			Rendering::LowRenderer::Camera::GetInstance()->GetMovementSpeed();
		m_gameObject.TranslateBy(moveBy);
	}
}

void Core::Components::PlayerComponent::Update()
{
	Move();
	//glm::vec3 direction = Rendering::LowRenderer::Camera::GetInstance()->GetForward();
	glm::vec3 direction(0.0f, -Rendering::LowRenderer::Camera::GetInstance()->GetYaw() - 90, 0.0f);
	
	m_gameObject.GetTransform().SetRot(direction);
}
