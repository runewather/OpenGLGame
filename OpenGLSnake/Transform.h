#pragma once
#include "glm\glm.hpp"


class Transform
{
private:
	glm::vec3 position;
	glm::vec3 scale;
	float rotation;
public:
	void SetPosition(float x, float y);
	void SetScale(float x, float y);
	void SetRotation(float deg);
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	float GetRotation();
	Transform();
};

