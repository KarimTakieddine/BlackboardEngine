#include "stdafx.h"
#include "Time.h"

std::chrono::time_point<std::chrono::steady_clock>	Time::startPoint	= std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock>	Time::currentPoint	= Time::startPoint;

GLfloat												Time::elapsedTime	= 0.0f;
GLfloat												Time::deltaTime		= 0.0f;

GLuint												Time::frameCount	= 1;

void Time::updateState()
{
	currentPoint	= std::chrono::steady_clock::now();
	elapsedTime		= std::chrono::duration_cast<std::chrono::duration<GLfloat>>(currentPoint - startPoint).count();
	deltaTime		= elapsedTime / frameCount;

	++frameCount;
}