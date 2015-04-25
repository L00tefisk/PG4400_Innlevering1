#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);

	float magnitude();
	Vector2D getNormalizedVector();
	Vector2D getVector();
	float x;
	float y;
private:

	float size;
};

#endif