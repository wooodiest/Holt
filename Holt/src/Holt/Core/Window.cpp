#include "hlpch.h"
#include "Window.h"


#ifdef HL_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Holt {

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef HL_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		HL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}