#include "glpch.h"
#include "PerspectiveCamera.h"

namespace OpenGLRenderer
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane)),
		m_ViewMatrix(glm::mat4(1.0f))
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
	}

	void PerspectiveCamera::CalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
	}
}