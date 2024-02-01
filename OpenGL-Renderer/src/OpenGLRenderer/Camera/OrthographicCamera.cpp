#include "glpch.h"
#include "OrthographicCamera.h"

namespace OpenGLRenderer
{
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float nearPlane, float farPlane)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, nearPlane, farPlane)), m_Position(0.0f), m_ViewMatrix(1.0f), m_Rotation(0.0f)
	{
	}

	void OrthographicCamera::CalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
	}
}