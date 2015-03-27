#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();
	virtual void Draw() = 0;
private:
	unsigned short bitmapID = 0;
};

#endif DRAWABLE_H
