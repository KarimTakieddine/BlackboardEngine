#pragma once

#include "Mesh.hpp"

class Triangle : public Mesh
{

public:

	Triangle();

	explicit Triangle(ShaderProgram const & program);

	explicit Triangle(GLuint vertexArrayIndex, GLuint vertexBufferIndex, GLuint elementBufferIndex, GLuint textureBufferIndex, ShaderProgram const & program);

	Triangle(Triangle const & other);

	void initialize() override;

protected:

	void draw() override;

	void update() override;

};