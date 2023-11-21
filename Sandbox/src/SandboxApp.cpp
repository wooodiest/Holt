#include <Holt.h>

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Holt::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_TriangleTransform(0.0f)
	{
		m_VertexArray.reset(Holt::VertexArray::Create());

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Holt::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(Holt::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

		Holt::BufferLayout layout = {
			{ Holt::ShaderDataType::Float3, "a_Position" },
			{ Holt::ShaderDataType::Float4, "a_Color"}
		};

		triangleVertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		std::shared_ptr<Holt::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(Holt::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(new Holt::Shader("ExampleShader", vertexSrc, fragmentSrc));

		/// Square

		m_SquareVertexArray.reset(Holt::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Holt::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Holt::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->SetLayout({
			{ Holt::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Holt::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Holt::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrcBlue = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrcBlue = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new Holt::Shader("BlueShader", vertexSrcBlue, fragmentSrcBlue));
		
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Holt::Renderer::Submit(m_BlueShader, m_SquareVertexArray, transform);
			}
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_TriangleTransform);
		Holt::Renderer::Submit(m_Shader, m_VertexArray, transform);
		
		// End

		Holt::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	virtual void OnEvent(Holt::Event& event) override
	{

	}

private:
	std::shared_ptr<Holt::Shader> m_Shader;
	std::shared_ptr<Holt::VertexArray> m_VertexArray;

	std::shared_ptr<Holt::Shader> m_BlueShader;
	std::shared_ptr<Holt::VertexArray> m_SquareVertexArray;

	///

	Holt::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	///
	glm::vec3 m_TriangleTransform;
	float m_TriangleTransformSpeed = 1.0f;

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