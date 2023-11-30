#include "hlpch.h"
#include "OrthographicCameraController.h"

#include "Holt/Core/Input.h"
#include "Holt/Core/KeyCodes.h"

#define ORTHOGRAPHIC_CAMERA_CONTROLLER_INDEPENDENT // Camera movement independent of rotation (for example if rotated pressing d still rotates the camera to the right)

namespace Holt {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HL_PROFILE_FUNCTION();

#ifdef ORTHOGRAPHIC_CAMERA_CONTROLLER_INDEPENDENT
		if (Input::IsKeyPressed(HL_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HL_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(HL_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HL_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HL_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(HL_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}
#else
		if (Input::IsKeyPressed(HL_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(HL_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(HL_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(HL_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HL_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(HL_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}
#endif
		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		HL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HL_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HL_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}