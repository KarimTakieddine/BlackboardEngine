#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
:
m_data()
{ }

Transform::Transform(Transform const & other)
:
m_data(other.m_data)
{ }

Transform & Transform::operator=(Transform const & other)
{
	m_data = other.m_data;

	return *this;
}

Transform & Transform::translate(VEC3 const & displacement)
{
	m_data = glm::translate(m_data, displacement);

	return *this;
}

Transform & Transform::rotate(GLfloat degrees, VEC3 const & axis)
{
	m_data = glm::rotate(m_data, glm::radians(degrees), axis);

	return *this;
}

GLfloat const * Transform::getData() const
{
	return glm::value_ptr(m_data);
}