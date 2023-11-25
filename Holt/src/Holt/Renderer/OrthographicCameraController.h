#pragma once

#include "OrthographicCamera.h"
#include "Holt/Core/Timestep.h"
#include "Holt/Events/ApplicationEvent.h"
#include "Holt/Events/MouseEvent.h"

namespace Holt
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float asspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetRotation(bool rotation)                        { m_Rotation = rotation; }
		void SetZoomLevel(float zoomLevel)                     { m_ZoomLevel = zoomLevel; }
		void SetCameraRotation(float cameraRotation)           { m_CameraRotation = cameraRotation; }		
		void SetCameraTranslationSpeed(float translationSpeed) { m_CameraRotationSpeed = translationSpeed; }
		void SetCameraRotationSpeed(float rotationSpeed)       { m_CameraRotationSpeed = rotationSpeed; }
		void SetCameraPosition(const glm::vec3 cameraPosition) { m_CameraPosition = cameraPosition; }

		float GetZoomLevel()              const { return m_ZoomLevel; }
		float GetCameraRotation()         const { return m_CameraRotation; }
		float GetCameraTrnaslationSpeed() const { return m_CameraTranslationSpeed; }
		float GetCameraRotationSpeed()    const { return m_CameraRotationSpeed; }
		glm::vec3 GetCameraPosition()     const { return m_CameraPosition; }
		glm::vec3& GetCameraPositionRef()       { return m_CameraPosition; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 10.0f, m_CameraRotationSpeed = 180.0f;

	};
}
