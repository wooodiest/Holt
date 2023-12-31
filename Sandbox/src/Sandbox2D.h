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
	Holt::Ref<Holt::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_Color1 = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_Color2 = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_TintColor1   = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 m_TintColor2 = { 0.2f, 0.3f, 0.4f, 0.85f };
	float m_tilingFactor = 10.0f;
	float m_RoteatedQuadRotation = 45.0f;

};