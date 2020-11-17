#include "ogepch.h"
#include "openGameEngine3D/Renderer/GraphicsContext.h"

#include "openGameEngine3D/Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLContext.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Scope<GraphicsContext> GraphicsContext::Create (void* window)
	{
		switch (Renderer::GetAPI ())
		{
			//case RendererAPI::API::None:    HZ_CORE_ASSERT (false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::None:    std::cout << "false RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext> (static_cast<GLFWwindow*>(window));
		}

		//HZ_CORE_ASSERT (false, "Unknown RendererAPI!");
		std::cout << false, "Unknown RendererAPI!";
		return nullptr;
	}

}