#include <Holt.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Holt::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1600.0f / 900.0f, true)
	{
		m_VertexArray = Holt::VertexArray::Create();

		float triangleVertices[3 * 7] = {
			-0.9f, -0.9f, 0.0f, 0.8f, 0.2f, 0.8f, 0.7f,
			 0.9f, -0.9f, 0.0f, 0.2f, 0.3f, 0.8f, 0.7f,
			 0.0f,  0.9f, 0.0f, 0.8f, 0.8f, 0.2f, 0.7f
		};

		Holt::Ref<Holt::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer = Holt::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));

		Holt::BufferLayout layout = {
			{ Holt::ShaderDataType::Float3, "a_Position" },
			{ Holt::ShaderDataType::Float4, "a_Color"}
		};

		triangleVertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		Holt::Ref<Holt::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer = Holt::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);

		m_ShaderLibrary.Load("assets/shaders/Example.glsl");

		/// Square

		m_SquareVertexArray = Holt::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Holt::Ref<Holt::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = Holt::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVertexBuffer->SetLayout({
			{ Holt::ShaderDataType::Float3, "a_Position" },
			{ Holt::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Holt::Ref<Holt::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = Holt::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		m_ShaderLibrary.Load("assets/shaders/Flat.glsl");
		
		/// Texture
		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_Texture = Holt::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Holt::OpenGLShader>(m_ShaderLibrary.Get("Example"))->Bind();
		std::dynamic_pointer_cast<Holt::OpenGLShader>(m_ShaderLibrary.Get("Example"))->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(Holt::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// - Triangle transform
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

		/// Render
		Holt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Holt::RenderCommand::Clear();

		Holt::Renderer::BeginScene(m_CameraController.GetCamera());

		// -  Grid
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		auto flatShader = std::dynamic_pointer_cast<Holt::OpenGLShader>(m_ShaderLibrary.Get("Flat"));
		flatShader->Bind();

		for (int y = -15; y < 15; y++)
		{
			for (int x = -15; x < 15; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if ((x+y) % 2 == 0)
					flatShader->UploadUniformFloat4("u_Color", color1);
				else
					flatShader->UploadUniformFloat4("u_Color", color2);

				Holt::Renderer::Submit(m_ShaderLibrary.Get("Flat"), m_SquareVertexArray, transform);
			}
		}
		// - Texture
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) * scale;
		m_Texture->Bind();
		Holt::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVertexArray, transform);

		//  - Triangle
		scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.15f));
		transform = glm::translate(glm::mat4(1.0f), m_TriangleTransform) * scale;
		Holt::Renderer::Submit(m_ShaderLibrary.Get("Example"), m_VertexArray, transform);

		Holt::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("FPS: %.1f", io.Framerate);
		
		ImGui::ColorEdit4("Color - 1", &color1.r);
		ImGui::ColorEdit4("Color - 2", &color2.r);
	
		ImGui::End();
	}

	virtual void OnEvent(Holt::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Holt::ShaderLibrary m_ShaderLibrary; // Later will be owned by renderer
	
	Holt::Ref<Holt::VertexArray> m_VertexArray;
	Holt::Ref<Holt::VertexArray> m_SquareVertexArray;
	Holt::Ref<Holt::Texture2D> m_Texture;

	Holt::OrthographicCameraController m_CameraController;

	glm::vec4 color1 = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 color2 = { 0.8f, 0.2f, 0.3f, 1.0f };
};

class Sandbox : public Holt::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Holt::Application* Holt::CreateApplication()
{
	return new Sandbox();
}