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
	std::map<GLenum, GLenum>::const_iterator i = StateConstants::BufferTargetBindingMap.find(target);

	if (i == StateConstants::BufferTargetBindingMap.end())
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
m_shaderProgram(nullptr),
m_vertexBufferSize(),
m_elementBufferSize(),
m_textureBufferSize()
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureBufferIndex);
}

Mesh::Mesh(ShaderProgram const & program)
:
m_shaderProgram(&program),
m_vertexBufferSize(),
m_elementBufferSize(),
m_textureBufferSize()
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureBufferIndex);
}

Mesh::Mesh(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureBufferIndex, ShaderProgram const & program)
:
m_shaderProgram(&program),
m_vertexBufferSize(),
m_elementBufferSize(),
m_textureBufferSize(),
m_vertexArrayIndex(vertexArrayIndex),
m_vertexBufferIndex(vertexBufferIndex),
m_elementBufferIndex(elementBufferIndex),
m_textureBufferIndex(textureBufferIndex)
{ }

Mesh::Mesh(Mesh const & other)
:
m_shaderProgram(other.m_shaderProgram),
m_vertexBufferSize(other.m_vertexBufferSize),
m_elementBufferSize(other.m_elementBufferSize),
m_textureBufferSize(other.m_textureBufferSize)
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureBufferIndex);

	copy(other);
}

Mesh & Mesh::operator=(Mesh const & other)
{
	m_shaderProgram = other.m_shaderProgram;

	m_vertexBufferSize = other.m_vertexBufferSize,
	m_elementBufferSize = other.m_elementBufferSize;
	m_textureBufferSize = other.m_textureBufferSize;

	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureBufferIndex);

	return copy(other);
}

Mesh & Mesh::copy(Mesh const & other)
{
	copyBufferData(other.m_vertexBufferIndex, m_vertexBufferIndex, other.m_vertexBufferSize);

	copyBufferData(other.m_elementBufferIndex, m_elementBufferIndex, other.m_elementBufferSize);

	//TODO: Copy texture data

	return *this;
}

Mesh & Mesh::bindVertexData(BufferData<GLfloat> const & vertexData)
{
	m_vertexBufferSize = vertexData.size;

	bindBufferData<GLfloat>(m_vertexBufferIndex, vertexData);

	return *this;
}

GLboolean Mesh::bindVertexAttribute(GLboolean normalized, VertexAttribute const & attribute) const
{
	if (!isBoundToState(m_vertexArrayIndex, GL_VERTEX_ARRAY_BINDING))
	{
		glBindVertexArray(m_vertexArrayIndex);
	}

	return attribute.bind(normalized);
}

void Mesh::render()
{
	m_shaderProgram->use();

	if (!isBoundToState(m_vertexArrayIndex, GL_VERTEX_ARRAY_BINDING))
	{
		glBindVertexArray(m_vertexArrayIndex);
	}

	draw();
}

Mesh::~Mesh()
{
	glDeleteTextures(1, &m_textureBufferIndex);
	glDeleteBuffers(1, &m_elementBufferIndex);
	glDeleteBuffers(1, &m_vertexBufferIndex);
	glDeleteVertexArrays(1, &m_vertexArrayIndex);
}