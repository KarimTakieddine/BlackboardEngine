#include "stdafx.h"
#include "File.h"

GLboolean File::read(GLchar const * filename, std::vector<GLchar> & buffer)
{
	std::ifstream stream(filename, std::ios::binary);

	if (!stream.is_open())
	{
		return GL_FALSE;
	}

	stream.seekg(0, stream.end);
	GLsizeiptr size = stream.tellg();
	stream.seekg(0, stream.beg);

	if (size == 0)
	{
		stream.close();
		return GL_FALSE;
	}

	if (buffer.size() != size)
	{
		buffer.resize(size);
	}

	stream.read(&buffer[0], size);
	buffer.push_back('\x00');

	stream.close();

	return GL_TRUE;
}