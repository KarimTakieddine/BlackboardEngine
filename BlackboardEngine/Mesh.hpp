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

#pragma once

#include "stdafx.h"

#include "BufferData.hpp"
#include "Image.h"
#include "TextureAttribute.h"
#include "TextureData.h"
#include "TransformUniform.h"
#include "VertexAttribute.h"

enum RenderFlag
{
	VERTEX_COLORED	= 0x00000000,
	TEXTURED		= 0x00000001,
	TEXTURED_LIT	= 0x00000002,
	WIREFRAME		= 0x00000004,
};

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

	explicit Mesh
	(
		ShaderProgram const & program
	);

	explicit Mesh
	(
		RenderFlag				flag,
		ShaderProgram const &	program
	);

	explicit Mesh
	(
		RenderFlag				flag,
		GLuint					vertexArrayIndex,
		GLuint					vertexBufferIndex,
		GLuint					elementBufferIndex,
		GLuint					textureIndex,
		ShaderProgram const &	program
	);

	GLboolean loadTextureData
	(
		GLubyte const *				data,
		TextureData const &			textureData,
		TextureAttribute const &	textureAttribute
	);

	GLboolean copyTextureData
	(
		Mesh const & other
	);

	Mesh & copy
	(
		Mesh const & other
	);

	Mesh
	(
		Mesh const & other
	);

	Mesh & operator=
	(
		Mesh const & other
	);

	Mesh & bindVertexData
	(
		BufferData<GLfloat> const & vertexData
	);

	Mesh & bindElementData
	(
		BufferData<GLuint> const & elementData
	);

	GLboolean loadTextureFile
	(
		GLchar const *				filename,
		TextureAttribute const &	textureAttribute
	);

	GLboolean bindVertexAttribute
	(
		GLboolean				normalized,
		VertexAttribute const & attribute
	) const;

	void initialize();

	void setRenderFlag
	(
		RenderFlag flag
	);

	void initializeTransformUniform
	(
		GLchar const * name
	);

	void render();

	virtual void initializeTextured()		= 0;
	virtual void initializeTexturedLit()	= 0;
	virtual void initializeWireframe()		= 0;
	virtual void initializeVertexColored()	= 0;

	virtual ~Mesh();

protected:

	virtual void update()				= 0;
	virtual void drawTextured()			= 0;
	virtual void drawTexturedLit()		= 0;
	virtual void drawWireframe()		= 0;
	virtual void drawVertexColored()	= 0;

	TextureAttribute		m_textureAttribute;
	TextureData				m_textureData;

	ShaderProgram const *	m_shaderProgram;

	GLsizeiptr				m_vertexBufferSize,
							m_elementBufferSize;

	GLuint					m_vertexArrayIndex,
							m_vertexBufferIndex,
							m_elementBufferIndex,
							m_textureIndex;

	GLubyte					m_renderFlag;

private:

		void draw();
};