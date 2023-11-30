#include "hlpch.h"
#include "OpenGLContext.h"

#include "Holt/Core/Core.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Holt {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HL_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		HL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HL_CORE_ASSERT(status, "Failed to initialize Glad!");

		HL_CORE_INFO("OpenGL Info:");
		HL_CORE_INFO("Vendor:   {0}",   (char*)glGetString(GL_VENDOR));
		HL_CORE_INFO("Renderer: {0}",   (char*)glGetString(GL_RENDERER));
		HL_CORE_INFO("Version:  {0}",   (char*)glGetString(GL_VERSION));
		HL_CORE_INFO("Shading:  {0}\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

#ifdef HL_ENABLE_ASSERTS
		int versionMajor, versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		HL_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Holt requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		HL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}