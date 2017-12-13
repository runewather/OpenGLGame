#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

//Call this function when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	//Init GLFW
	glfwInit();
	//Set OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Create Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	//Set the window to context
	glfwMakeContextCurrent(window);
	
	//Init GLAD
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//Set Viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	//Set callback function to adjust screen when resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Delete all resources that were allocated
	glfwTerminate();
	return 0;
}