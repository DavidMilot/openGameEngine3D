#pragma once

#include "openGameEngine3D/Renderer/RenderCommand.h"
#include "openGameEngine3D/Renderer/OrthographicCamera.h"
#include "openGameEngine3D/Renderer/PerspectiveCamera.h"
#include "openGameEngine3D/Renderer/Shader.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	class Renderer
	{
	public:
		static void Init ();
		static void OnWindowResize (uint32_t width, uint32_t height);
		static void Shutdown ();

		static void BeginScene (OrthographicCamera& camera);
		static void BeginScene (PerspectiveCamera& camera);
		static void EndScene ();

		static void Submit (const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4 (1.0f));

		static RendererAPI::API GetAPI ()
		{
			return RendererAPI::GetAPI ();
		}
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}