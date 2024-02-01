#include "glpch.h"
#include "PerspectiveCamera.h"
#include <OpenGLRenderer/Log/Log.h>

namespace OpenGLRenderer
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane)
		: m_ProjectionMatrix(glm::mat4(1.0f)),
		m_ViewMatrix(glm::mat4(1.0f)),
		m_Fov(fov), m_Aspect(aspect), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_NearPlane, m_FarPlane);
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
	}

	void PerspectiveCamera::CalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
	}

	void PerspectiveCamera::MouseMovement(float xpos, float ypos)
	{
		if (m_FirstMouse)
		{
			m_LastMouseX = xpos;
			m_LastMouseY = ypos;
			m_FirstMouse = false;
		}

		float xoffset = xpos - m_LastMouseX;
		float yoffset = m_LastMouseY - ypos;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;
		if (m_Pitch > 89.0f)
		{
			m_Pitch = 89.0f;
		}
		if (m_Pitch < -89.0f)
		{
			m_Pitch = -89.0f;
		}

		glm::vec3 direction = { cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)), 
								sin(glm::radians(m_Pitch)), 
								sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)) };

		m_CameraFront = glm::normalize(direction);
		CalculateViewMatrix();
		m_LastMouseX = xpos;
		m_LastMouseY = ypos;
	}

	void PerspectiveCamera::UpdateAspect(float aspect)
	{
		m_Aspect = aspect;
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, 0.1f, 100.0f);
	}

	void PerspectiveCamera::UpdateFov(float fov)
	{
		m_Fov = fov;
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, 0.1f, 100.0f);
	}

	void PerspectiveCamera::MouseScrollZoom(float yoffset, float deltaTime)
	{
		m_Fov -= yoffset * deltaTime * 320.0f;
		if (m_Fov < 1.0f)
		{
			m_Fov = 1.0f;
		}
		if (m_Fov > 90.0f)
		{
			m_Fov = 90.0f;
		}

		UpdateFov(m_Fov);
	}
}