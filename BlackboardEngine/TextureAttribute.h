#pragma once

#include "stdafx.h"

struct TextureAttribute
{

	VEC3	borderColor;
	GLenum	targetBinding;
	GLenum	horizontalWrapMode,	verticalWrapMode;
	GLenum	minimizeFilter, magnifyFilter;

	TextureAttribute();

	TextureAttribute
	(
		GLenum			minFilter,
		GLenum			magFilter,
		GLenum			hWrapMode,
		GLenum			vWrapMode,
		GLenum			tBinding,
		VEC3 const &	bColor
	);

	TextureAttribute
	(
		TextureAttribute const & other
	);

};