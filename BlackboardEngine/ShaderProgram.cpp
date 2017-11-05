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