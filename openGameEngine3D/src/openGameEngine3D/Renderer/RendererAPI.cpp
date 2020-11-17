#include "ogepch.h"
#include "openGameEngine3D/Renderer/RendererAPI.h"

#include "Platforms/OpenGL/OpenGLRendererAPI.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create ()
	{
		switch (s_API)
		{
			//case RendererAPI::API::None:    HZ_CORE_ASSERT (false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::None:    std::cout << "false, RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI> ();
		}

		//HZ_CORE_ASSERT (false, "Unknown RendererAPI!");
		std::cout << "false, Unknown RendererAPI!";
		return nullptr;
	}

}