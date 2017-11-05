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

#pragma once

#include "stdafx.h"

template<typename T>
struct BufferData
{

	GLsizeiptr size;
	T const * data;
	GLenum target, usage;

	BufferData()
	:
	size(),
	data(nullptr),
	target(GL_BUFFER),
	usage(GL_STATIC_DRAW)
	{ }


	BufferData(GLenum target, GLenum usage, T const * data, GLsizeiptr size)
	:
	size(size),
	data(data),
	target(target),
	usage(usage)
	{ }

	BufferData(BufferData<T> const & other)
	:
	size(other.size),
	data(other.data),
	target(other.target),
	usage(other.usage)
	{ }

	BufferData & operator=(BufferData<T> const & other)
	{
		size = other.size;
		data = other.data;
		target = other.target;
		usage = other.usage;

		return *this;
	}

};