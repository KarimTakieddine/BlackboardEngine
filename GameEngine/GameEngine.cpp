#include "stdafx.h"

#include "File.h"

enum ErrorCode
{
	ERROR_SUCCESS, 
	ERROR_GLFW_INIT,
	ERROR_WND_INIT,
	ERROR_GLEW_INIT
};

static void OnWindowResized(int width, int height, GLFWwindow * window)
{
	glViewport(0, 0, width, height);
}

int main()
{

	if (glfwInit() != GL_TRUE)
	{
		return ERROR_GLFW_INIT;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow * window = glfwCreateWindow(640, 480, "GameEngine", nullptr, nullptr);

	if (!window)
	{
		return ERROR_WND_INIT;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		return ERROR_GLEW_INIT;
	}

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	glfwTerminate();

    return ERROR_SUCCESS;
}