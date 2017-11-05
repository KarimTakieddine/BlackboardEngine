/*	--------------------###############################################################################----------------------

*	Copyright (c) 2017 Karim Takieddine

*	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
*	documentation files (the "Software"), to deal in the Software without restriction, including without limitation
*	the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
*	to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*	The above copyright notice and this permission notice shall be included in allcopies or substantial portions of
*	the Software.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
*	TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*	--------------------###############################################################################--------------------- */

#include "stdafx.h"
#include "ImageBuffer.h"
#include "Quad.h"
#include "Triangle.h"
#include "Time.h"

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

	GLFWwindow * window = glfwCreateWindow(640, 480, "BlackboardEngine", nullptr, nullptr);

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

	Quad quad(shaderProgram);

	quad.initialize();
	quad.loadTextureFile(".\\resources\\cat.png", TextureAttribute(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_TEXTURE_2D, VEC3(1.0f, 1.0f, 1.0f)));
	quad.initializeTransformUniform("model");

	Quad quadCopy(quad);
	//quadCopy.loadTextureFile(".\\resources\\pup.png", TextureAttribute(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_TEXTURE_2D, VEC3(1.0f, 1.0f, 1.0f)));
	quadCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("position", BufferAttribute(GL_FLOAT, 3, 0, 8 * sizeof(GLfloat)), shaderProgram));
	quadCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("color", BufferAttribute(GL_FLOAT, 3, 3 * sizeof(GLfloat), 8 * sizeof(GLfloat)), shaderProgram));
	quadCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("textureCoordinates", BufferAttribute(GL_FLOAT, 2, 6 * sizeof(GLfloat), 8 * sizeof(GLfloat)), shaderProgram));
	
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		quad.render();
		quad.transformUniform.transform.translate(VEC3(0.05 * Time::deltaTime, 0.0f, 0.05 * Time::deltaTime));

		quadCopy.render();
		quadCopy.transformUniform.transform.translate(VEC3(-0.05 * Time::deltaTime, 0.0f, -0.05 * Time::deltaTime));

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		Time::updateState();
	}

	glfwTerminate();

    return ERROR_SUCCESS;
}