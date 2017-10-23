#include "stdafx.h"
#include "Image.h"

Image::Image()
:
m_pixelBuffer(nullptr),
m_size()
{ }

Image::Image(Image const & other)
:
m_size(other.m_size)
{
	m_pixelBuffer = new RGBColor[m_size];
	memcpy(m_pixelBuffer, other.getPixelBuffer(), m_size);
}

GLboolean Image::loadFromBuffer(ImageBuffer const & buffer)
{
	m_size = buffer.getSize();

	if (m_size == 0)
	{
		return GL_FALSE;
	}

	if (m_pixelBuffer)
	{
		delete[](m_pixelBuffer);
	}

	m_pixelBuffer = new RGBColor[m_size];

	GLubyte const * bufferData = buffer.getData();

	for (int i = 0; i < buffer.getHeight(); ++i)
	{
		for (int j = 0; j < buffer.getWidth(); ++j)
		{
			GLubyte red = *bufferData++;
			GLubyte green = *bufferData++;
			GLubyte blue = *bufferData++;

			m_pixelBuffer[i * buffer.getWidth() + j] = RGBColor(red, green, blue);
		}
	}

	return GL_TRUE;
}

RGBColor * Image::pixelBuffer()
{
	return const_cast<RGBColor *>(static_cast<Image const &>(*this).getPixelBuffer());
}

RGBColor const * Image::getPixelBuffer() const
{
	return m_pixelBuffer;
}

GLubyte const * Image::getRawData() const
{
	return &(m_pixelBuffer[0].red);
}

Image::~Image()
{
	delete[](m_pixelBuffer);
}