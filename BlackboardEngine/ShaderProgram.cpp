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
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
:
m_shaderList(),
m_index(glCreateProgram()),
m_linkStatus()
{ }

ShaderProgram::ShaderProgram(ShaderProgram const & other)
:
m_shaderList(),
m_index(glCreateProgram()),
m_linkStatus()
{
	copy(other);
}

ShaderProgram & ShaderProgram::operator=(ShaderProgram const & other)
{
	m_shaderList = std::vector<Shader const *>();
	m_index = glCreateProgram();

	return copy(other);
}

ShaderProgram & ShaderProgram::attachShader(Shader const & shader)
{
	glAttachShader(m_index, shader.getIndex());
	m_shaderList.push_back(&shader);
	return *this;
}

ShaderProgram & ShaderProgram::copy(ShaderProgram const & other)
{
	for (std::vector<Shader const *>::const_iterator i = other.m_shaderList.begin(); i != other.m_shaderList.end(); ++i)
	{
		attachShader(*(*i));
	}

	link();

	return *this;
}

GLboolean ShaderProgram::detachShader(Shader const & shader)
{
	GLuint index = shader.getIndex();

	for (std::vector<Shader const *>::const_iterator i = m_shaderList.begin(); i != m_shaderList.end(); ++i)
	{
		if ((*i)->getIndex() == index)
		{
			glDetachShader(m_index, index);
			m_shaderList.erase(i);
			return GL_TRUE;
		}
	}

	return GL_FALSE;
}

GLboolean ShaderProgram::link()
{
	for (std::vector<Shader const *>::const_iterator i = m_shaderList.begin(); i != m_shaderList.end(); ++i)
	{
		if (!(*i)->isCompiled())
		{
			return GL_FALSE;
		}
	}

	glLinkProgram(m_index);
	glGetProgramiv(m_index, GL_LINK_STATUS, &m_linkStatus);

	return GL_TRUE;
}

GLboolean ShaderProgram::isLinked() const
{
	return m_linkStatus == GL_TRUE;
}

void ShaderProgram::use() const
{
	glUseProgram(m_index);
}

GLuint ShaderProgram::getIndex() const
{
	return m_index;
}

ShaderProgram::~ShaderProgram()
{
	for (std::vector<Shader const *>::const_iterator i = m_shaderList.begin(); i != m_shaderList.end(); ++i)
	{
		glDetachShader(m_index, (*i)->getIndex());
	}

	glDeleteProgram(m_index);
}