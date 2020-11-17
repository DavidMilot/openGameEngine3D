#include "ogepch.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	/////////////////////////////////////////////////////////////////////////////
	// VertexBuffer /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

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

	OpenGLVertexBuffer::OpenGLVertexBuffer ()
	{
		OGE_PROFILE_FUNCTION ();

		glCreateBuffers (1, &m_RendererID);


	}

	OpenGLVertexBuffer::OpenGLVertexBuffer (uint32_t size)
	{
		OGE_PROFILE_FUNCTION ();

		glCreateBuffers (1, &m_RendererID);
		glBindBuffer (GL_ARRAY_BUFFER, m_RendererID);
		glBufferData (GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer (float* vertices, uint32_t size)
	{
		OGE_PROFILE_FUNCTION ();

		glCreateBuffers (1, &m_RendererID);
		glBindBuffer (GL_ARRAY_BUFFER, m_RendererID);
		glBufferData (GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer ()
	{
		OGE_PROFILE_FUNCTION ();
		glDeleteBuffers (1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind () const
	{
		OGE_PROFILE_FUNCTION ();
		glBindBuffer (GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind () const
	{
		OGE_PROFILE_FUNCTION ();
		glBindBuffer (GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::RenderCube (unsigned int obj, int count)
	{
		// render the cube
//		std::cout << m_RendererID;
		glBindVertexArray (obj);
		glDrawArrays (GL_TRIANGLES, 0, count);
	}

	void OpenGLVertexBuffer::BindVertexArray () const
	{
		glBindVertexArray (m_RendererID);
	}

	void OpenGLVertexBuffer::AddCustomVertexBuffer (uint32_t index, int size, ShaderDataType type, bool normalized, int stride, uint32_t offset) const
	{
		glVertexAttribPointer (index, 3, ShaderDataTypeToOpenGLBaseType (type), normalized, stride * sizeof (float), (void*)offset);
		glEnableVertexAttribArray (index);
		//glVertexAttribDivisor (m_VertexBufferIndex, 1); not needed??
	}

	void OpenGLVertexBuffer::SetData (const void* data, uint32_t size)
	{
		glBindBuffer (GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData (GL_ARRAY_BUFFER, 0, size, data);
	}

	/////////////////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer (uint32_t* indices, uint32_t count)
		: m_Count (count)
	{
		glCreateBuffers (1, &m_RendererID);


		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer (GL_ARRAY_BUFFER, m_RendererID);
		glBufferData (GL_ARRAY_BUFFER, count * sizeof (uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer ()
	{
		OGE_PROFILE_FUNCTION ();
		glDeleteBuffers (1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind () const
	{
		OGE_PROFILE_FUNCTION ();
		glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind () const
	{
		OGE_PROFILE_FUNCTION ();
		glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}