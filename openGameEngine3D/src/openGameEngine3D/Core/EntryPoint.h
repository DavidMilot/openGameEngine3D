#pragma once

#include "openGameEngine3D/Core/Base.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

#ifdef OGE_PLATFORM_WINDOWS

extern openGameEngine3D::Application* openGameEngine3D::CreateApplication ();

int main (int argc, char** argv)
{
	openGameEngine3D::Log::Init ();

	OGE_PROFILE_BEGIN_SESSION ("Startup", "openGameEngine3D-Profile-Startup.json");

	auto app = openGameEngine3D::CreateApplication ();

	OGE_PROFILE_END_SESSION ();

	OGE_PROFILE_BEGIN_SESSION ("Runtime", "openGameEngine3D-Profile-Runtime.json");

	app->Run ();

	OGE_PROFILE_END_SESSION ();

	OGE_PROFILE_BEGIN_SESSION ("Shutdown", "openGameEngine3D-Profile-Shutdown.json");

	delete app;

	OGE_PROFILE_END_SESSION ();

}

#endif