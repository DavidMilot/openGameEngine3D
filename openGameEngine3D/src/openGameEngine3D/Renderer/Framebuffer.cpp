#include "ogepch.h"
#include "Framebuffer.h"

#include "openGameEngine3D/Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLFramebuffer.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Ref<Framebuffer> Framebuffer::Create (const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    OGE_CORE_ASSERT (false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer> (spec);
		}

		OGE_CORE_ASSERT (false, "Unknown RendererAPI!");
		return nullptr;
	}
}