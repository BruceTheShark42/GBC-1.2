#include "gbcpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace gbc
{
	OpenGLContext::OpenGLContext(GLFWwindow *window)
		: window(window)
	{
		GBC_CORE_ASSERT(window != nullptr, "Context creation: window is nullptr!");
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(window);
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GBC_CORE_ASSERT(success, "Couldn't initialize Glad!");
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(window);
	}
}
