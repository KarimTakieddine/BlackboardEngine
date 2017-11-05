#pragma once

#include "stdafx.h"

class Transform
{

public:

	Transform();

	Transform(Transform const & other);

	Transform & operator=(Transform const & other);

	Transform & translate(VEC3 const & displacement);

	Transform & rotate(GLfloat degrees, VEC3 const & axis);

	GLfloat const * getData() const;

private:

	MAT4 m_data;

};