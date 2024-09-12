#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 t_position = glm::vec3(0.0f, 0.0f, 0.0f)) : m_position(t_position),
					m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
					m_front(glm::vec3(0.0f, 0.0f, -1.0f))
{
}

glm::mat4 Camera::getViewMatrix() const
{
 	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::move(Direction t_direction, float t_deltaTime)
{
	float speed = SPEED * t_deltaTime;

	switch (t_direction)
	{
	case Direction::forward:
		m_position += m_front * speed;
		break;
	case Direction::backward:
		m_position -= m_front * speed;
		break;
	case Direction::left:
		m_position -= glm::normalize(glm::cross(m_front, m_up)) * speed;
		break;
	case Direction::right:
		m_position += glm::normalize(glm::cross(m_front, m_up)) * speed;
	}
}

void Camera::lookAround(float t_XOffset, float t_YOffset)
{
	m_pitch += t_YOffset *= SENSITIVITY;
	m_yaw += t_XOffset *= SENSITIVITY;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	glm::vec3 newDirection;
	newDirection.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	newDirection.y = glm::sin(glm::radians(m_pitch));
	newDirection.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));

	m_front = glm::normalize(newDirection);
}