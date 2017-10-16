#pragma once

#include "stdafx.h"
#include "BufferAttribute.h"
#include "ShaderProgram.h"

class VertexAttribute
{

public:

	BufferAttribute bufferAttribute;

	VertexAttribute();

	explicit VertexAttribute(GLchar const * name, BufferAttribute const & attribute, ShaderProgram const & program);

	VertexAttribute(VertexAttribute const & other);

	void initialize(GLchar const * name, ShaderProgram const & program);

	GLboolean bind(GLboolean normalized) const;

	GLint getLocation() const;

	GLboolean isValid() const;

private:

	GLint m_shaderLocation;

};