#pragma once
#include <iostream>
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include "glm\glm.hpp"

class Game
{
private:
	glm::ivec2 window_dimension;
	std::string window_name;
	GLFWwindow *window;
	float delta_time;
	float last_frame_time;
private:
	void Init();
	void GameLoop();
	void Processinput(float dt);
	void UpdatePhysics(float dt);
	void Update(float dt);
	static void WindowResize(GLFWwindow* window, int width, int height);
public:
	glm::vec2 GetWindowDimension();
	Game(std::string w_name, int width, int height);
	~Game();
};

