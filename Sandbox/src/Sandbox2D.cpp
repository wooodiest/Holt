#include "Sandbox2D.h"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f, true)
{

}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Holt::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Holt::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Holt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Holt::RenderCommand::Clear();

	Holt::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	Holt::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_Color1);
	Holt::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_Color2);
	Holt::Renderer2D::DrawQuad({ 0.0f, -0.0f, -0.1f}, { 5.0f, 5.0f }, m_CheckerboardTexture, m_Tint1, textureScale);
	Holt::Renderer2D::DrawQuad({ 1.0f, -1.0f, 0.05f }, { 1.0f, 1.0f }, m_CheckerboardTexture, m_Tint2);

	Holt::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color-1", &m_Color1.r);
	ImGui::ColorEdit4("Color-2", &m_Color2.r);
	ImGui::ColorEdit4("Tint-1", &m_Tint1.r);
	ImGui::DragFloat("Texture-Scale-1", &textureScale, 0.1f);
	ImGui::ColorEdit4("Tint-2", &m_Tint2.r);
	ImGui::End();
}

void Sandbox2D::OnEvent(Holt::Event& event)
{
	m_CameraController.OnEvent(event);
}
