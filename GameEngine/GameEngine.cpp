#include "stdafx.h"

#include "ShaderProgram.h"

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

	GLfloat const vertices[18] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vertexArray);

	GLint positionAttribute = glGetAttribLocation(shaderProgram.getIndex(), "position");
	glEnableVertexAttribArray(positionAttribute);
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);

	GLint colorAttribute = glGetAttribLocation(shaderProgram.getIndex(), "color");
	glEnableVertexAttribArray(colorAttribute);
	glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void const *>(3 * sizeof(GLfloat)));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 3);

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