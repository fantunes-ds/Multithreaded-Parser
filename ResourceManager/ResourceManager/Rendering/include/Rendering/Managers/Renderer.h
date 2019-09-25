#pragma once
#include <Rendering/Export.h>
#include <Rendering/Context/IDriver.h>
#include <Rendering/Resources/Mesh.h>
#include "Rendering/Resources/Model.h"

namespace Rendering::Managers
{
	class API_RENDERING Renderer
	{
	public:
		Renderer() noexcept = default;
		~Renderer() noexcept = default;

		template<typename T>
		void Initialize()
		{
			static_assert(std::is_base_of_v<Context::IDriver, T>);

			m_driver = std::make_unique<T>();
			m_driver->EnableDebug();
		}

		void Clear() const noexcept;
		void PolygonModeLine() noexcept;
		void PolygonModeFill() noexcept;
		void Draw(Resources::Model& p_model) const noexcept;

		bool IsDrawFilled() const;
	private:
		std::unique_ptr<Context::IDriver> m_driver;
		bool m_fillDrawIsOn{ false };
	};
}
