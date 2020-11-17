#pragma once

#include "openGameEngine3D/Renderer/GraphicsContext.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

struct GLFWwindow;

namespace openGameEngine3D
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext (GLFWwindow* windowHandle);

		virtual void Init () override;
		virtual void SwapBuffers () override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}