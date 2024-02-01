#pragma once

#include "Camera.h"

namespace OpenGLRenderer
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float top, float bottom, float nearPlane = -1.0f, float farPlane = 1.0f);

		void SetPosition(const glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }
		void SetRotation(float angle) { m_Rotation = angle; CalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::vec3& GetPosition() const { return m_Position; }
		const float GetRotation() const { return m_Rotation; }

	private:
		void CalculateViewMatrix();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}
