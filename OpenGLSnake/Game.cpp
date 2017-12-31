#include "Game.h"


glm::ivec2 Game::GetWindowDimension()
{
	GLint height, width;
	glfwGetWindowSize(window_, &width, &height);
	return glm::ivec2(width, height);
}

void Game::WindowResizeCallback(GLFWwindow *window, GLint width, GLint height)
{
	glViewport(0, 0, width, height);
}

void Game::ProcessInput(GLFWwindow *window)
{
	player->ProcessInput(window);
}

void Game::Update(float dt)
{

}

void Game::Draw()
{
	player->Draw();
}

int Game::GameLoop()
{
	while (!glfwWindowShouldClose(window_))
	{
		ProcessInput(window_);
		Update(0.5f);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		Draw();
				
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
	return 0;
}

Game::Game(const char *title, GLint width, GLint height) 
{
	Init(title, width, height);
}

int Game::Init(const char *title, GLint width, GLint height)
{
	//Init GLFW
	glfwInit();
	//OpenGL settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Create window
	window_ = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window_)
	{
		std::cout << "ERROR: FAILED TO CREATE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Set window context
	glfwMakeContextCurrent(window_);
	//Set window resize callback function
	glfwSetFramebufferSizeCallback(window_, WindowResizeCallback);
	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	player = new Player("Player");
	GameLoop();
	return 0;
}