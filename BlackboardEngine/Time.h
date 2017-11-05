#pragma once

#include "stdafx.h"

class Time
{

public:

	static std::chrono::time_point<std::chrono::steady_clock>	startPoint, currentPoint;
	static GLfloat												elapsedTime, deltaTime;
	static GLuint												frameCount;

	static void updateState();

};