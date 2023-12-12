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
		m_FrameBuffer = Holt::Framebuffer::Create(spec);
	}

	void EditorLayer::OnDetach()
	{
		HL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Holt::Timestep ts)
	{
		HL_PROFILE_FUNCTION();
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		{
			HL_PROFILE_SCOPE("Renderer Prep");

			m_FrameBuffer->Bind();
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
			m_FrameBuffer->Unbind();
		}

	}

	void EditorLayer::OnImGuiRender()
	{
		HL_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
		static bool dockingEnabled = true;
		if (dockingEnabled)
		{
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
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

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
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

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows, 
					// which we can't undo at the moment without finer window depth/z control.
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

					if (ImGui::MenuItem("Exit")) Holt::Application::Get().Close();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

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

			uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{ 1280.0f, 720.0f }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::End();

			ImGui::End();
		}
		else
		{
			ImGuiIO& io = ImGui::GetIO();

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
		}
	}

	void EditorLayer::OnEvent(Holt::Event& event)
	{
		m_CameraController.OnEvent(event);
	}


}
