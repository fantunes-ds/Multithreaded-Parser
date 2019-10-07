#pragma once

#include <Rendering/Export.h>
#include <Rendering/Context/IDevice.h>
#include <Rendering/Context/OpenGL/GLFWWindow.h>

namespace Rendering::Context::OpenGL
{
	class API_RENDERING GLFWDevice final : public IDevice
	{
	public:
		GLFWDevice() noexcept;
		GLFWDevice(unsigned int p_width, unsigned int p_height) noexcept;
		~GLFWDevice() noexcept;

		void Init() noexcept override;
		void Init(unsigned int p_width, unsigned int p_height) noexcept;
		bool ShouldClose() const noexcept override;
		void Render() const noexcept override;
		void RefreshEvent() const noexcept override;

		std::shared_ptr<GLFWWindow> GetWindow() const noexcept;

	private:
		std::shared_ptr<GLFWWindow> m_window;
	};
}
