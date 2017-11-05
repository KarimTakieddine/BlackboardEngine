#include "stdafx.h"
#include "TextureAttribute.h"

TextureAttribute::TextureAttribute()
:
borderColor			(1.0f, 1.0f, 1.0f),
targetBinding		(GL_TEXTURE_2D),
horizontalWrapMode	(GL_REPEAT),
verticalWrapMode	(GL_REPEAT),
minimizeFilter		(GL_LINEAR),
magnifyFilter		(GL_LINEAR)
{ }

TextureAttribute::TextureAttribute
(
	GLenum			minFilter,
	GLenum			magFilter,
	GLenum			hWrapMode,
	GLenum			vWrapMode,
	GLenum			tBinding,
	VEC3 const &	bColor
)
:
borderColor			(bColor),
targetBinding		(tBinding),
horizontalWrapMode	(hWrapMode),
verticalWrapMode	(vWrapMode),
minimizeFilter		(minFilter),
magnifyFilter		(magFilter)
{

}

TextureAttribute::TextureAttribute
(
	TextureAttribute const & other
)
:
borderColor				(other.borderColor),
targetBinding			(other.targetBinding),
horizontalWrapMode		(other.horizontalWrapMode),
verticalWrapMode		(other.verticalWrapMode),
minimizeFilter			(other.minimizeFilter),
magnifyFilter			(other.magnifyFilter)
{ }