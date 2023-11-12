#pragma once

#include "Window.h"

namespace Holt {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose();

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	private:
		static Application* s_Instance;

	};

	// To be defined in client
	Application* CreateApplication();
}

