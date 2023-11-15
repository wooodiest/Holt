#pragma once

#include "Holt/Core/Layer.h"

#include "Holt/Events/ApplicationEvent.h"
#include "Holt/Events/KeyEvent.h"
#include "Holt/Events/MouseEvent.h"

namespace Holt {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}