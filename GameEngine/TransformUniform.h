#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "Uniform.h"

class TransformUniform : public Uniform
{

public:

	Transform transform;

	TransformUniform();

	explicit TransformUniform(GLchar const * name, ShaderProgram const & program, Transform const & transform);

	TransformUniform(TransformUniform const & other);

protected:

	void bind() override;

};