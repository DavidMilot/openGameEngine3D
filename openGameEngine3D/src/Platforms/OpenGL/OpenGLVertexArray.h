#pragma once

#include "openGameEngine3D/Renderer/VertexArray.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray ();
		virtual ~OpenGLVertexArray ();

		virtual void Bind () const override;
		virtual void Unbind () const override;

		virtual void AddVertexBuffer (const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer (const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers () const
		{
			return m_VertexBuffers;
		}
		virtual const Ref<IndexBuffer>& GetIndexBuffer () const
		{
			return m_IndexBuffer;
		}

		//Custom
		virtual void AddCustomVertexBuffer (uint32_t index, int size, ShaderDataType type, bool normalized, int stride, uint32_t offset) override;
		virtual void RenderCube (unsigned int obj, int count) override;
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}