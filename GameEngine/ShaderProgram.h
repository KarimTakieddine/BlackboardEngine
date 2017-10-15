#pragma once

#include "Shader.h"

class ShaderProgram
{

public:

	ShaderProgram();

	ShaderProgram(ShaderProgram const & other);

	ShaderProgram & attachShader(Shader const & shader);

	GLboolean detachShader(Shader const & shader);

	GLboolean link();

	GLboolean isLinked() const;

	void use() const;

	GLuint getIndex() const;

	~ShaderProgram();

private:

	std::vector<Shader const *> m_shaderList;

	GLuint m_index;
	GLint m_linkStatus;

};