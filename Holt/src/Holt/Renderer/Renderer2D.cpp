#include "hlpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Holt {

	struct Renderer2DStorage
	{
		Ref<VertexArray> _VertexArray;
		Ref<Shader>      _Shader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->_VertexArray = VertexArray::Create();
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
		s_Data->_VertexArray->AddVertexBuffer(vertexBuffur);
		uint32_t indicies[6] = { 0, 1, 2, 2, 3, 0 };
		auto indexBuffer = Holt::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t));
		s_Data->_VertexArray->SetIndexBuffer(indexBuffer);
		s_Data->_Shader = Holt::Shader::Create("assets/shaders/Flat.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->_Shader->Bind();
		s_Data->_Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data->_Shader->SetMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->_Shader->Bind();
		s_Data->_Shader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->_Shader->SetMat4("u_Transform", transform);

		s_Data->_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->_VertexArray);
	}

}