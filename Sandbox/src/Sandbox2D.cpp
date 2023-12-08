#include "Sandbox2D.h"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f, true)
{
	HL_PROFILE_FUNCTION();
}

Sandbox2D::~Sandbox2D()
{
	HL_PROFILE_FUNCTION();
}

void Sandbox2D::OnAttach()
{
	HL_PROFILE_FUNCTION();
	m_CheckerboardTexture = Holt::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	HL_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Holt::Timestep ts)
{
	HL_PROFILE_FUNCTION();
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Holt::Renderer2D::ResetStats();
	{
		HL_PROFILE_SCOPE("Renderer Prep");

		Holt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Holt::RenderCommand::Clear();
	}
	
	{
		HL_PROFILE_SCOPE("Renderer Draw");

		Holt::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Holt::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.5f }, { 30.0f, 30.0f }, m_CheckerboardTexture, m_tilingFactor, m_TintColor1);
		Holt::Renderer2D::DrawQuad({ -0.4f, -0.4f }, { 0.8f, 0.8f }, m_Color1);
		Holt::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_Color2);
		Holt::Renderer2D::DrawRotatedQuad({ 2.0f, -1.0f, 0.05f }, { 1.0f, 1.0f }, glm::radians(m_RoteatedQuadRotation), m_CheckerboardTexture, 1.0f, m_TintColor2);

		static float rotation = 0.0f;
		rotation += 50.0f * ts;
		Holt::Renderer2D::DrawRotatedQuad({ 2.0f, -3.0f, 0.1f }, { 2.0f, 2.0f }, glm::radians(rotation), {1.0f, 0.0f, 0.0f, 1.0f});

#if 0 // Draw 10k quads
		for (float y = -5.0f; y < 5.0f; y += 0.1f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.1f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, (x + 5.0f) / 10.0f, (y + 5.0f) / 10.0f, 0.9f };
				Holt::Renderer2D::DrawQuad({ x, y }, { 0.1f, 0.1f }, color);
			}
		}
#endif

#if 1 // Draw 40k quads
		for (float y = -10.0f; y < 10.0f; y += 0.1f)
		{
			for (float x = -10.0f; x < 10.0f; x += 0.1f)
			{
				glm::vec4 color = { (x + 10.0f) / 20.0f, (x + 10.0f) / 20.0f, (y + 10.0f) / 20.0f, 0.9f };
				Holt::Renderer2D::DrawQuad({ x, y }, { 0.1f, 0.1f }, color);
			}
		}
#endif

#if 0 // Draw 100k quads
		for (float y = -10.0f; y < 10.0f; y += 0.063f)
		{
			for (float x = -10.0f; x < 10.0f; x += 0.063f)
			{
				glm::vec4 color = { (x + 10.0f) / 20.0f, (x + 10.0f) / 20.0f, (y + 10.0f) / 20.0f, 0.9f };
				Holt::Renderer2D::DrawQuad({ x, y }, { 0.063f, 0.063f }, color);
			}
		}
#endif
		Holt::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender()
{
	HL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Holt::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
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
}

void Sandbox2D::OnEvent(Holt::Event& event)
{
	m_CameraController.OnEvent(event);
}
