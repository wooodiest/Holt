#pragma once

namespace Holt {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose();
		bool m_Running = true;

	private:
		static Application* s_Instance;

	};

	// To be defined in client
	Application* CreateApplication();
}

