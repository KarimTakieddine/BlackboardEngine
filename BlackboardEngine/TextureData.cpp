#include "stdafx.h"
#include "TextureData.h"

TextureData::TextureData()
:
size	(),
width	(),
height	()
{ }

TextureData::TextureData
(
	GLsizei		w,
	GLsizei		h,
	GLsizeiptr	sz
)
:
size	(sz),
width	(w),
height	(h)
{ }

TextureData::TextureData
(
	TextureData const & other
)
:
size	(other.size),
width	(other.width),
height	(other.height)
{ }

GLboolean TextureData::isValid() const
{
	return width > 0 && height > 0 && size > 0;
}
