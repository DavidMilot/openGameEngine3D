#include "ogepch.h"
#include "openGameEngine3D/Core/Window.h"

#ifdef OGE_PLATFORM_WINDOWS
	#include "Platforms/Windows/WindowsWindow.h"
#endif

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Scope<Window> Window::Create (const WindowProps& props)
	{
	#ifdef OGE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow> (props);
	#else
		OGE_CORE_ASSERT (false, "Unknown platform!");
		return nullptr;
	#endif
	}

}