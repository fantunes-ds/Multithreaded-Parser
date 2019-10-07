#include <stdafx.h>

#include <Rendering/Context/OpenGL/GLFWDevice.h>

using namespace Rendering::Context::OpenGL;

GLFWDevice::GLFWDevice() noexcept
{
	Init();
}

GLFWDevice::GLFWDevice(unsigned int p_width, unsigned int p_height) noexcept
{
	Init(p_width, p_height);
}


GLFWDevice::~GLFWDevice() noexcept
{
	glfwTerminate();
}

void GLFWDevice::Init() noexcept
{
	glfwInit();

	m_window = std::make_unique<GLFWWindow>(1024, 768);

	// Debug
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// OpenGL Context configuration
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	glfwMakeContextCurrent(std::any_cast<GLFWwindow*>(m_window->Data()));
}

void GLFWDevice::Init(unsigned int p_width, unsigned int p_height) noexcept
{
	glfwInit();

	m_window = std::make_unique<GLFWWindow>(p_width, p_height);

	// Debug
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// OpenGL Context configuration
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	glfwMakeContextCurrent(std::any_cast<GLFWwindow*>(m_window->Data()));
}

bool GLFWDevice::ShouldClose() const noexcept
{
	return m_window->ShouldClose();
}

void GLFWDevice::Render() const noexcept
{
	glfwSwapBuffers(std::any_cast<GLFWwindow*>(m_window->Data()));
}

void GLFWDevice::RefreshEvent() const noexcept
{
	glfwPollEvents();
}

std::shared_ptr<GLFWWindow> GLFWDevice::GetWindow() const noexcept
{
	return m_window;
}
