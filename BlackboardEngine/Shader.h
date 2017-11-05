#pragma once

#include "stdafx.h"
#include "File.h"

class Shader
{

public:

	Shader();

	explicit Shader(GLenum type);

	Shader(Shader const & other);

	Shader & operator=(Shader const & other);

	Shader & copy(Shader const & other);

	Shader & compile(GLchar const * source);

	GLboolean loadFile(GLchar const * file);

	GLuint getIndex() const;

	GLboolean isCompiled() const;

	~Shader();

private:

	GLenum m_type;
	GLuint m_index;
	GLint m_compileStatus;
	GLsizei m_sourceLength;
};