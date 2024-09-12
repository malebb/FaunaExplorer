#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction
{
	forward,
	backward,
	left,
	right
};

class Camera
{

public:
	
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_up;
	glm::vec3 m_front;

	Camera(glm::vec3 t_position);
	void move(Direction t_direction, float t_deltaTime);
	void lookAround(float t_XOffset, float t_YOffset);
	glm::mat4 getViewMatrix() const;

private:

	static constexpr float SPEED = 2.5f;
	static constexpr float SENSITIVITY = 0.05f;

	float m_pitch = 0.0f;
	float m_yaw = -90.0f;
};