#include "stdafx.h"
#include "RGBColor.h"

RGBColor::RGBColor()
:
red(),
green(),
blue()
{ }

RGBColor::RGBColor(GLubyte r, GLubyte g, GLubyte b)
:
red(r),
green(g),
blue(b)
{ }

RGBColor::RGBColor(RGBColor const & other)
:
red(other.red),
green(other.green),
blue(other.blue)
{ }
