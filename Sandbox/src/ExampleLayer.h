#pragma once
#include "Holt.h"

class ExampleLayer : public Holt::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Holt::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Holt::Event& event) override;

private:
	Holt::ShaderLibrary m_ShaderLibrary; // Later will be owned by renderer

	Holt::Ref<Holt::VertexArray> m_TriangleVertexArray;
	Holt::Ref<Holt::VertexArray> m_SquareVertexArray;
	Holt::Ref<Holt::Texture2D>   m_CheckerboardTexture;

	Holt::OrthographicCameraController m_CameraController;

	glm::vec4 color1 = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 color2 = { 0.8f, 0.2f, 0.3f, 1.0f };

};