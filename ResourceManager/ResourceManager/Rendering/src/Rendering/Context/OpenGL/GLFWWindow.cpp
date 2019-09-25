#include <stdafx.h>
#include <Rendering/Context/OpenGL/GLFWWindow.h>
#include "Rendering/Managers/InputManager.h"

using namespace Rendering::Context::OpenGL;

GLFWWindow* GLFWWindow::m_instance;

GLFWWindow::GLFWWindow(unsigned int p_width, unsigned int p_height) noexcept
{
	m_glfwWindow = glfwCreateWindow(p_width, p_height, "Platformer - Luigi 64", nullptr, nullptr);
	assert(m_instance == nullptr);
	m_instance = this;

	BindKeyCallback();
	BindMouseButtonCallback();
	BindCloseWindowCallback();
}

GLFWWindow::~GLFWWindow() noexcept
{
	if (m_glfwWindow != nullptr)
		glfwDestroyWindow(m_glfwWindow);
}

bool GLFWWindow::ShouldClose() const noexcept
{
	return glfwWindowShouldClose(m_glfwWindow);
}

const std::any GLFWWindow::Data() const noexcept
{
	return m_glfwWindow;
}

GLFWWindow* GLFWWindow::GetInstance() noexcept
{
	return m_instance;
}

void GLFWWindow::BindKeyCallback() const noexcept
{
	const auto keyCallback = [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
	{
		IWindow* instanceWindow = GetInstance();

		if (instanceWindow != nullptr)
		{
			if (p_action == GLFW_PRESS)
				instanceWindow->m_keyPressedEvent.Invoke(p_key);

			if (p_action == GLFW_RELEASE)
				instanceWindow->m_keyReleasedEvent.Invoke(p_key);

			if (p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(p_window, GL_TRUE);
			}
		}
	};

	glfwSetKeyCallback(m_glfwWindow, keyCallback);
}

void GLFWWindow::BindMouseButtonCallback() const noexcept
{
	const auto mouseButtonCallback = [](GLFWwindow* p_window, int p_button, int p_action, int p_mods)
	{
		IWindow* instanceWindow = GetInstance();

		if (instanceWindow != nullptr)
		{
			if (p_action == GLFW_PRESS)
				instanceWindow->m_mouseButtonPressedEvent.Invoke(p_button);

			if (p_action == GLFW_RELEASE)
				instanceWindow->m_mouseButtonReleasedEvent.Invoke(p_button);
		}
	};

	glfwSetMouseButtonCallback(m_glfwWindow, mouseButtonCallback);
}

void GLFWWindow::BindCloseWindowCallback() const noexcept
{
	const auto closeWindowCallback = [](GLFWwindow* p_window)
	{
		IWindow* instanceWindow = GetInstance();

		if (instanceWindow != nullptr)
		{
			glfwTerminate();
		}
	};

	glfwSetWindowCloseCallback(m_glfwWindow, closeWindowCallback);
}