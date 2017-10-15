#include "stdafx.h"
#include "BufferAttribute.h"

BufferAttribute::BufferAttribute()
:
stride(),
offset(),
count(),
type(GL_TYPE)
{ }

BufferAttribute::BufferAttribute(GLenum type, GLint count, GLsizei offset, GLsizei stride)
:
stride(stride),
offset(offset),
count(count),
type(type)
{ }

BufferAttribute::BufferAttribute(BufferAttribute const & other)
:
stride(other.stride),
offset(other.offset),
count(other.count),
type(other.type)
{ }

BufferAttribute & BufferAttribute::operator=(BufferAttribute const & other)
{
	stride = other.stride;
	offset = other.offset;
	count = other.count;
	type = other.type;

	return *this;
}