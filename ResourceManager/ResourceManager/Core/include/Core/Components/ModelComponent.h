#pragma once
#include <memory>
#include <Core/GameObject.h>
#include <Core/Components/IComponent.h>
#include <Rendering/Resources/Model.h>

namespace Core::Components
{
	class ModelComponent : public IComponent
	{
	public:
		ModelComponent(GameObject& p_gameObject);
		ModelComponent(GameObject& p_gameObject, const std::string& p_path);
		~ModelComponent();
		ModelComponent(const ModelComponent& p_other);

		const std::string GetType() const override;
		void Update() override;
		const std::shared_ptr<Rendering::Resources::Mesh>& GetMesh() const;
		const std::shared_ptr<Rendering::Resources::Model>& GetModel() const;

	private:
		std::string m_type = "ModelComponent";
		std::shared_ptr<Rendering::Resources::Model> m_model;
		Core::GameObject& m_gameObject;
	};
}
