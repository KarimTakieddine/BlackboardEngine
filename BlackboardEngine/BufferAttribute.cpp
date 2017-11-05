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