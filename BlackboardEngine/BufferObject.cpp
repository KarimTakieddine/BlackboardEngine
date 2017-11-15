#include "stdafx.h"
#include "BufferObject.h"

BufferObject::BufferObject()
:
m_size	(),
m_target(GL_BUFFER)
{
	glGenBuffers(1, &m_index);
}

BufferObject::BufferObject
(
	GLenum target
)
:
m_size	(),
m_target(target)
{
	glGenBuffers(1, &m_index);
}

BufferObject::BufferObject
(
	GLenum		target,
	GLsizeiptr	size
)
:
m_size	(size),
m_target(target)
{
	glGenBuffers(1, &m_index);
}

BufferObject::BufferObject
(
	GLenum		target,
	GLuint		index,
	GLsizeiptr	size
)
:
m_size	(size),
m_index	(index),
m_target(target)
{ }

BufferObject::BufferObject
(
	BufferObject const & other
)
:
m_size	(other.m_size),
m_target(other.m_target)
{
	glGenBuffers(1, &m_index);
	lazyBind();
	setData(GL_STATIC_DRAW, nullptr);
	other.bindToTarget(GL_COPY_READ_BUFFER);
	bindToTarget(GL_COPY_WRITE_BUFFER);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_size);
}

void BufferObject::bindToTarget
(
	GLenum target
) const
{
	glBindBuffer(target, m_index);
}

void BufferObject::bind() const
{
	bindToTarget(m_target);
}

void BufferObject::lazyBind() const
{
	if (isBoundToState())
	{
		return;
	}

	bind();
}

GLboolean BufferObject::isBoundToState() const
{
	GLint boundIndex;

	std::map<GLenum, GLenum>::const_iterator i = GLInfo::BufferBindingMap.find(m_target);

	if (i == GLInfo::BufferBindingMap.end())
	{
		return GL_FALSE;
	}

	glGetIntegerv(i->second, &boundIndex);

	return m_index == boundIndex;
}

GLboolean BufferObject::isValid() const
{
	return m_index != 0;
}

void BufferObject::setSize
(
	GLsizeiptr size
)
{
	m_size = size;
}

void BufferObject::setData
(
	GLenum			usage,
	void const *	data
)
{
	glBufferData(m_target, m_size, data, usage);
}

GLsizeiptr BufferObject::getSize() const
{
	return m_size;
}

BufferObject::~BufferObject()
{
	if (isValid())
	{
		glDeleteBuffers(1, &m_index);
	}
}