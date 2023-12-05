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
		Ref<Texture2D>   _WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		HL_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();
		s_Data->_VertexArray = VertexArray::Create();
		float verticies[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		auto vertexBuffur = Holt::VertexBuffer::Create(verticies, sizeof(verticies));
		Holt::BufferLayout layout = {
			{ Holt::ShaderDataType::Float3, "a_Position" },
			{ Holt::ShaderDataType::Float2, "a_TexCoord" }
		};
		vertexBuffur->SetLayout(layout);
		s_Data->_VertexArray->AddVertexBuffer(vertexBuffur);
		uint32_t indicies[6] = { 0, 1, 2, 2, 3, 0 };
		auto indexBuffer = Holt::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t));
		s_Data->_VertexArray->SetIndexBuffer(indexBuffer);

		s_Data->_WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->_WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->_Shader = Holt::Shader::Create("assets/shaders/Default.glsl");
		s_Data->_Shader->Bind();
		s_Data->_Shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		HL_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		HL_PROFILE_FUNCTION();

		s_Data->_Shader->Bind();
		s_Data->_Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		HL_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HL_PROFILE_FUNCTION();

		s_Data->_Shader->Bind();
		s_Data->_Shader->SetFloat4("u_Color", color);
		s_Data->_Shader->SetFloat("u_TexScale", 1.0f);

		s_Data->_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->_Shader->SetMat4("u_Transform", transform);

		s_Data->_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->_VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HL_PROFILE_FUNCTION();

		s_Data->_Shader->Bind();
		s_Data->_Shader->SetFloat4("u_Color", tintColor);
		s_Data->_Shader->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->_Shader->SetMat4("u_Transform", transform);

		s_Data->_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->_VertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HL_PROFILE_FUNCTION();

		s_Data->_Shader->Bind();
		s_Data->_Shader->SetFloat4("u_Color", color);
		s_Data->_Shader->SetFloat("u_TexScale", 1.0f);

		s_Data->_WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->_Shader->SetMat4("u_Transform", transform);

		s_Data->_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->_VertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HL_PROFILE_FUNCTION();

		s_Data->_Shader->Bind();
		s_Data->_Shader->SetFloat4("u_Color", tintColor);
		s_Data->_Shader->SetFloat("u_TilingFactor", tilingFactor);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->_Shader->SetMat4("u_Transform", transform);

		s_Data->_VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->_VertexArray);
	}


}