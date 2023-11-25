#include <Holt.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Holt::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_ScaleV(0.1f), m_CameraPosition(0.0f), m_TriangleTransform(0.0f)
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
		// Camera
		if (Holt::Input::IsKeyPressed(HL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Holt::Input::IsKeyPressed(HL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Holt::Input::IsKeyPressed(HL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Holt::Input::IsKeyPressed(HL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Holt::Input::IsKeyPressed(HL_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Holt::Input::IsKeyPressed(HL_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		// Triangle transform
		if (Holt::Input::IsKeyPressed(HL_KEY_J))
			m_TriangleTransform.x -= m_TriangleTransformSpeed * ts;
		else if (Holt::Input::IsKeyPressed(HL_KEY_L))
			m_TriangleTransform.x += m_TriangleTransformSpeed * ts;

		if (Holt::Input::IsKeyPressed(HL_KEY_I))
			m_TriangleTransform.y += m_TriangleTransformSpeed * ts;
		else if (Holt::Input::IsKeyPressed(HL_KEY_K))
			m_TriangleTransform.y -= m_TriangleTransformSpeed * ts;

		/// Begin
		Holt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Holt::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Holt::Renderer::BeginScene(m_Camera);

		///
		// Grid
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_ScaleV);
		auto flatShader = std::dynamic_pointer_cast<Holt::OpenGLShader>(m_ShaderLibrary.Get("Flat"));
		flatShader->Bind();

		for (int y = -15; y < 15; y++)
		{
			for (int x = -15; x < 15; x++)
			{
				glm::vec3 pos(x * 1.1f * m_Scale, y * 1.1f * m_Scale, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if ((x+y) % 2 == 0)
					flatShader->UploadUniformFloat4("u_Color", colorBlue);
				else
					flatShader->UploadUniformFloat4("u_Color", colorRed);

				Holt::Renderer::Submit(m_ShaderLibrary.Get("Flat"), m_SquareVertexArray, transform);
			}
		}
		// Texture
		scale = glm::scale(glm::mat4(1.0f), m_ScaleV * 10.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) * scale;
		m_Texture->Bind();
		Holt::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVertexArray, transform);

		// Triangle
		scale = glm::scale(glm::mat4(1.0f), m_ScaleV);
		transform = glm::translate(glm::mat4(1.0f), m_TriangleTransform) * scale;
		Holt::Renderer::Submit(m_ShaderLibrary.Get("Example"), m_VertexArray, transform);

		// End

		Holt::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		///
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("FPS: %.1f", io.Framerate);
		///
		ImGui::SeparatorText("Display");
		if (ImGui::DragFloat("Scale", &m_Scale, 0.01f))
		{
			m_ScaleV.x = m_Scale;
			m_ScaleV.y = m_Scale;
		}
		if (ImGui::Button("Reset   "))
		{
			m_Scale = 0.1f;
			m_ScaleV.x = 0.1f;
			m_ScaleV.y = 0.1f;
		}
		///
		ImGui::SeparatorText("Camera");
		ImGui::DragFloat2("Position", &m_CameraPosition.x, 0.01f);
		ImGui::DragFloat("Speed", &m_CameraMoveSpeed, 0.1f);
		ImGui::DragFloat("Rotation", &m_CameraRotation, 0.1f);
		ImGui::DragFloat("Rotation speed", &m_CameraRotationSpeed, 1.0f);
		if (ImGui::Button("Reset"))
		{
			m_CameraPosition = glm::vec3(0.0f);
			m_CameraMoveSpeed = 5.0f;

			m_CameraRotation = 0.0f;
			m_CameraRotationSpeed = 180.0f;
		}
		///
		ImGui::SeparatorText("Triangle");
		ImGui::DragFloat2("Position ", &m_TriangleTransform.x, 0.01f);
		ImGui::DragFloat("Speed ", &m_TriangleTransformSpeed, 0.1f);
		if (ImGui::Button("Reset "))
		{
			m_TriangleTransform = glm::vec3(0.0f);
			m_TriangleTransformSpeed = 1.0f;
		}
		///
		ImGui::SeparatorText("Grid");
		ImGui::ColorEdit4("Color - 1", &colorBlue.r);
		ImGui::ColorEdit4("Color - 2", &colorRed.r);
		if (ImGui::Button("Reset  "))
		{
			colorBlue = { 0.2f, 0.3f, 0.8f, 1.0f };
			colorRed = { 0.8f, 0.2f, 0.3f, 1.0f };
		}
		///
		ImGui::End();
	}

	virtual void OnEvent(Holt::Event& event) override
	{
		if (event.GetEventType() == Holt::EventType::MouseScrolled)
		{
			Holt::MouseScrolledEvent& e = (Holt::MouseScrolledEvent&)event;
			if (e.GetYOffset() == 1)
			{
				m_Scale *= 1.1f;
				m_ScaleV.x = m_Scale;
				m_ScaleV.y = m_Scale;
			}
			else if (e.GetYOffset() == -1)
			{
				m_Scale *= 0.9f;
				m_ScaleV.x = m_Scale;
				m_ScaleV.y = m_Scale;
			}
		}
	}

private:
	Holt::ShaderLibrary m_ShaderLibrary; // Later will be owned by renderer
	
	Holt::Ref<Holt::VertexArray> m_VertexArray;
	Holt::Ref<Holt::VertexArray> m_SquareVertexArray;
	Holt::Ref<Holt::Texture2D> m_Texture;

	///
	float m_Scale = 0.1f;
	glm::vec3 m_ScaleV;

	Holt::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	///
	glm::vec3 m_TriangleTransform;
	float m_TriangleTransformSpeed = 1.0f;

	glm::vec4 colorBlue = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 colorRed = { 0.8f, 0.2f, 0.3f, 1.0f };
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