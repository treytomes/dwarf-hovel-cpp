#pragma once

#include "Bitmap2pp.h"

class Sprite {
public:
	Point2UI position;
	Color color0;
	Color color1;
	Color color2;
	Color color3;

	inline Sprite(const char* _data, unsigned int _height = BITMAP_HEIGHT_DEFAULT) {
		bitmap = new Bitmap2pp(_data, _height);
		position = Point2UI::zero();
		color0 = Color::transparent();
		color1 = Color::transparent();
		color2 = Color::transparent();
		color3 = Color::transparent();
	}

	inline ~Sprite() {
		if (bitmap != nullptr) {
			delete bitmap;
		}
	}

	void draw(IRenderContext* ctx) {
		bitmap->draw(ctx, position, color0, color1, color2, color3);
	}

private:
	Bitmap2pp* bitmap;
};
