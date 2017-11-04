#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
:
borderColor(1.0f, 1.0f, 1.0f),
targetBinding(GL_TEXTURE_2D),
horizontalWrapMode(GL_REPEAT),
verticalWrapMode(GL_REPEAT),
minimizeFilter(GL_LINEAR),
magnifyFilter(GL_LINEAR)
{ }

Texture::Texture
(
	GLenum minFilter,
	GLenum magFilter,
	GLenum hWrapMode,
	GLenum vWrapMode,
	GLenum tBinding,
	VEC3 const & bColor
)
:
borderColor(bColor),
targetBinding(tBinding),
horizontalWrapMode(hWrapMode),
verticalWrapMode(vWrapMode),
minimizeFilter(minFilter),
magnifyFilter(magFilter)
{

}

Texture::Texture(Texture const & other)
:
borderColor(other.borderColor),
targetBinding(other.targetBinding),
horizontalWrapMode(other.horizontalWrapMode),
verticalWrapMode(other.verticalWrapMode),
minimizeFilter(other.minimizeFilter),
magnifyFilter(other.magnifyFilter)
{ }