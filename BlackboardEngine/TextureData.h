#pragma once

#include "stdafx.h"

struct TextureData
{
	GLsizeiptr size;
	GLsizei width, height;

	TextureData();

	explicit TextureData
	(
		GLsizei		w,
		GLsizei		h, 
		GLsizeiptr	sz
	);

	TextureData
	(
		TextureData const & other
	);

	GLboolean isValid() const;
};