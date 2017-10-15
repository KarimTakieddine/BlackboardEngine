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
m_index(glCreateShader(m_type)),
m_sourceLength(other.m_sourceLength)
{
	std::vector<GLchar> buffer(m_sourceLength);
	glGetShaderSource(other.m_index, m_sourceLength, nullptr, &buffer[0]);
	compile(buffer.data());
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