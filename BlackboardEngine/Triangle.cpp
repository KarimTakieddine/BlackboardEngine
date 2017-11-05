#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle()
:
Mesh()
{ }

Triangle::Triangle(ShaderProgram const & program)
:
Mesh(program)
{ }

Triangle::Triangle
(
	GLuint vertexArrayIndex,
	GLuint vertexBufferIndex,
	GLuint elementBufferIndex,
	GLuint textureBufferIndex,
	ShaderProgram const & program
)
:
Mesh(vertexArrayIndex, vertexBufferIndex, elementBufferIndex, textureBufferIndex, program)
{ }

Triangle::Triangle(Triangle const & other)
:
Mesh(other)
{ }

void Triangle::initialize()
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

void Triangle::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::update()
{

}