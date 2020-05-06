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

		GBC_CORE_INFO("OpenGL:");
		GBC_CORE_INFO(" - Vendor = {0}", glGetString(GL_VENDOR));
		GBC_CORE_INFO(" - Renderer = {0}", glGetString(GL_RENDERER));
		GBC_CORE_INFO(" - Version = {0}", glGetString(GL_VERSION));

		int maxTextures;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
		GBC_CORE_INFO(" - Max Texture Slots = {0}", maxTextures);
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(window);
	}
}
