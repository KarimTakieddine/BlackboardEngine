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
#include "Quad.h"

Quad::Quad()
:
Mesh()
{ }

Quad::Quad(ShaderProgram const & program)
:
Mesh(program)
{ }

Quad::Quad
(
	GLuint vertexArrayIndex,
	GLuint vertexBufferIndex,
	GLuint elementBufferIndex,
	GLuint textureBufferIndex,
	ShaderProgram const & program
)
:
Mesh
(
	vertexArrayIndex,
	vertexBufferIndex,
	elementBufferIndex,
	textureBufferIndex,
	program
)
{ }

Quad::Quad(Quad const & other)
:
Mesh(other)
{ }

void Quad::initialize()
{
	GLfloat const vertices[32] = 
	{
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	bindVertexData(BufferData<GLfloat>(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices)));

	bindVertexAttribute(GL_FALSE, VertexAttribute("position", BufferAttribute(GL_FLOAT, 3, 0, 8 * sizeof(GLfloat)), *m_shaderProgram));
	bindVertexAttribute(GL_FALSE, VertexAttribute("color", BufferAttribute(GL_FLOAT, 3, 3 * sizeof(GLfloat), 8 * sizeof(GLfloat)), *m_shaderProgram));
	bindVertexAttribute(GL_FALSE, VertexAttribute("textureCoordinates", BufferAttribute(GL_FLOAT, 2, 6 * sizeof(GLfloat), 8 * sizeof(GLfloat)), *m_shaderProgram));
	
	GLuint const elements[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	bindElementData(BufferData<GLuint>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, elements, sizeof(elements)));
}

void Quad::draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Quad::update()
{

}