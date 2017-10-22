#pragma once

#include "stdafx.h"
#include "Mesh.hpp"

class Quad : public Mesh
{

public:

	Quad();

	explicit Quad(ShaderProgram const & program);

	explicit Quad(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureBufferIndex, ShaderProgram const & program);

	Quad(Quad const & other);

	void initialize() override;

protected:

	void draw() override;

	void update() override;

};