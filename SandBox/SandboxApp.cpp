
#include <openGameEngine3D.h>
#include <openGameEngine3D/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

class Sandbox : public openGameEngine3D::Application
{
public:
	Sandbox ()
	{
		// PushLayer(new ExampleLayer());
		PushLayer (new Sandbox2D ());
	}

	~Sandbox ()
	{
	}
};

openGameEngine3D::Application* openGameEngine3D::CreateApplication ()
{
	return new Sandbox ();
}