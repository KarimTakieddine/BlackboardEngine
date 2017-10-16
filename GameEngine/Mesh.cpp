#include "stdafx.h"
#include "Mesh.hpp"

void Mesh::copyBufferData(GLuint source, GLuint destination, GLsizeiptr size)
{
	glBindBuffer(GL_COPY_READ_BUFFER, source);
	glBindBuffer(GL_COPY_WRITE_BUFFER, destination);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
}

Mesh::Mesh()
:
m_shaderProgram(nullptr)
{
	glGenVertexArrays(1, &m_vertexArrayIndex);
	glGenBuffers(1, &m_vertexBufferIndex);
	glGenBuffers(1, &m_elementBufferIndex);
	glGenTextures(1, &m_textureBufferIndex);
}

Mesh::Mesh(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureBufferIndex, ShaderProgram const & program)
:
m_shaderProgram(&program),
m_vertexArrayIndex(vertexArrayIndex),
m_vertexBufferIndex(vertexBufferIndex),
m_elementBufferIndex(elementBufferIndex),
m_textureBufferIndex(textureBufferIndex)
{ }

Mesh::Mesh(Mesh const & other)
:
m_shaderProgram(other.m_shaderProgram)
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

GLboolean Mesh::bindVertexAttribute(GLboolean normalized, VertexAttribute const & attribute) const
{
	return attribute.bind(normalized);
}

Mesh::~Mesh()
{
	glDeleteTextures(1, &m_textureBufferIndex);
	glDeleteBuffers(1, &m_elementBufferIndex);
	glDeleteBuffers(1, &m_vertexBufferIndex);
	glDeleteVertexArrays(1, &m_vertexArrayIndex);
}