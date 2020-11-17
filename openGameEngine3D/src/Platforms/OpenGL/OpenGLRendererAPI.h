#pragma once

#include "openGameEngine3D/Renderer/RendererAPI.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init () override;
		virtual void SetViewport (uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor (const glm::vec4& color) override;
		virtual void Clear () override;

		virtual void DrawIndexed (const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

	};
}