#include "EditorLayer.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace Holt {

	EditorLayer::EditorLayer()
		: Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f, true)
	{
		HL_PROFILE_FUNCTION();
	}

	EditorLayer::~EditorLayer()
	{
		HL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnAttach()
	{
		HL_PROFILE_FUNCTION();
		m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");

		FramebufferSpecification spec;
		spec.Width = 1280;
		spec.Height = 720;
		m_Framebuffer = Holt::Framebuffer::Create(spec);

		///
		m_ActiveScene = CreateRef<Scene>();

		auto ent1 = m_ActiveScene->CreateEntity("Square - 1");
		ent1.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 1.0f, 1.0f });
		ent1.GetComponent<TransformComponent>().Translation.x = -2.0f;
		ent1.GetComponent<TransformComponent>().Scale.x *= 2;
		ent1.GetComponent<TransformComponent>().Scale.y *= 2;

		auto ent2 = m_ActiveScene->CreateEntity("Square - 2");
		ent2.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		ent2.GetComponent<TransformComponent>().Translation.x = 2.0f;
		ent2.GetComponent<TransformComponent>().Scale.x *= 2;
		ent2.GetComponent<TransformComponent>().Scale.y *= 2;

		auto ent3 = m_ActiveScene->CreateEntity("Square - 3");
		ent3.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
		ent3.GetComponent<SpriteRendererComponent>().Texture = m_CheckerboardTexture;
		ent3.GetComponent<TransformComponent>().Rotation.z = glm::radians(45.0f);
		ent3.GetComponent<TransformComponent>().Translation.x = 0.0f;
		ent3.GetComponent<TransformComponent>().Translation.y = 3.0f;
		ent3.GetComponent<TransformComponent>().Scale.x *= 2;
		ent3.GetComponent<TransformComponent>().Scale.y *= 2;

		auto cam1 = m_ActiveScene->CreateEntity("Orthograpic camera");
		cam1.AddComponent<CameraComponent>();
		cam1.GetComponent<CameraComponent>().Primary = true;

		auto cam2 = m_ActiveScene->CreateEntity("Perspective camera");
		cam2.AddComponent<CameraComponent>();
		cam2.GetComponent<CameraComponent>().Camera.SetProjectionType(SceneCamera::ProjectionType::Perspective);
		cam2.GetComponent<TransformComponent>().Translation.z = 25.0f;

		class CameraController : public ScriptableEntity
		{
		public:

			virtual void OnUpdate(Timestep ts)
			{
				auto& transform = GetComponent<TransformComponent>().Translation;
				auto& camera = GetComponent<CameraComponent>();

				float speed = 5.0f;

				if (camera.Primary)
				{
					if (Input::IsKeyPressed(KeyCode::A))
						transform.x -= speed * ts;
					if (Input::IsKeyPressed(KeyCode::D))
						transform.x += speed * ts;
					if (Input::IsKeyPressed(KeyCode::W))
						transform.y += speed * ts;
					if (Input::IsKeyPressed(KeyCode::S))
						transform.y -= speed * ts;
				}			
			}
		};
		cam1.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{
		HL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Holt::Timestep ts)
	{
		HL_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Update
		if(m_ViewportFocused)
			m_CameraController.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();	

		m_Framebuffer->Bind();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();
		
		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
		
	}

	void EditorLayer::OnImGuiRender()
	{
		HL_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		// Menu bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Holt::Application::Get().Close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		//
		m_SceneHierarchyPanel.OnImGuiRender();

		// Settings / Stats
		ImGui::Begin("Stats");

		auto stats = Holt::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");

		ImGui::Text("FPS: %f", io.Framerate);
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		// Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Holt::Event& event)
	{
		m_CameraController.OnEvent(event);
	}


}
