#include "hlpch.h"
#include "Application.h"

#include "glad/glad.h"

namespace Holt {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window.reset(Window::Create());
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose()
	{
		m_Running = false;
		return true;
	}

}
