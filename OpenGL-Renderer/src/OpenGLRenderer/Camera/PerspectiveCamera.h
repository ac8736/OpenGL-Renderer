#pragma once

#include "Camera.h"

namespace OpenGLRenderer
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov = 45.0f, float aspect = 800.0f / 600.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		const glm::vec3& GetPosition() const { return cameraPos; }
		const float GetRotation() const { return 0.0f; }
	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}