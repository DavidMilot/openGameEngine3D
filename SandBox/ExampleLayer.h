#pragma once

#include "openGameEngine3D.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

class ExampleLayer : public openGameEngine3D::Layer
{
public:
	ExampleLayer ();
	virtual ~ExampleLayer () = default;

	virtual void OnAttach () override;
	virtual void OnDetach () override;

	void OnUpdate (openGameEngine3D::Timestep ts) override;
	virtual void OnImGuiRender () override;
	void OnEvent (openGameEngine3D::Event& e) override;
private:
	openGameEngine3D::ShaderLibrary m_ShaderLibrary;
	openGameEngine3D::Ref<openGameEngine3D::Shader> m_Shader;
	openGameEngine3D::Ref<openGameEngine3D::VertexArray> m_VertexArray;

	openGameEngine3D::Ref<openGameEngine3D::Shader> m_FlatColorShader;
	openGameEngine3D::Ref<openGameEngine3D::VertexArray> m_SquareVA;

	openGameEngine3D::Ref<openGameEngine3D::Texture2D> m_Texture, m_ChernoLogoTexture;

	//openGameEngine3D::OrthographicCameraController m_CameraController;
	openGameEngine3D::PerspectiveCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
