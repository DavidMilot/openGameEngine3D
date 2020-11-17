#pragma once

#include "openGameEngine3D/Renderer/Buffer.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer ();
		OpenGLVertexBuffer (uint32_t size);

		OpenGLVertexBuffer (float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer ();

		virtual void Bind () const override;
		virtual void Unbind () const override;
		virtual void SetData (const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout () const override
		{
			return m_Layout;
		}
		virtual void SetLayout (const BufferLayout& layout) override
		{
			m_Layout = layout;
		}

		//Custom
		virtual void BindVertexArray () const override;
		virtual void AddCustomVertexBuffer (uint32_t index, int size, ShaderDataType type, bool normalized, int stride, uint32_t offset) const;
		virtual void RenderCube (unsigned int obj, int count);

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer (uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer ();

		virtual void Bind () const;
		virtual void Unbind () const;

		virtual uint32_t GetCount () const
		{
			return m_Count;
		}
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}