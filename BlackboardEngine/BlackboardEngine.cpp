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
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "Quad.h"
#include "Cube.h"
#include "Tetrahedron.h"
#include "Triangle.h"
#include "Time.h"

enum ErrorCode
{
	ERROR_NONE,
	ERROR_GLFW_INIT,
	ERROR_WND_INIT,
	ERROR_AUDIO_INIT,
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

	AudioDevice audioDevice;

	if (!audioDevice.initialize(nullptr))
	{
		return ERROR_AUDIO_INIT;
	}

	AudioBuffer audioBuffer(audioDevice);
	AudioSource audioSource;

	CWaves waves;
	WAVEID waveId;

	if (waves.OpenWaveFile(".\\resources\\410443__mayonaka123__boomwhacker.wav", &waveId) == WR_OK)
	{
		WAVEFORMATEX format		= {};
		unsigned long dataSize	= 0;
		unsigned long frequency = 0;
		unsigned long alFormat	= 0;

		waves.GetWaveSize(waveId, &dataSize);
		waves.GetWaveALBufferFormat(waveId, &alGetEnumValue, &alFormat);
		waves.GetWaveFrequency(waveId, &frequency);
		waves.GetWaveFormatExHeader(waveId, &format);

		// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...

		dataSize -= (dataSize % format.nBlockAlign);

		unsigned long bytesRead = 0;

		void * data = malloc(dataSize);

		waves.SetWaveDataOffset(waveId, 0);

		if (waves.ReadWaveData(waveId, data, dataSize, &bytesRead) == WR_OK)
		{
			alGetError();
			alBufferData(audioBuffer.getIndex(), alFormat, data, bytesRead, frequency);
			alSourcei(audioSource.getIndex(), AL_BUFFER, audioBuffer.getIndex());
			alSourcePlay(audioSource.getIndex());
		}

		free(data);
		data = nullptr;
	}

	Shader vertexShader(GL_VERTEX_SHADER);

	vertexShader.loadFile(".\\shaders\\vertex_normal.shd");

	if (!vertexShader.isCompiled())
	{
		return ERROR_SHD_COMPILE;
	}

	Shader fragmentShader(GL_FRAGMENT_SHADER);

	fragmentShader.loadFile(".\\shaders\\fragment_phong_lighting.shd");

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
	quad.setRenderFlag(TEXTURED_LIT);
	quad.loadTextureFile(".\\resources\\guy.JPG", TextureAttribute(GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_TEXTURE_2D, VEC3(1.0f, 1.0f, 1.0f)));
	quad.initializeTransformUniform("model");

	MAT44 view = glm::lookAt
	(
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	MAT44 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 1.0f, -10.0f);

	GLint viewUniformColorLocation = glGetUniformLocation(shaderProgram.getIndex(), "view");
	glUniformMatrix4fv(viewUniformColorLocation, 1, GL_FALSE, glm::value_ptr(view));
	GLint projectionUniformColorLocation = glGetUniformLocation(shaderProgram.getIndex(), "projection");
	glUniformMatrix4fv(projectionUniformColorLocation, 1, GL_FALSE, glm::value_ptr(projection));

	VEC3 lightPosition(0.5, 0.5, 0.5);
	VEC3 lightIntensity(1.0f, 1.0f, 1.0f);
	float ambientCoefficient	= 0.15f;
	float specularExponent		= 2.0f;
	float lightAttenuation		= 0.2f;
	float gamma					= 1.0f;

	GLint lightUniformPositionLocation		= glGetUniformLocation(shaderProgram.getIndex(), "lightPosition");
	GLint lightUniformIntensityLocation		= glGetUniformLocation(shaderProgram.getIndex(), "lightIntensity");
	GLint lightAmbientCoefficientLocation	= glGetUniformLocation(shaderProgram.getIndex(), "ambientCoefficient");
	GLint specularExponentLocation			= glGetUniformLocation(shaderProgram.getIndex(), "specularExponent");
	GLint lightAttenuationLocation			= glGetUniformLocation(shaderProgram.getIndex(), "lightAttenuation");
	GLint gammaCorrectionLocation			= glGetUniformLocation(shaderProgram.getIndex(), "gamma");

	glUniform1f(lightAmbientCoefficientLocation, ambientCoefficient);
	glUniform1f(specularExponentLocation, specularExponent);
	glUniform1f(lightAttenuationLocation, lightAttenuation);
	glUniform1f(gammaCorrectionLocation, gamma);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		if (glfwGetKey(window, GLFW_KEY_LEFT))
		{
			lightPosition -= VEC3(3.0f * Time::deltaTime, 0.0f, 0.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT))
		{
			lightPosition += VEC3(3.0f * Time::deltaTime, 0.0f, 0.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_UP))
		{
			lightPosition += VEC3(0.0f, 3.0f * Time::deltaTime, 0.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN))
		{
			lightPosition -= VEC3(0.0f, 3.0f * Time::deltaTime, 0.0f);
		}

		glUniform3fv(lightUniformPositionLocation, 1, glm::value_ptr(lightPosition));
		glUniform3fv(lightUniformIntensityLocation, 1, glm::value_ptr(lightIntensity));

		quad.render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		Time::updateState();
	}

	glfwTerminate();

    return ERROR_NONE;
}