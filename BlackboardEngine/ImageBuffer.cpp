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
#include "ImageBuffer.h"

ImageBuffer::ImageBuffer()
:
m_data(nullptr),
m_size(),
m_width(),
m_height()
{ }

ImageBuffer::ImageBuffer(ImageBuffer const & other)
:
m_width(other.getWidth()),
m_height(other.getHeight()),
m_size(other.getSize())
{
	m_data = new GLubyte[m_size];
	memcpy(m_data, other.getData(), m_size);
}

GLboolean ImageBuffer::load(GLchar const * filename)
{
	if (m_data)
	{
		SOIL_free_image_data(m_data);
	}

	m_data = SOIL_load_image(filename, &m_width, &m_height, nullptr, SOIL_LOAD_RGB);
	m_size = m_width * m_height * sizeof(RGBColor);

	return m_data ? GL_TRUE : GL_FALSE;
}

GLboolean ImageBuffer::loadData(GLsizei width, GLsizei height, GLubyte const * data)
{
	if (width == 0 || height == 0)
	{
		return GL_FALSE;
	}

	m_width		= width;
	m_height	= height;
	m_size		= m_width * m_height * sizeof(RGBColor);

	if (m_data)
	{
		SOIL_free_image_data(m_data);
	}

	m_data = new GLubyte[m_size];
	memcpy(m_data, data, m_size);

	return GL_TRUE;
}

GLint ImageBuffer::getWidth() const
{
	return m_width;
}

GLint ImageBuffer::getHeight() const
{
	return m_height;
}

GLsizeiptr ImageBuffer::getSize() const
{
	return m_size;
}

GLubyte const * ImageBuffer::getData() const
{
	return m_data;
}

ImageBuffer::~ImageBuffer()
{
	SOIL_free_image_data(m_data);
}