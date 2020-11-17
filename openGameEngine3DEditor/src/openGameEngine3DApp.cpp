
#include <openGameEngine3D.h>
#include <openGameEngine3D/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace openGameEngine3D
{
	class openGameEngine3DEditor : public Application
	{
		public:
			openGameEngine3DEditor () : Application("openGameEngine3D Editor")
			{
				PushLayer (new EditorLayer ());
			}

			~openGameEngine3DEditor ()
			{
			}
	};

	Application* CreateApplication ()
	{
		return new openGameEngine3DEditor ();
	}
}
