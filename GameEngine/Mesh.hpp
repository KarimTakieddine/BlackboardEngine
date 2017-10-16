#pragma once

#include "stdafx.h"

#include "BufferData.hpp"
#include "ShaderProgram.h"
#include "VertexAttribute.h"

class Mesh
{

public:

	static void copyBufferData(GLuint source, GLuint destination, GLsizeiptr size);

	template<typename T>
	static void bindBufferData(GLuint bufferIndex, BufferData<T> const & bufferData)
	{
		GLenum targetBuffer = bufferData.target;

		//TODO: Implement lazy binding semantics

		glBindBuffer(targetBuffer, bufferIndex);
		glBufferData(targetBuffer, bufferData.size, bufferData.data, bufferData.usage);
	}

	Mesh();

	explicit Mesh(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureBufferIndex, ShaderProgram const & program);

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