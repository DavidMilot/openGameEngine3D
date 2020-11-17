#include "ogepch.h"
#include "Scene.h"

#include "Components.h"
#include "openGameEngine3D/Renderer/Renderer2D.h"
#include "Entity.h"
#include "openGameEngine3D/Renderer/Renderer3D.h"

#include <glm/glm.hpp>
#include <glm\gtx\string_cast.hpp>

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
	Scene::Scene () 
	{

	}

	Scene::~Scene (){}

	Entity Scene::CreateEntity (const std::string& name)
	{
		Entity entity = { m_Registry.create (), this };
		entity.AddComponent<TransformComponent> ();
		auto& tag = entity.AddComponent<TagComponent> ();
		tag.Tag = name.empty () ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate (Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent> ().each ([=] (auto entity, auto& nsc)
				{
					// TODO: Move to Scene::OnScenePlay
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript ();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate ();
					}

					nsc.Instance->OnUpdate (ts);
				});
		}

		// Render 2D
		/*Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent> ();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent> (entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene (mainCamera->GetProjection (), *cameraTransform);

			auto group = m_Registry.group<TransformComponent> (entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent> (entity);

				Renderer2D::DrawQuad (transform, sprite.Color);
			}
			Renderer2D::EndScene ();
		}*/
		
		Camera3D* camera3D = nullptr;
		glm::mat4* camera3DTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, Camera3DComponent> ();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, Camera3DComponent> (entity);

				if (camera.Primary)
				{
					camera3D = &camera.scene3DCamera;
					camera3DTransform = &transform.Transform;

					//std::cout << glm::to_string (camera3DTransform->length) << std::endl;
					break;
				}
			}
		}
		
		if (camera3D)
		{
			//Renderer3D::BeginScene (camera3D->GetProjection (), *camera3DTransform);
			Renderer3D::BeginScene (camera3D->GetProjection (), *camera3DTransform);
			/*
			auto group = m_Registry.group<TransformComponent> (entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent> (entity);

				Renderer3D::DrawQuad (transform, sprite.Color);
			}*/
			Renderer3D::EndScene ();
			//std::cout << "HEOO";
		}
	}

	void Scene::OnViewportResize (uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		/*
		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent> ();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent> (entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize (width, height);
		}*/

		// Resize our non-FixedAspectRatio cameras
		
		auto view3D = m_Registry.view<Camera3DComponent> ();
		for (auto entity : view3D)
		{
			auto& camera3DComponent = view3D.get<Camera3DComponent> (entity);
			if (!camera3DComponent.FixedAspectRatio)
				camera3DComponent.scene3DCamera.SetViewportSize (width, height);
		}
	}
}