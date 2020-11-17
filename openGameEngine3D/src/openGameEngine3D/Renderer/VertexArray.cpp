#include "ogepch.h"
#include "openGameEngine3D/Renderer/VertexArray.h"

#include "openGameEngine3D/Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Ref<VertexArray> VertexArray::Create ()
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:     std::cout << "false, RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray> ();
		}

		std::cout << "false, Unknown RendererAPI!";
		return nullptr;
	}
}