#include "ogepch.h"
#include "openGameEngine3D/Renderer/RenderCommand.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create ();
}