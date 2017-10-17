#include "stdafx.h"
#include "TransformUniform.h"

TransformUniform::TransformUniform()
:
Uniform(),
transform()
{ }

TransformUniform::TransformUniform(GLchar const * name, ShaderProgram const & program, Transform const & transform)
:
Uniform(name, program),
transform(transform)
{ }

TransformUniform::TransformUniform(TransformUniform const & other)
:
Uniform(other),
transform(other.transform)
{ }

void TransformUniform::bind()
{
	glUniformMatrix4fv(m_shaderLocation, 1, GL_FALSE, transform.getData());
}