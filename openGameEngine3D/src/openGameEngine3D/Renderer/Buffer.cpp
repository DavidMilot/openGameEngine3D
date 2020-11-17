#include "ogepch.h"
#include "openGameEngine3D/Renderer/Buffer.h"

#include "openGameEngine3D/Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Ref<VertexBuffer> VertexBuffer::Create ()
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    OGE_CORE_ASSERT (false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer> ();
		}

		OGE_CORE_ASSERT (false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create (uint32_t size)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    OGE_CORE_ASSERT (false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer> (size);
		}

		OGE_CORE_ASSERT (false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create (float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    std::cout << "false" << " RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer> (vertices, size);
		}

		std::cout << "False , Unknown RendererAPI!";
		//HZ_CORE_ASSERT (false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:     std::cout << "false" << " RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer> (indices, size);
		}

		std::cout << "False , Unknown RendererAPI!";
		//HZ_CORE_ASSERT (false, "Unknown RendererAPI!");
		return nullptr;
	}

}