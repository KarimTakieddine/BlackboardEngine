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
#include "Shader.h"

Shader::Shader()
:
m_type(GL_SHADER),
m_index(glCreateShader(m_type)),
m_compileStatus(),
m_sourceLength()
{ }

Shader::Shader(GLenum type)
:
m_type(type),
m_index(glCreateShader(type)),
m_compileStatus(),
m_sourceLength()
{ }

Shader::Shader(Shader const & other)
:
m_type(other.m_type),
m_index(glCreateShader(m_type))
{
	copy(other);
}

Shader & Shader::copy(Shader const & other)
{
	m_sourceLength = other.m_sourceLength;
	std::vector<GLchar> buffer(m_sourceLength);
	glGetShaderSource(other.m_index, m_sourceLength, nullptr, &buffer[0]);

	return compile(buffer.data());
}

Shader & Shader::operator=(Shader const & other)
{
	m_type = other.m_type;
	m_index = glCreateShader(m_type);

	return copy(other);
}

Shader & Shader::compile(GLchar const * buffer)
{
	glShaderSource(m_index, 1, &buffer, nullptr);
	glCompileShader(m_index);
	glGetShaderiv(m_index, GL_COMPILE_STATUS, &m_compileStatus);
	return *this;
}

GLboolean Shader::loadFile(GLchar const * file)
{
	std::vector<GLchar> buffer;

	if (!File::read(file, buffer))
	{
		return GL_FALSE;
	}

	m_sourceLength = buffer.size();

	compile(buffer.data());

	return GL_TRUE;
}

GLuint Shader::getIndex() const
{
	return m_index;
}

GLboolean Shader::isCompiled() const
{
	return m_compileStatus == GL_TRUE;
}

Shader::~Shader()
{
	glDeleteShader(m_index);
}