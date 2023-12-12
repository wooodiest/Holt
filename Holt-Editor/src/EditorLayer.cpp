#include "EditorLayer.h"

#include "imgui/imgui.h"

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
	}

	void EditorLayer::OnDetach()
	{
		HL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Holt::Timestep ts)
	{
		HL_PROFILE_FUNCTION();
		// Update
		if(m_ViewportFocused)
			m_CameraController.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		{
			HL_PROFILE_SCOPE("Renderer Prep");

			m_Framebuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
		}

		{
			HL_PROFILE_SCOPE("Renderer Draw");

			Renderer2D::BeginScene(m_CameraController.GetCamera());

			Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.5f }, { 30.0f, 30.0f }, m_CheckerboardTexture, m_tilingFactor, m_TintColor1);
			Renderer2D::DrawQuad({ -0.4f, -0.4f }, { 0.8f, 0.8f }, m_Color1);
			Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_Color2);
			Renderer2D::DrawRotatedQuad({ 2.0f, -1.0f, 0.05f }, { 1.0f, 1.0f }, glm::radians(m_RoteatedQuadRotation), m_CheckerboardTexture, 1.0f, m_TintColor2);

			static float rotation = 0.0f;
			rotation += 50.0f * ts;
			Holt::Renderer2D::DrawRotatedQuad({ 2.0f, -3.0f, 0.1f }, { 2.0f, 2.0f }, glm::radians(rotation), { 1.0f, 0.0f, 0.0f, 1.0f });

#if 0 // Draw 10k quads
			for (float y = -5.0f; y < 5.0f; y += 0.1f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.1f)
				{
					glm::vec4 color = { (x + 5.0f) / 10.0f, (x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 0.9f };
					Renderer2D::DrawQuad({ x, y }, { 0.1f, 0.1f }, color);
				}
			}
#endif

#if 1 // Draw 40k quads
			for (float y = -10.0f; y < 10.0f; y += 0.1f)
			{
				for (float x = -10.0f; x < 10.0f; x += 0.1f)
				{
					glm::vec4 color = { (x + 10.0f) / 20.0f, (x + 10.0f) / 20.0f, (y + 10.0f) / 20.0f, 0.9f };
					Renderer2D::DrawQuad({ x, y }, { 0.1f, 0.1f }, color);
				}
			}
#endif

#if 0 // Draw 100k quads
			for (float y = -10.0f; y < 10.0f; y += 0.063f)
			{
				for (float x = -10.0f; x < 10.0f; x += 0.063f)
				{
					glm::vec4 color = { (x + 10.0f) / 20.0f, (x + 10.0f) / 20.0f, (y + 10.0f) / 20.0f, 0.9f };
					Renderer2D::DrawQuad({ x, y }, { 0.063f, 0.063f }, color);
				}
			}
#endif
			Renderer2D::EndScene();
			m_Framebuffer->Unbind();
		}

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

		// Settings / Stats
		ImGui::Begin("Settings");

		auto stats = Holt::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");

		ImGui::Text("FPS: %f", io.Framerate);
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::SeparatorText("");
		ImGui::Text("Scene Settings:");
		ImGui::ColorEdit4("Color-1", &m_Color1.r);
		ImGui::ColorEdit4("Color-2", &m_Color2.r);
		ImGui::ColorEdit4("Tint-1", &m_TintColor1.r);
		ImGui::DragFloat("Tiling factor", &m_tilingFactor, 0.1f);
		ImGui::ColorEdit4("Tint-2", &m_TintColor2.r);
		ImGui::DragFloat("Quad rotation", &m_RoteatedQuadRotation, 0.5f, 0.0f, 360.0f);

		ImGui::End();

		// Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
		}
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
