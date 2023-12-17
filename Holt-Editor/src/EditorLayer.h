#pragma once

#include <Holt.h>

#include "Panels/SceneHierarchyPanel.h"

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
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		int m_GizmoType = -1;
		//
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;

		Ref<Texture2D> m_CheckerboardTexture;
	};

}
