#pragma once

#include "stdafx.h"
#include "GLInfo.h"

class BufferObject
{

public:

	BufferObject();

	explicit BufferObject
	(
		GLenum target
	);

	explicit BufferObject
	(
		GLenum		target,
		GLsizeiptr	size
	);

	explicit BufferObject
	(
		GLenum		target,
		GLuint		index,
		GLsizeiptr	size
	);

	BufferObject
	(
		BufferObject const & other
	);

	void bindToTarget
	(
		GLenum target
	)
	const;

	void bind()					const;

	void lazyBind()				const;

	GLboolean isBoundToState()	const;

	GLboolean isValid()			const;

	void setSize
	(
		GLsizeiptr size
	);

	void setData
	(
		GLenum			usage,
		void const *	data
	);

	GLsizeiptr getSize() const;

	~BufferObject();

private:

	GLsizeiptr	m_size;
	GLuint		m_index;
	GLenum		m_target;
};