#pragma once
#include <Core/Components/IComponent.h>
#include <Core/GameObject.h>
#include <Rendering/LowRenderer/Camera.h>

namespace Core::Components
{	
	enum class PLAYERSTATE
	{
		IS_JUMPING,
		ON_GROUND
	};

	class PlayerComponent : public IComponent
	{
	public:

		PlayerComponent(Core::GameObject& p_gameObject);
		~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& p_other);

		int GetHealth() const;
		PLAYERSTATE GetState() const;
		const std::string GetType() const override;

		void Move();
		void Update() override;

	private:
		int m_health;
		PLAYERSTATE m_state;
		Core::GameObject& m_gameObject;
	};
}

