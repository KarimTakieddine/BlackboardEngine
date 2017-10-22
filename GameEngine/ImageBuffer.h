#pragma once

#include "stdafx.h"

class ImageBuffer
{

public:

	ImageBuffer();

	ImageBuffer(ImageBuffer const & other);

	GLboolean load(GLchar const * filename);

	GLint getWidth() const;

	GLint getHeight() const;

	GLubyte const * getData() const;

	~ImageBuffer();

private:

	GLubyte * m_data;
	GLint m_width, m_height;

};