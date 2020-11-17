#include "ogepch.h"
#include "Platforms/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	OpenGLContext::OpenGLContext (GLFWwindow* windowHandle)
		: m_WindowHandle (windowHandle)
	{
		//OGE_CORE_ASSERT (windowHandle, "Window handle is null!")
		if (windowHandle == nullptr) {
			std::cout << windowHandle << "Window handle is null!";
		}
	}

	void OpenGLContext::Init ()
	{
		OGE_PROFILE_FUNCTION ();
		glfwMakeContextCurrent (m_WindowHandle);
		int status = gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress);
		//OGE_CORE_ASSERT (status, "Failed to initialize Glad!");
		if (status == false) 
		{
			std::cout << status << "Failed to initialize Glad!";
		}

		std::cout << "OpenGL Info:";
		std::cout << "  Vendor: {0} " <<  glGetString (GL_VENDOR);
		std::cout << "  Renderer: {0}" << glGetString (GL_RENDERER);
		std::cout << "  Version: {0}" << glGetString (GL_VERSION);

		OGE_CORE_ASSERT (GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers ()
	{
		OGE_PROFILE_FUNCTION ();
		glfwSwapBuffers (m_WindowHandle);
	}
}