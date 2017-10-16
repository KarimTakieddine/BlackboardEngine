#pragma once

#include "stdafx.h"

#include "ShaderProgram.h"
#include "VertexAttribute.h"

class Mesh
{

public:

	static void copyBufferData(GLuint source, GLuint destination, GLsizeiptr size);

	Mesh();

	Mesh(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureBufferIndex, ShaderProgram const & program);

	Mesh(Mesh const & other);

	Mesh & operator=(Mesh const & other);

	Mesh & copy(Mesh const & other);

	GLboolean bindVertexAttribute(GLboolean normalized, VertexAttribute const & attribute) const;

	~Mesh();

private:

	ShaderProgram const * m_shaderProgram;
	GLsizeiptr m_vertexBufferSize, m_elementBufferSize;
	GLuint m_vertexArrayIndex, m_vertexBufferIndex, m_elementBufferIndex, m_textureBufferIndex;

};