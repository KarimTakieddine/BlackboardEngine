#pragma once

#include "stdafx.h"

#include "BufferData.hpp"
#include "Image.h"
#include "TextureAttribute.h"
#include "TextureData.h"
#include "TransformUniform.h"
#include "VertexAttribute.h"

class Mesh
{

public:

	TransformUniform transformUniform;

	static GLboolean isBoundToState(GLuint index, GLenum binding);

	static GLboolean isBufferBoundToState(GLuint bufferIndex, GLenum target);

	static GLboolean copyBufferData(GLuint source, GLuint destination, GLsizeiptr size);

	template<typename T>
	static void bindBufferData(GLuint bufferIndex, BufferData<T> const & bufferData)
	{
		GLenum targetBuffer = bufferData.target;

		if (!isBufferBoundToState(bufferIndex, targetBuffer))
		{
			glBindBuffer(targetBuffer, bufferIndex);
		}

		glBufferData(targetBuffer, bufferData.size, bufferData.data, bufferData.usage);
	}

	Mesh();

	explicit Mesh(ShaderProgram const & program);

	explicit Mesh(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureIndex, ShaderProgram const & program);

	Mesh(Mesh const & other);

	Mesh & operator=(Mesh const & other);

	Mesh & copy(Mesh const & other);

	Mesh & bindVertexData(BufferData<GLfloat> const & vertexData);

	Mesh & bindElementData(BufferData<GLuint> const & elementData);

	GLboolean loadTextureData(GLubyte const * data, TextureData const & textureData, TextureAttribute const & textureAttribute);

	GLboolean loadTextureFile(GLchar const * filename, TextureAttribute const & textureAttribute);

	GLboolean copyTextureData(Mesh const & other);

	GLboolean bindVertexAttribute(GLboolean normalized, VertexAttribute const & attribute) const;

	void initializeTransformUniform(GLchar const * name);

	void render();

	virtual void initialize() = 0;

	virtual ~Mesh();

protected:

	virtual void draw() = 0;
	virtual void update() = 0;

	TextureAttribute m_textureAttribute;
	TextureData m_textureData;
	ShaderProgram const * m_shaderProgram;
	GLsizeiptr m_vertexBufferSize, m_elementBufferSize;
	GLuint m_vertexArrayIndex, m_vertexBufferIndex, m_elementBufferIndex, m_textureIndex;
};