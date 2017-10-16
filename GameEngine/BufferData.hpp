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