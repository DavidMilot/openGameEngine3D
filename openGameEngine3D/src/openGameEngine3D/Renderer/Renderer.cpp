#include "ogepch.h"
#include "openGameEngine3D/Renderer/Renderer.h"
#include "openGameEngine3D/Renderer/Renderer2D.h"
#include "openGameEngine3D/Renderer/Renderer3D.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData> ();

	void Renderer::Init ()
	{
		OGE_PROFILE_FUNCTION ();
		RenderCommand::Init ();
		//Rendering 3D
		//Renderer2D::Init ();

		Renderer3D::Init ();
	}
	void Renderer::Shutdown ()
	{
		//Rendering 3D
		//Renderer2D::Shutdown ();
		Renderer3D::Shutdown ();
	}

	void Renderer::BeginScene (PerspectiveCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix ();
	}
	
	void Renderer::BeginScene (OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix ();
	}

	void Renderer::OnWindowResize (uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport (0, 0, width, height);
	}

	void Renderer::EndScene ()
	{
	}

	void Renderer::Submit (const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind ();
		shader->SetMat4 ("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4 ("u_Transform", transform);
		vertexArray->Bind ();
		RenderCommand::DrawIndexed (vertexArray);
	}
}