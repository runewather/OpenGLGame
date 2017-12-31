#pragma once
#include <iostream>
#include <glad\glad.h>
#include <GlFW/glfw3.h>
#include "glm/glm.hpp"
#include "Player.h"


class Game
{
private:
	GLFWwindow *window_;
	Player *player;
private:
	int Init(const char *title, GLint wdith, GLint height);
	glm::ivec2 GetWindowDimension();
	int GameLoop();
	void ProcessInput(GLFWwindow *window);
	void Update(float dt);
	void Draw();
	static void WindowResizeCallback(GLFWwindow *window, GLint width, GLint heigth);
public:
	Game(const char *title, GLint width, GLint height);
};

