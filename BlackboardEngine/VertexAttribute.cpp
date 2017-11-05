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
#include "VertexAttribute.h"

VertexAttribute::VertexAttribute()
:
bufferAttribute(),
m_shaderLocation(-1)
{ }

VertexAttribute::VertexAttribute(GLchar const * name, BufferAttribute const & attribute, ShaderProgram const & program)
:
bufferAttribute(attribute)
{
	initialize(name, program);
}

VertexAttribute::VertexAttribute(VertexAttribute const & other)
:
bufferAttribute(other.bufferAttribute),
m_shaderLocation(other.m_shaderLocation)
{ }

void VertexAttribute::initialize(GLchar const * name, ShaderProgram const & program)
{
	m_shaderLocation = glGetAttribLocation(program.getIndex(), name);
}

GLboolean VertexAttribute::bind(GLboolean normalized) const
{
	if (!isValid())
	{
		return GL_FALSE;
	}

	glEnableVertexAttribArray(m_shaderLocation);
	glVertexAttribPointer(m_shaderLocation, bufferAttribute.count, bufferAttribute.type, normalized, bufferAttribute.stride, reinterpret_cast<void const *>(bufferAttribute.offset));

	return GL_TRUE;
}

GLint VertexAttribute::getLocation() const
{
	return m_shaderLocation;
}

GLboolean VertexAttribute::isValid() const
{
	return m_shaderLocation != -1;
}