#include "stdafx.h"
#include "Uniform.h"

Uniform::Uniform()
:
m_shaderLocation(-1)
{ }

Uniform::Uniform
(
	GLchar const * name,
	ShaderProgram const & program
)
{
	initialize(name, program);
}

void Uniform::initialize(GLchar const * name, ShaderProgram const & program)
{
	m_shaderLocation = glGetUniformLocation(program.getIndex(), name);
}

GLboolean Uniform::isValid() const
{
	return m_shaderLocation != -1;
}

GLboolean Uniform::doBinding()
{
	if (!isValid())
	{
		return GL_FALSE;
	}

	bind();

	return GL_TRUE;
}