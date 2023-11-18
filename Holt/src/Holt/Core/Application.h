#pragma once

#include "Core.h"
#include "Window.h"

#include "Holt/Core/LayerStack.h"

#include "Holt/Events/Event.h"
#include "Holt/Events/ApplicationEvent.h"
#include "Holt/Events/KeyEvent.h"
#include "Holt/Events/MouseEvent.h"

#include "Holt/ImGui/ImGuiLayer.h"

#include "Holt/Renderer/Shader.h"
#include "Holt/Renderer/Buffer.h"
#include "Holt/Renderer/VertexArray.h"

#include "Holt/Renderer/OrthographicCamera.h"


namespace Holt {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;

	};

	// To be defined in client
	Application* CreateApplication();
}

