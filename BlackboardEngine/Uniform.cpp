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
#include "Uniform.h"

Uniform::Uniform()
:
m_shaderLocation(-1)
{ }

Uniform::Uniform
(
	GLchar const * name,
	ShaderProgram const & program
)
{
	initialize(name, program);
}

void Uniform::initialize(GLchar const * name, ShaderProgram const & program)
{
	m_shaderLocation = glGetUniformLocation(program.getIndex(), name);
}

GLboolean Uniform::isValid() const
{
	return m_shaderLocation != -1;
}

GLboolean Uniform::doBinding()
{
	if (!isValid())
	{
		return GL_FALSE;
	}

	bind();

	return GL_TRUE;
}