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
m_texture(),
m_shaderProgram(nullptr),
m_vertexBufferSize(),
m_elementBufferSize(),
m_textureBufferSize(),
m_textureWidth(),
m_textureHeight()
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureIndex);
}

Mesh::Mesh(ShaderProgram const & program)
:
transformUniform(),
m_texture(),
m_shaderProgram(&program),
m_vertexBufferSize(),
m_elementBufferSize(),
m_textureBufferSize(),
m_textureWidth()
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureIndex);
}

Mesh::Mesh(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureIndex, ShaderProgram const & program)
:
transformUniform(),
m_texture(),
m_shaderProgram(&program),
m_vertexBufferSize(),
m_elementBufferSize(),
m_textureBufferSize(),
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

GLboolean Mesh::loadTextureData(GLint width, GLint height, GLubyte const * data, GLsizeiptr size, Texture const & texture)
{
	if (width <= 0 || height <= 0)
	{
		return GL_FALSE;
	}

	m_textureBufferSize = size;
	m_textureWidth		= width;
	m_textureHeight		= height;

	GLenum target = texture.targetBinding;

	if (!isBufferBoundToState(m_textureIndex, target))
	{
		glBindTexture(target, m_textureIndex);
	}

	glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, texture.horizontalWrapMode);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, texture.verticalWrapMode);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, texture.minimizeFilter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, texture.magnifyFilter);
	glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(texture.borderColor));

	m_texture = texture;

	return GL_TRUE;
}

GLboolean Mesh::loadTextureFile(GLchar const * filename, Texture const & texture)
{
	ImageBuffer buffer;

	if (!buffer.load(filename))
	{
		return GL_FALSE;
	}

	return loadTextureData(buffer.getWidth(), buffer.getHeight(), buffer.getData(), buffer.getSize(), texture);
}

GLboolean Mesh::copyTextureData(Mesh const & other)
{
	GLsizeiptr const textureBufferSize = other.m_textureBufferSize;

	if (textureBufferSize == 0)
	{
		return GL_FALSE;
	}

	Texture const & texture = other.m_texture;
	GLenum const target = texture.targetBinding;

	unsigned char * textureImageData = new unsigned char[textureBufferSize];
	glGetTexImage(texture.targetBinding, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImageData);

	if (!loadTextureData(other.m_textureWidth, other.m_textureHeight, textureImageData, textureBufferSize, texture))
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
	m_shaderProgram->use();

	if (!isBoundToState(m_vertexArrayIndex, GL_VERTEX_ARRAY_BINDING))
	{
		glBindVertexArray(m_vertexArrayIndex);
	}

	if (!isBufferBoundToState(m_textureIndex, m_texture.targetBinding))
	{
		glBindTexture(m_texture.targetBinding, m_textureIndex);
	}

	draw();

	transformUniform.doBinding();

	update();
}

Mesh::~Mesh()
{
	glDeleteTextures(1, &m_textureIndex);
	glDeleteBuffers(1, &m_elementBufferIndex);
	glDeleteBuffers(1, &m_vertexBufferIndex);
	glDeleteVertexArrays(1, &m_vertexArrayIndex);
}