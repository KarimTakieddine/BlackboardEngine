#pragma once

#include "stdafx.h"

struct BufferAttribute
{

	GLsizei stride, offset;
	GLint count;
	GLenum type;

	BufferAttribute();

	explicit BufferAttribute(GLenum type, GLint count, GLsizei offset, GLsizei stride);

	BufferAttribute(BufferAttribute const & other);

	BufferAttribute & operator=(BufferAttribute const & other);

};