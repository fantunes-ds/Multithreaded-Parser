#include <stdafx.h>
#include "Rendering/Test.h"
#include "Rendering/Context/OpenGL/GLFWDevice.h"
#include "Rendering/Context/OpenGL/GLEWDriver.h"

int TestBadRendering(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		// fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		std::cerr << "Error: " << glewGetErrorString(err) << '\n';
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}

int TestGoodRendering()
{
	Rendering::Context::OpenGL::GLFWDevice device{};
	Rendering::Context::OpenGL::GLEWDriver driver{};

	while(!device.ShouldClose())
	{
		device.RefreshEvent();

		driver.Clear();
		device.Render();
	}

	return EXIT_SUCCESS;
}
