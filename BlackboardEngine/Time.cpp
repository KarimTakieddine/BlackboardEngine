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