#pragma once

#include "stdafx.h"
#include "RGBColor.h"

class ImageBuffer
{

public:

	ImageBuffer();

	ImageBuffer(ImageBuffer const & other);

	GLboolean load(GLchar const * filename);

	GLint getWidth() const;

	GLint getHeight() const;

	GLsizeiptr getSize() const;

	GLubyte const * getData() const;

	~ImageBuffer();

private:

	GLubyte * m_data;
	GLsizeiptr m_size;
	GLint m_width, m_height;

};