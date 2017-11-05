#include "stdafx.h"
#include "StateConstants.h"

const std::map<GLenum, GLenum> StateConstants::TargetToBindingLookupMap =
{
	{ GL_ARRAY_BUFFER,			GL_ARRAY_BUFFER_BINDING			},
	{ GL_ELEMENT_ARRAY_BUFFER,	GL_ELEMENT_ARRAY_BUFFER_BINDING },
	{ GL_TEXTURE_2D,			GL_TEXTURE_BINDING_2D			}
};