#pragma once

#include "ColoredBitmap.h"
#include "Point2I.h"

class Sprite {
public:
	ColoredBitmap* bitmap;
	Point2I position;
	bool flip_x;
	bool flip_y;
	float angle;

	inline Sprite(ColoredBitmap* _bitmap)
		: flip_x(false), flip_y(false), angle(0.0f) {
		bitmap = _bitmap;
		position = Point2I::zero();
	}

	inline void draw(IRenderContext* ctx) {
		bitmap->draw(ctx, position, flip_x, flip_y, angle);
	}
};
