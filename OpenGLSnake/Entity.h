#pragma once
#include <GLFW\glfw3.h>
#ifndef ENTITY_H_
#define ENTITY_H_



class Entity
{
public:
	virtual void Update(float dt) = 0;
	virtual void ProcessInput(GLFWwindow *window) = 0;
	virtual void Draw() = 0;
};

#endif // !ENTITY_H_
