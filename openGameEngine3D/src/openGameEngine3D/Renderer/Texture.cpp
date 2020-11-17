#include "ogepch.h"
#include "openGameEngine3D/Renderer/Texture.h"

#include "openGameEngine3D/Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLTexture.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Ref<Texture2D> Texture2D::Create (uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    std::cout << "false, RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D> (width, height);
		}

		OGE_CORE_ASSERT (false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create (const std::string& path)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    std::cout << "false, RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D> (path);
		}

		OGE_CORE_ASSERT (false, "Unknown RendererAPI!");
		//std::cout << "false, Unknown RendererAPI!";
		return nullptr;
	}

}