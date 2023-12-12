#include <Holt.h>
#include <Holt/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Holt {

	class HoltEditor : public Application
	{
	public:
		HoltEditor()
			: Application("Holt Editor")
		{
			PushLayer(new EditorLayer());
		}

		~HoltEditor()
		{

		}

	};

	Application* CreateApplication()
	{
		return new HoltEditor();
	}

}

