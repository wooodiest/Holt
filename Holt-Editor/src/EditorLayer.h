#pragma once

#include <Holt.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Holt/Renderer/EditorCamera.h"

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
		EditorCamera m_EditorCamera;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Scene> m_ActiveScene;

		int m_GizmoType = -1;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

	};

}
