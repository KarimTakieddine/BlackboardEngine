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

#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "OpenAL\al.h"
#include "OpenAL\alc.h"
#include "OpenAL\CWaves.h"

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"

#include "glm\matrix.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "SOIL\SOIL.h"

#define GLM_FORCE_RADIANS

typedef glm::vec2 VEC2;
typedef glm::vec3 VEC3;
typedef glm::vec4 VEC4;
typedef glm::mat2 MAT22;
typedef glm::mat3 MAT33;
typedef glm::mat4 MAT44;