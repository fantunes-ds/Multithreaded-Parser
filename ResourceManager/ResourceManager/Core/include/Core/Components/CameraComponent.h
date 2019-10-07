#pragma once

#include <Core/Components/IComponent.h>

#include <Rendering/LowRenderer/Camera.h>
#include <Core/GameObject.h>

namespace Core::Components
{
	class CameraComponent : public IComponent
	{
	public:
		CameraComponent(GameObject& p_gameObject, glm::vec3& p_distanceFromPlayer);
		~CameraComponent() = default;

		const std::string GetType() const override;
		void Update() override;

	private:
		GameObject& m_gameObject;
		glm::vec3 m_distanceFromPlayer;
	};
}
