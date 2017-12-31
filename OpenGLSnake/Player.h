#pragma once
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include <GLFW\glfw3.h>

class Player :	public Entity
{
public:
	Transform *transform;
private:
	const char *name_;
	const char *tag_;
	SpriteRenderer *spr;
public:
	Player(const char *name, const char *tag);
	Player(const char *name);
	void Move(float x, float y);
	void Update(float dt) override;
	void ProcessInput(GLFWwindow *window) override;
	void Draw() override;
};

