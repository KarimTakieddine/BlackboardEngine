#include "stdafx.h"

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

	GLfloat const vertices[18] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	BufferData<GLfloat> vertexBufferData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices));

	Mesh mesh(shaderProgram);
	mesh.bindVertexData(vertexBufferData);

	VertexAttribute positionAttribute("position", BufferAttribute(GL_FLOAT, 3, 0, 6 * sizeof(GLfloat)), shaderProgram);
	mesh.bindVertexAttribute(GL_FALSE, positionAttribute);

	VertexAttribute colorAttribute("color", BufferAttribute(GL_FLOAT, 3, 3 * sizeof(GLfloat), 6 * sizeof(GLfloat)), shaderProgram);
	mesh.bindVertexAttribute(GL_FALSE, colorAttribute);

	Mesh mesh_2(mesh);
	mesh_2.bindVertexAttribute(GL_FALSE, positionAttribute);
	mesh_2.bindVertexAttribute(GL_FALSE, colorAttribute);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//mesh.render();
		mesh_2.render();

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