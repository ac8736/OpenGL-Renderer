#pragma once

#include "Camera.h"

namespace OpenGLRenderer
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionViewMatrix() const { return m_ViewProjectionMatrix; }

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetCameraFront() const { return m_CameraFront; }
		const glm::vec3& GetCameraUp() const { return m_CameraUp; }
		const float GetRotation() const { return 1.0f; }
		
		void SetPosition(glm::vec3& pos) { m_Position = pos; CalculateViewMatrix(); }
	private:
		void CalculateViewMatrix();

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}