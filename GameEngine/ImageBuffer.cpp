#include "stdafx.h"
#include "ImageBuffer.h"

ImageBuffer::ImageBuffer()
:
m_width(),
m_height(),
m_data(nullptr)
{ }

ImageBuffer::ImageBuffer(ImageBuffer const & other)
:
m_width(other.m_width),
m_height(other.m_height)
{
	if (m_data)
	{
		SOIL_free_image_data(m_data);
	}

	size_t size = m_width * m_height * 3;

	m_data = new GLubyte[size];
	memcpy(m_data, other.getData(), size);
}

GLboolean ImageBuffer::load(GLchar const * filename)
{
	m_data = SOIL_load_image(filename, &m_width, &m_height, nullptr, SOIL_LOAD_RGB);

	return m_data ? GL_TRUE : GL_FALSE;
}

GLint ImageBuffer::getWidth() const
{
	return m_width;
}

GLint ImageBuffer::getHeight() const
{
	return m_height;
}

GLubyte const * ImageBuffer::getData() const
{
	return m_data;
}

ImageBuffer::~ImageBuffer()
{
	SOIL_free_image_data(m_data);
}