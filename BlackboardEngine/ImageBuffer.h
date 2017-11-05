#pragma once

#include "stdafx.h"
#include "RGBColor.h"

class ImageBuffer
{

public:

	ImageBuffer();

	ImageBuffer(ImageBuffer const & other);

	GLboolean load(GLchar const * filename);

	GLboolean loadData(GLsizei width, GLsizei height, GLubyte const * data);

	GLsizei getWidth() const;

	GLsizei getHeight() const;

	GLsizeiptr getSize() const;

	GLubyte const * getData() const;

	~ImageBuffer();

private:

	GLubyte * m_data;
	GLsizeiptr m_size;
	GLsizei m_width, m_height;

};