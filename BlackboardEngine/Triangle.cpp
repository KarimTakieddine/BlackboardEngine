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
#include "Triangle.h"

Triangle::Triangle()
:
Mesh()
{ }

Triangle::Triangle
(
	ShaderProgram const & program
)
:
Mesh(program)
{ }

Triangle::Triangle
(
	Triangle const & other
)
:
Mesh(other)
{ }

void Triangle::initializeTextured()
{

}

void Triangle::initializeWireframe()
{
	GLfloat const vertices[18] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	GLuint const elements[6] =
	{
		0, 1,

		1, 2,

		2, 0
	};

	bindVertexData(BufferData<GLfloat>(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices)));

	bindVertexAttribute(GL_FALSE, VertexAttribute("position", BufferAttribute(GL_FLOAT, 3, 0, 6 * sizeof(GLfloat)), *m_shaderProgram));
	bindVertexAttribute(GL_FALSE, VertexAttribute("color", BufferAttribute(GL_FLOAT, 3, 3 * sizeof(GLfloat), 6 * sizeof(GLfloat)), *m_shaderProgram));

	bindElementData(BufferData<GLuint>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, elements, sizeof(elements)));
}

void Triangle::initializeVertexColored()
{
	GLfloat const vertices[18] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	bindVertexData(BufferData<GLfloat> (GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices)));

	bindVertexAttribute(GL_FALSE, VertexAttribute("position", BufferAttribute(GL_FLOAT, 3, 0, 6 * sizeof(GLfloat)), *m_shaderProgram));
	bindVertexAttribute(GL_FALSE, VertexAttribute("color", BufferAttribute(GL_FLOAT, 3, 3 * sizeof(GLfloat), 6 * sizeof(GLfloat)), *m_shaderProgram));
}

void Triangle::update()
{

}

void Triangle::drawTextured()
{

}

void Triangle::drawWireframe()
{
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, nullptr);
}

void Triangle::drawVertexColored()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}