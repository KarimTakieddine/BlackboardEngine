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