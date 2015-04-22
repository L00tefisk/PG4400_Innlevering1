#include "Vector2D.h"

#include <math.h>

Vector2D::Vector2D()
{
	// Intentionally left blank
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
	size = sqrt(x*x + y*y);
}

float Vector2D::dot(const Vector2D& vec)
{
	return x * vec.x + y * vec.y;
}

float Vector2D::project(const Vector2D& vec)
{
	float angle = atan2(y - vec.y, x - vec.x);
	return size * cos(angle);
}

Vector2D Vector2D::getNormal()
{
	return *this;
}

Vector2D Vector2D::getVector()
{
	return *this;
}