#include "hlpch.h"
#include "Application.h"

namespace Holt {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
	}

	void Application::Run()
	{
		while (m_Running)
		{

		}
	}

	bool Application::OnWindowClose()
	{
		m_Running = false;
		return true;
	}

}
