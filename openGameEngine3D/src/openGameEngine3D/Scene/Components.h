#pragma once

#include <glm/glm.hpp>
#include "SceneCamera.h"
#include "Scene3DCamera.h"
#include "ScriptableEntity.h"

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
	struct TagComponent
	{
		std::string Tag;

		TagComponent () = default;
		TagComponent (const TagComponent&) = default;
		TagComponent (const std::string& tag)
			: Tag (tag)
		{
		}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 & transform)
			: Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent () = default;
		CameraComponent (const CameraComponent&) = default;
		
	};

	struct Camera3DComponent
	{
		Scene3DCamera scene3DCamera;
		bool Primary = false; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		Camera3DComponent () = default;
		Camera3DComponent (const Camera3DComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();

		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind ()
		{
			InstantiateScript = [] ()
			{
				return static_cast<ScriptableEntity*>(new T ());
			};

			DestroyScript = [] (NativeScriptComponent* nsc)
			{
				delete nsc->Instance; nsc->Instance = nullptr;
			};
		}
	};
}