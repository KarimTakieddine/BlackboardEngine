#pragma once

#include "stdafx.h"
#include "ShaderProgram.h"

class Uniform
{

public:

	Uniform();

	explicit Uniform(GLchar const * name, ShaderProgram const & program);

	void initialize(GLchar const * name, ShaderProgram const & program);

	GLboolean isValid() const;

	GLboolean doBinding();

protected:

	virtual void bind() = 0;

	GLint m_shaderLocation;
};