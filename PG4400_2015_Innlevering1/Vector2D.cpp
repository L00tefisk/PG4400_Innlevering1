#include "Vector2D.h"

#include <math.h>

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
	size = 0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
	size = sqrt(x*x + y*y);
}
float Vector2D::magnitude()
{
	return size;
}

Vector2D Vector2D::getNormalizedVector()
{
	return Vector2D(x / size, y / size);
}
Vector2D Vector2D::getVector()
{
	return *this;
}

