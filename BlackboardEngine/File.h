#pragma once

#include "stdafx.h"

class File
{

public:

	static GLboolean read(GLchar const * filename, std::vector<GLchar> & buffer);

};