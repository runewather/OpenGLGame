#include "Game.h"

void Game::Init()
{
	//Init GLFW
	glfwInit();
	//Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Create Window
	this->window = glfwCreateWindow(window_dimension.x, window_dimension.y, window_name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR: FAILED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return;
	}
	//Set context to window
	glfwMakeContextCurrent(this->window);
	//Set resize window callback function
	glfwSetFramebufferSizeCallback(this->window, this->WindowResize);
	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "ERROR: FAILED TO INITIALIZE GLAD" << std::endl;
	}
	//Set Viewport
	glViewport(0, 0, this->window_dimension.x, this->window_dimension.y);
	//Enable z-buffer
	glEnable(GL_DEPTH_TEST);
	//Init time vars
	this->delta_time = 0.0f;
	this->last_frame_time = 0.0f;
	//init Game Loop
	this->GameLoop();
}

void Game::WindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Game::Update(float dt)
{

}

void Game::Processinput(float dt)
{
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		std::cout << "DELTA TIME: " << dt << std::endl;
	}
}

void Game::GameLoop()
{
	while (!glfwWindowShouldClose(this->window))
	{
		//Calculate delta time
		float current_time = glfwGetTime();
		this->delta_time = current_time - last_frame_time;
		last_frame_time = current_time;
		//Process input
		this->Processinput(this->delta_time);
		//Update Entities
		this->Update(this->delta_time);
		//Draw Entities
		//DRAW
		glfwSwapBuffers(window);
		glfwPollEvents();		
	}
}

Game::Game(std::string w_name, int width, int height)
{
	this->window_name = w_name;
	this->window_dimension.x = width;
	this->window_dimension.y = height;
	Init();
}


Game::~Game()
{
}
