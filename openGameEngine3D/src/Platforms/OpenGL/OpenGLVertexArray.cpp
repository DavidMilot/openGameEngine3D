#include "ogepch.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{

	static GLenum ShaderDataTypeToOpenGLBaseType (ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;

		}

		std::cout << "false, Unknown ShaderDataType!";
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray ()
	{
		OGE_PROFILE_FUNCTION ();
		glCreateVertexArrays (1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray ()
	{
		OGE_PROFILE_FUNCTION ();
		glDeleteVertexArrays (1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind () const
	{
		OGE_PROFILE_FUNCTION ();
		glBindVertexArray (m_RendererID);
	}

	void OpenGLVertexArray::Unbind () const
	{
		OGE_PROFILE_FUNCTION ();
		glBindVertexArray (0);
	}

	void OpenGLVertexArray::AddVertexBuffer (const Ref<VertexBuffer>& vertexBuffer)
	{
		OGE_PROFILE_FUNCTION ();
		std::cout << vertexBuffer->GetLayout ().GetElements ().size () << " Vertex Buffer has no layout!";

		glBindVertexArray (m_RendererID);
		vertexBuffer->Bind ();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout ();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
					{
						glEnableVertexAttribArray (m_VertexBufferIndex);
						glVertexAttribPointer (m_VertexBufferIndex,
							element.GetComponentCount (),
							ShaderDataTypeToOpenGLBaseType (element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride (),
							(const void*)element.Offset);
						m_VertexBufferIndex++;
						break;
					}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
					{
						uint8_t count = element.GetComponentCount ();
						for (uint8_t i = 0; i < count; i++)
						{
							glEnableVertexAttribArray (m_VertexBufferIndex);
							glVertexAttribPointer (m_VertexBufferIndex,
								count,
								ShaderDataTypeToOpenGLBaseType (element.Type),
								element.Normalized ? GL_TRUE : GL_FALSE,
								layout.GetStride (),
								(const void*)(element.Offset + sizeof (float) * count * i));
							glVertexAttribDivisor (m_VertexBufferIndex, 1);
							m_VertexBufferIndex++;
						}
						break;
					}
				default:
					OGE_CORE_ASSERT (false, "Unknown ShaderDataType!");
			}
		}
			m_VertexBuffers.push_back (vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer (const Ref<IndexBuffer>& indexBuffer)
	{
		OGE_PROFILE_FUNCTION ();
		glBindVertexArray (m_RendererID);
		indexBuffer->Bind ();

		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::AddCustomVertexBuffer (uint32_t index, int size, ShaderDataType type, bool normalized, int stride, uint32_t offset)
	{
		glVertexAttribPointer (index, 3, ShaderDataTypeToOpenGLBaseType(type), normalized, stride * sizeof (float), (void*)offset);
		glEnableVertexAttribArray (index);
		//glVertexAttribDivisor (m_VertexBufferIndex, 1); not needed??
	}

	void OpenGLVertexArray::RenderCube (unsigned int obj, int count)
	{
		// render the cube
		glBindVertexArray (obj);
		glDrawArrays (GL_TRIANGLES, 0, count);
	}
}