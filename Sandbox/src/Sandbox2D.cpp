#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f, true)
{

}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
	m_VertexArray = Holt::VertexArray::Create();
	float verticies[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	auto vertexBuffur = Holt::VertexBuffer::Create(verticies, sizeof(verticies));
	Holt::BufferLayout layout = {
		{ Holt::ShaderDataType::Float3, "a_Position" }
	};
	vertexBuffur->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffur);
	uint32_t indicies[6] = { 0, 1, 2, 2, 3, 0 };
	auto indexBuffer = Holt::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);
	m_Shader = Holt::Shader::Create("assets/shaders/Flat.glsl");
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

	Holt::Renderer::BeginScene(m_CameraController.GetCamera());
	
	m_Shader->Bind();
	m_Shader->SetFloat4("u_Color", m_Color);

	Holt::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, 0.0f}));

	Holt::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", &m_Color.r);
	ImGui::End();
}

void Sandbox2D::OnEvent(Holt::Event& event)
{
	m_CameraController.OnEvent(event);
}
