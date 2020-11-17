#pragma once

#include "openGameEngine3D.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

class Sandbox2D : public openGameEngine3D::Layer
{
public:
	Sandbox2D ();
	virtual ~Sandbox2D () = default;

	virtual void OnAttach () override;
	virtual void OnDetach () override;

	void OnUpdate (openGameEngine3D::Timestep ts) override;
	virtual void OnImGuiRender () override;
	void OnEvent (openGameEngine3D::Event& e) override;
private:
	openGameEngine3D::OrthographicCameraController m_CameraController;

	// Temp
	openGameEngine3D::Ref<openGameEngine3D::VertexArray> m_SquareVA;
	openGameEngine3D::Ref<openGameEngine3D::Shader> m_FlatColorShader;

	openGameEngine3D::Ref<openGameEngine3D::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};