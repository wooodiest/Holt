#pragma once
#include "Holt.h"

namespace Holt {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Holt::Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Holt::Event& event) override;
	private:
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_MainCameraEntity;

		Ref<Texture2D> m_CheckerboardTexture;
	};

}
