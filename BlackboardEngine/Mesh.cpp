/*	--------------------###############################################################################----------------------

*	Copyright (c) 2017 Karim Takieddine

*	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
*	documentation files (the "Software"), to deal in the Software without restriction, including without limitation
*	the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
*	to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*	The above copyright notice and this permission notice shall be included in allcopies or substantial portions of
*	the Software.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
*	TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*	--------------------###############################################################################--------------------- */

#include "stdafx.h"
#include "Mesh.hpp"
#include "StateConstants.h"

GLboolean Mesh::isBoundToState(GLuint index, GLenum binding)
{
	GLint currentIndex;
	glGetIntegerv(binding, &currentIndex);

	return index == currentIndex;
}

GLboolean Mesh::isBufferBoundToState(GLuint bufferIndex, GLenum target)
{
	std::map<GLenum, GLenum>::const_iterator i = StateConstants::TargetToBindingLookupMap.find(target);

	if (i == StateConstants::TargetToBindingLookupMap.end())
	{
		return GL_FALSE;
	}

	return isBoundToState(bufferIndex, i->second);
}

GLboolean Mesh::copyBufferData(GLuint source, GLuint destination, GLsizeiptr size)
{
	if (size == 0)
	{
		return GL_FALSE;
	}

	glBindBuffer(GL_COPY_READ_BUFFER, source);
	glBindBuffer(GL_COPY_WRITE_BUFFER, destination);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

	return GL_TRUE;
}

Mesh::Mesh()
:
transformUniform(),
m_textureAttribute(),
m_textureData(),
m_shaderProgram(nullptr),
m_vertexBufferSize(),
m_elementBufferSize()
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureIndex);
}

Mesh::Mesh(ShaderProgram const & program)
:
transformUniform(),
m_textureAttribute(),
m_textureData(),
m_shaderProgram(&program),
m_vertexBufferSize(),
m_elementBufferSize()
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureIndex);
}

Mesh::Mesh(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureIndex, ShaderProgram const & program)
:
transformUniform(),
m_textureAttribute(),
m_textureData(),
m_shaderProgram(&program),
m_vertexBufferSize(),
m_elementBufferSize(),
m_vertexArrayIndex(vertexArrayIndex),
m_vertexBufferIndex(vertexBufferIndex),
m_elementBufferIndex(elementBufferIndex),
m_textureIndex(textureIndex)
{ }

Mesh::Mesh(Mesh const & other)
:
transformUniform(other.transformUniform),
m_shaderProgram(other.m_shaderProgram),
m_vertexBufferSize(other.m_vertexBufferSize)
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureIndex);

	copy(other);
}

Mesh & Mesh::operator=(Mesh const & other)
{
	transformUniform = other.transformUniform;
	m_shaderProgram = other.m_shaderProgram;

	m_vertexBufferSize = other.m_vertexBufferSize;

	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureIndex);

	return copy(other);
}

Mesh & Mesh::copy(Mesh const & other)
{
	if (!isBoundToState(m_vertexArrayIndex, GL_VERTEX_ARRAY_BINDING))
	{
		glBindVertexArray(m_vertexArrayIndex);
	}

	copyBufferData(other.m_vertexBufferIndex, m_vertexBufferIndex, other.m_vertexBufferSize);

	bindElementData(BufferData<GLuint>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, nullptr, other.m_elementBufferSize));

	copyBufferData(other.m_elementBufferIndex, m_elementBufferIndex, other.m_elementBufferSize);

	copyTextureData(other);

	return *this;
}

Mesh & Mesh::bindVertexData(BufferData<GLfloat> const & vertexData)
{
	m_vertexBufferSize = vertexData.size;

	bindBufferData<GLfloat>(m_vertexBufferIndex, vertexData);

	return *this;
}

Mesh & Mesh::bindElementData(BufferData<GLuint> const & elementData)
{
	m_elementBufferSize = elementData.size;

	bindBufferData<GLuint>(m_elementBufferIndex, elementData);

	return *this;
}

GLboolean Mesh::loadTextureData(GLubyte const * data, TextureData const & textureData, TextureAttribute const & textureAttribute)
{
	if (!textureData.isValid())
	{
		return GL_FALSE;
	}

	GLenum target = textureAttribute.targetBinding;

	if (!isBufferBoundToState(m_textureIndex, target))
	{
		glBindTexture(target, m_textureIndex);
	}

	glTexImage2D(target, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(target,		GL_TEXTURE_WRAP_S,			textureAttribute.horizontalWrapMode);
	glTexParameteri(target,		GL_TEXTURE_WRAP_T,			textureAttribute.verticalWrapMode);
	glTexParameteri(target,		GL_TEXTURE_MIN_FILTER,		textureAttribute.minimizeFilter);
	glTexParameteri(target,		GL_TEXTURE_MAG_FILTER,		textureAttribute.magnifyFilter);
	glTexParameterfv(target,	GL_TEXTURE_BORDER_COLOR,	glm::value_ptr(textureAttribute.borderColor));

	m_textureAttribute	= textureAttribute;
	m_textureData		= textureData;

	return GL_TRUE;
}

GLboolean Mesh::loadTextureFile(GLchar const * filename, TextureAttribute const & texture)
{
	ImageBuffer buffer;

	if (!buffer.load(filename))
	{
		return GL_FALSE;
	}

	return loadTextureData(buffer.getData(), TextureData(buffer.getWidth(), buffer.getHeight(), buffer.getSize()), texture);
}

GLboolean Mesh::copyTextureData(Mesh const & other)
{
	TextureData const & textureData = other.m_textureData;

	if (textureData.size == 0)
	{
		return GL_FALSE;
	}

	TextureAttribute const & textureAttribute	= other.m_textureAttribute;
	GLenum const target							= textureAttribute.targetBinding;
	GLsizeiptr const size						= textureData.size;
	unsigned char * textureImageData			= new unsigned char[size];

	glGetTexImage(target, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImageData);

	if (!loadTextureData(textureImageData, textureData, textureAttribute))
	{
		delete[](textureImageData);
		return GL_FALSE;
	}

	delete[](textureImageData);
	return GL_TRUE;
}

GLboolean Mesh::bindVertexAttribute(GLboolean normalized, VertexAttribute const & attribute) const
{
	if (!isBoundToState(m_vertexArrayIndex, GL_VERTEX_ARRAY_BINDING))
	{
		glBindVertexArray(m_vertexArrayIndex);
	}

	return attribute.bind(normalized);
}

void Mesh::initializeTransformUniform(GLchar const * name)
{
	transformUniform.initialize(name, *m_shaderProgram);
}

void Mesh::render()
{
	update();

	m_shaderProgram->use();

	transformUniform.doBinding();

	if (!isBoundToState(m_vertexArrayIndex, GL_VERTEX_ARRAY_BINDING))
	{
		glBindVertexArray(m_vertexArrayIndex);
	}

	if (!isBufferBoundToState(m_textureIndex, m_textureAttribute.targetBinding))
	{
		glBindTexture(m_textureAttribute.targetBinding, m_textureIndex);
	}

	draw();
}

Mesh::~Mesh()
{
	glDeleteTextures(1, &m_textureIndex);
	glDeleteBuffers(1, &m_elementBufferIndex);
	glDeleteBuffers(1, &m_vertexBufferIndex);
	glDeleteVertexArrays(1, &m_vertexArrayIndex);
}