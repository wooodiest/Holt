#include "Examplelayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), m_CameraController(1600.0f / 900.0f, true)
{
	// Triangle //
	m_TriangleVertexArray = Holt::VertexArray::Create();
	float triangleVertices[3 * 7] = {
		-0.9f, -0.9f, 0.0f, 0.8f, 0.2f, 0.8f, 0.7f,
		 0.9f, -0.9f, 0.0f, 0.2f, 0.3f, 0.8f, 0.7f,
		 0.0f,  0.9f, 0.0f, 0.8f, 0.8f, 0.2f, 0.7f
	};
	auto triangleVertexBuffer = Holt::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
	Holt::BufferLayout triangleLayout = {
		{ Holt::ShaderDataType::Float3, "a_Position" },
		{ Holt::ShaderDataType::Float4, "a_Color"}
	};
	triangleVertexBuffer->SetLayout(triangleLayout);
	m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
	uint32_t triangleIndices[3] = { 0, 1, 2 };
	auto triangleIndexBuffer = Holt::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
	m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

	// Grid & Texture //
	m_SquareVertexArray = Holt::VertexArray::Create();
	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	auto squareVertexBuffer = Holt::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	Holt::BufferLayout squareLayout = {
		{ Holt::ShaderDataType::Float3, "a_Position" },
		{ Holt::ShaderDataType::Float2, "a_TexCoord"}
	};
	squareVertexBuffer->SetLayout(squareLayout);
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	auto squareIndexBuffer = Holt::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

	// Shader & Textures //
	m_ShaderLibrary.Load("assets/shaders/Example.glsl");
	m_ShaderLibrary.Load("assets/shaders/Flat.glsl");
	m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	m_CheckerboardTexture = Holt::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ShaderLibrary.Get("Texture")->Bind();
	m_ShaderLibrary.Get("Texture")->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Holt::Timestep ts)
{
	// Update //
	m_CameraController.OnUpdate(ts);

	// - Triangle transform - //
	static glm::vec3 m_TriangleTransform(0.0f);
	static float m_TriangleTransformSpeed = 1.0f;

	if (Holt::Input::IsKeyPressed(HL_KEY_J))
		m_TriangleTransform.x -= m_TriangleTransformSpeed * ts;
	else if (Holt::Input::IsKeyPressed(HL_KEY_L))
		m_TriangleTransform.x += m_TriangleTransformSpeed * ts;

	if (Holt::Input::IsKeyPressed(HL_KEY_I))
		m_TriangleTransform.y += m_TriangleTransformSpeed * ts;
	else if (Holt::Input::IsKeyPressed(HL_KEY_K))
		m_TriangleTransform.y -= m_TriangleTransformSpeed * ts;

	// Render //
	Holt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Holt::RenderCommand::Clear();

	Holt::Renderer::BeginScene(m_CameraController.GetCamera());

	// - Grid - //
	auto flatShader = m_ShaderLibrary.Get("Flat");
	flatShader->Bind();
	for (int y = -15; y < 15; y++)
	{
		for (int x = -15; x < 15; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			if ((x + y) % 2 == 0)
				flatShader->SetFloat4("u_Color", color1);
			else
				flatShader->SetFloat4("u_Color", color2);

			Holt::Renderer::Submit(flatShader, m_SquareVertexArray, transform);
		}
	}

	// - Texture - //
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	m_CheckerboardTexture->Bind();
	Holt::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVertexArray, transform);

	// - Triangle - //
	transform = glm::translate(glm::mat4(1.0f), m_TriangleTransform) * glm::scale(glm::mat4(1.0f), glm::vec3(0.15f));
	Holt::Renderer::Submit(m_ShaderLibrary.Get("Example"), m_TriangleVertexArray, transform);

	
	Holt::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("ExampleLayer");

	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("FPS: %.1f", io.Framerate);

	ImGui::ColorEdit4("Color - 1", &color1.r);
	ImGui::ColorEdit4("Color - 2", &color2.r);

	ImGui::End();
}

void ExampleLayer::OnEvent(Holt::Event& event)
{
	m_CameraController.OnEvent(event);
}
