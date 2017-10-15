#pragma once

#include "stdafx.h"
#include "BufferAttribute.h"
#include "ShaderProgram.h"

class ShaderMemory
{

public:

	BufferAttribute bufferAttribute;

	ShaderMemory();

	explicit ShaderMemory(GLchar const * name, BufferAttribute const & attribute, ShaderProgram const & program);

	ShaderMemory(ShaderMemory const & other);

	void initialize(GLchar const * name, ShaderProgram const & program);

	GLint getLocation() const;

	GLboolean isValid() const;

private:

	GLint m_location;

};