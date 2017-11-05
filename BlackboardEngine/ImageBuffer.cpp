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