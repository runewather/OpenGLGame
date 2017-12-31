#include "Transform.h"



Transform::Transform()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = 0.0f;
}

void Transform::SetPosition(float x, float y)
{
	position = glm::vec3(x, y, 0.0f);
}

void Transform::SetScale(float x, float y)
{
	scale = glm::vec3(x, y, 1.0f);
}

void Transform::SetRotation(float deg)
{
	rotation = deg;
}

glm::vec3 Transform::GetPosition()
{
	return position;
}

glm::vec3 Transform::GetScale()
{
	return scale * 10.0f;
}

float Transform::GetRotation()
{
	return rotation;
}