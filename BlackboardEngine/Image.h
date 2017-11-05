#pragma once

#include "stdafx.h"
#include "ImageBuffer.h"

class Image
{

public:

	Image();

	Image(Image const & other);

	GLboolean loadFromBuffer(ImageBuffer const & buffer);

	RGBColor * pixelBuffer();

	RGBColor const * getPixelBuffer() const;

	GLubyte const * getRawData() const;

	~Image();

private:

	RGBColor * m_pixelBuffer;
	GLsizeiptr m_size;

};