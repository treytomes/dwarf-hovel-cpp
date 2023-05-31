#pragma once

#include "Bitmap2bpp.h"
#include "Point2I.h"

class Sprite {
public:
	Bitmap2bpp* bitmap;
	Point2I position;
	Color color0;
	Color color1;
	Color color2;
	Color color3;

	inline Sprite(Bitmap2bpp* _bitmap)
		: owns_bitmap(false) {
		bitmap = _bitmap;
		position = Point2I::zero();
		color0 = Color::transparent();
		color1 = Color::transparent();
		color2 = Color::transparent();
		color3 = Color::transparent();
	}

	inline Sprite(const char* _data, const unsigned int height)
		: owns_bitmap(true) {
		owns_bitmap = true;
		bitmap = new Bitmap2bpp(_data, height);
		position = Point2I::zero();
		color0 = Color::transparent();
		color1 = Color::transparent();
		color2 = Color::transparent();
		color3 = Color::transparent();
	}

	inline ~Sprite() {
		if (owns_bitmap && bitmap != nullptr) {
			delete bitmap;
		}
	}

	void draw(IRenderContext* ctx) {
		bitmap->draw(ctx, position, color0, color1, color2, color3);
	}

private:
	bool owns_bitmap;
};
