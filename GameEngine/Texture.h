#pragma once

#include "stdafx.h"

struct Texture
{

	VEC3 borderColor;
	GLenum targetBinding;
	GLenum horizontalWrapMode, verticalWrapMode;
	GLenum minimizeFilter, magnifyFilter;

	Texture();

	Texture
	(
		GLenum minFilter,
		GLenum magFilter,
		GLenum hWrapMode,
		GLenum vWrapMode,
		GLenum tBinding,
		VEC3 const & bColor
	);

	Texture(Texture const & other);

};