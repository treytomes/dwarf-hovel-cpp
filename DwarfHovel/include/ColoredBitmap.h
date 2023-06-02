#pragma once

#include "Bitmap2bpp.h"
#include "Color.h"

class ColoredBitmap {
public:
	Color color0;
	Color color1;
	Color color2;
	Color color3;

	inline ColoredBitmap(Bitmap2bpp* _bitmap, Color _color0, Color _color1, Color _color2, Color _color3)
		: bitmap(_bitmap) {
		color0 = _color0;
		color1 = _color1;
		color2 = _color2;
		color3 = _color3;
	}

	inline void draw(IRenderContext *context, Point2UI position, bool flip_x = false, bool flip_y = false, float angle = 0.0f) {
		bitmap->draw(context, position, color0, color1, color2, color3, flip_x, flip_y, angle);
	}

private:
	Bitmap2bpp* bitmap;
};