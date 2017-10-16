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