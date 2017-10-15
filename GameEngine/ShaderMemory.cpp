#include "stdafx.h"
#include "ShaderMemory.h"

ShaderMemory::ShaderMemory()
:
bufferAttribute(),
m_location(-1)
{ }

ShaderMemory::ShaderMemory(GLchar const * name, BufferAttribute const & attribute, ShaderProgram const & program)
:
bufferAttribute(attribute)
{
	initialize(name, program);
}

ShaderMemory::ShaderMemory(ShaderMemory const & other)
:
bufferAttribute(other.bufferAttribute),
m_location(other.m_location)
{ }

void ShaderMemory::initialize(GLchar const * name, ShaderProgram const & program)
{
	m_location = glGetAttribLocation(program.getIndex(), name);
}

GLint ShaderMemory::getLocation() const
{
	return m_location;
}

GLboolean ShaderMemory::isValid() const
{
	return m_location != -1;
}