#pragma once
#include "Holt.h"

class Sandbox2D : public Holt::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Holt::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Holt::Event& event) override;
private:
	Holt::OrthographicCameraController m_CameraController;
	Holt::Ref<Holt::VertexArray> m_VertexArray;
	Holt::Ref<Holt::Shader> m_Shader;
	glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };

};