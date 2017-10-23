#pragma once

#include "stdafx.h"

struct RGBColor
{

	RGBColor();

	RGBColor(GLubyte red, GLubyte green, GLubyte blue);

	RGBColor(RGBColor const & other);

	GLubyte red, green, blue;

};