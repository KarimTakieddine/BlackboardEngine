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

	GLuint const elements[6] =
	{
		0, 1, 2,
		0, 2, 3
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