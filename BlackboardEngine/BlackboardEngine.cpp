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
#include "Cube.h"
#include "Tetrahedron.h"
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

	Shader fragmentColorShader(GL_FRAGMENT_SHADER);
	fragmentColorShader.loadFile(".\\shaders\\fragment_color.shd");

	if (!fragmentColorShader.isCompiled())
	{
		return ERROR_SHD_COMPILE;
	}

	Shader fragmentTextureShader(GL_FRAGMENT_SHADER);
	fragmentTextureShader.loadFile(".\\shaders\\fragment_texture.shd");

	if (!fragmentTextureShader.isCompiled())
	{
		return ERROR_SHD_COMPILE;
	}

	ShaderProgram colorShaderProgram;

	colorShaderProgram.attachShader(vertexShader).attachShader(fragmentColorShader).link();

	if (!colorShaderProgram.isLinked())
	{
		return ERROR_SHD_PROGRAM_LINK;
	}

	ShaderProgram textureShaderProgram;

	textureShaderProgram.attachShader(vertexShader).attachShader(fragmentTextureShader).link();

	if (!textureShaderProgram.isLinked())
	{
		return ERROR_SHD_PROGRAM_LINK;
	}

	Triangle triangle(colorShaderProgram);
	triangle.initialize();
	triangle.initializeTransformUniform("model");

	Triangle triangleCopy(colorShaderProgram);
	triangleCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("position", BufferAttribute(GL_FLOAT, 3, 0, 6 * sizeof(GLfloat)), colorShaderProgram));
	triangleCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("color", BufferAttribute(GL_FLOAT, 3, 3 * sizeof(GLfloat), 6 * sizeof(GLfloat)), colorShaderProgram));
	triangleCopy.initializeTransformUniform("model");

	Triangle wireframeTriangle(colorShaderProgram);
	wireframeTriangle.setRenderFlag(WIREFRAME);
	wireframeTriangle.initializeTransformUniform("model");

	Quad quad(textureShaderProgram);
	quad.setRenderFlag(TEXTURED);
	quad.loadTextureFile(".\\resources\\cat.png", TextureAttribute(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_TEXTURE_2D, VEC3(1.0f, 1.0f, 1.0f)));
	quad.initializeTransformUniform("model");

	Quad quadCopy(quad);
	quadCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("position", BufferAttribute(GL_FLOAT, 3, 0, 8 * sizeof(GLfloat)), textureShaderProgram));
	quadCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("color", BufferAttribute(GL_FLOAT, 3, 3 * sizeof(GLfloat), 8 * sizeof(GLfloat)), textureShaderProgram));
	quadCopy.bindVertexAttribute(GL_FALSE, VertexAttribute("textureCoordinates", BufferAttribute(GL_FLOAT, 2, 6 * sizeof(GLfloat), 8 * sizeof(GLfloat)), textureShaderProgram));

	Quad wireframeQuad(colorShaderProgram);
	wireframeQuad.setRenderFlag(WIREFRAME);
	wireframeQuad.initializeTransformUniform("model");

	MAT4 view = glm::lookAt
	(
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	MAT4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 1.0f, -10.0f);

	colorShaderProgram.use();
	GLint viewUniformColorLocation = glGetUniformLocation(colorShaderProgram.getIndex(), "view");
	glUniformMatrix4fv(viewUniformColorLocation, 1, GL_FALSE, glm::value_ptr(view));
	GLint projectionUniformColorLocation = glGetUniformLocation(colorShaderProgram.getIndex(), "projection");
	glUniformMatrix4fv(projectionUniformColorLocation, 1, GL_FALSE, glm::value_ptr(projection));

	textureShaderProgram.use();
	GLint viewUniformTextureLocation = glGetUniformLocation(textureShaderProgram.getIndex(), "view");
	glUniformMatrix4fv(viewUniformTextureLocation, 1, GL_FALSE, glm::value_ptr(view));
	GLint projectionUniformTextureLocation = glGetUniformLocation(textureShaderProgram.getIndex(), "projection");
	glUniformMatrix4fv(projectionUniformTextureLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float degrees		= 0.0f;
	float displacement	= 0.0f;
	
	triangle.transformUniform.transform.setScale(VEC3(0.65f, 0.65f, 0.65f));
	triangleCopy.transformUniform.transform.setScale(VEC3(0.35f, 0.35f, 0.35f));
	wireframeTriangle.transformUniform.transform.setScale(VEC3(0.5f, 0.5f, 0.5f));
	quad.transformUniform.transform.setScale(VEC3(0.75f, 0.75f, 0.75f));
	quadCopy.transformUniform.transform.setScale(VEC3(0.5f, 0.5f, 0.5f));
	wireframeQuad.transformUniform.transform.setScale(VEC3(0.35f, 0.35f, 0.35f));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		degrees			+= 30.0f * Time::deltaTime;
		displacement	+= 0.05f * Time::deltaTime;

		triangle.transformUniform.transform.setRotation(-degrees, VEC3(0.0f, 0.0f, 1.0f));
		triangle.transformUniform.transform.setTranslation(VEC3(displacement, displacement, 0.0f));
		triangle.render();

		triangleCopy.transformUniform.transform.setRotation(degrees, VEC3(0.0f, 0.0f, 1.0f));
		triangleCopy.transformUniform.transform.setTranslation(VEC3(-displacement, -displacement, 0.0f));
		triangleCopy.render();

		wireframeTriangle.transformUniform.transform.setRotation(degrees, VEC3(0.0f, 0.0f, 1.0f));
		wireframeTriangle.transformUniform.transform.setTranslation(VEC3(0.0f, displacement, 0.0f));
		wireframeTriangle.render();

		quad.transformUniform.transform.setRotation(-degrees, VEC3(1.0f, 1.0f, 0.0f));
		quad.transformUniform.transform.setTranslation(VEC3(-displacement, 0.0f, 0.0f));
		quad.render();
		
		quadCopy.transformUniform.transform.setRotation(degrees, VEC3(1.0f, 1.0f, 0.0f));
		quadCopy.transformUniform.transform.setTranslation(VEC3(displacement, 0.0f, 0.0f));
		quadCopy.render();

		wireframeQuad.transformUniform.transform.setRotation(degrees, VEC3(1.0f, 1.0f, 0.0f));
		wireframeQuad.transformUniform.transform.setTranslation(VEC3(-displacement, displacement, 0.0f));
		wireframeQuad.render();

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