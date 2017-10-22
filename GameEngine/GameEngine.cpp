#include "stdafx.h"
#include "Quad.h"
#include "Triangle.h"

enum ErrorCode
{
	ERROR_SUCCESS,
	ERROR_GLFW_INIT,
	ERROR_WND_INIT,
	ERROR_GLEW_INIT,
	ERROR_SHD_COMPILE,
	ERROR_SHD_PROGRAM_LINK
};

static void OnWindowResized(GLFWwindow * window, int width, int height)
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

	glfwSetWindowSizeCallback(window, OnWindowResized);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return ERROR_GLEW_INIT;
	}

	Shader vertexShader(GL_VERTEX_SHADER);
	vertexShader.loadFile(".\\shaders\\vertex.shd");

	if (!vertexShader.isCompiled())
	{
		return ERROR_SHD_COMPILE;
	}

	Shader fragmentShader(GL_FRAGMENT_SHADER);
	fragmentShader.loadFile(".\\shaders\\fragment.shd");

	if (!fragmentShader.isCompiled())
	{
		return ERROR_SHD_COMPILE;
	}

	ShaderProgram shaderProgram;
	shaderProgram.attachShader(vertexShader).attachShader(fragmentShader).link();

	if (!shaderProgram.isLinked())
	{
		return ERROR_SHD_PROGRAM_LINK;
	}

	shaderProgram.use();

	Triangle triangle(shaderProgram);

	triangle.initialize();

	Quad quad(shaderProgram);

	quad.initialize();

	MAT4 view = glm::lookAt
	(
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	GLint viewUniformLocation = glGetUniformLocation(shaderProgram.getIndex(), "view");

	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	MAT4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 1.0f, -10.0f);

	GLint projectionUniformLocation = glGetUniformLocation(shaderProgram.getIndex(), "projection");

	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

	triangle.initializeTransformUniform("model");
	quad.initializeTransformUniform("model");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		quad.render();

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