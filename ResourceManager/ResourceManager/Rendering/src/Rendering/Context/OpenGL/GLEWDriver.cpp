#include <stdafx.h>

#include <Rendering/Context/OpenGL/GLEWDriver.h>

using namespace Rendering::Context::OpenGL;

GLEWDriver::GLEWDriver() noexcept
{
	glewInit();
	std::cout << glGetString(GL_VERSION) << '\n';
}

void GLEWDriver::Clear() const noexcept
{
	glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLEWDriver::PolygonMode(std::any p_face, std::any p_mode) const noexcept
{
	glPolygonMode(std::any_cast<int>(p_face), std::any_cast<int>(p_mode));
}
void GLEWDriver::EnableDebug() const noexcept {}
