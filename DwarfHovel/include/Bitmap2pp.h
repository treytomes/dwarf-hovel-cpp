#pragma once

#include "Color.h"
#include "IRenderContext.h"
#include "Point2UI.h"

#define BITMAP_BIT_WIDTH 16
#define BITMAP_BPP 2
#define BITMAP_WIDTH (BITMAP_BIT_WIDTH / BITMAP_BPP)
#define BITMAP_HEIGHT_DEFAULT 8

class Bitmap2pp {
public:
	inline Bitmap2pp(const char* _data, unsigned int _height = BITMAP_HEIGHT_DEFAULT)
		: width(BITMAP_WIDTH), height(_height) {
		data = new unsigned short[height];
		for (auto r = 0, n = 0; r < height; r++) {
			unsigned short value = 0;
			for (auto c = 0; c < width; c++, n++) {
				value >>= BITMAP_BPP;
				char ch = _data[n];
				value |= ((ch - '0') << (BITMAP_BIT_WIDTH - 2));
			}
			data[r] = value;
		}
	}

	inline ~Bitmap2pp() {
		if (data != nullptr) {
			delete data;
			data = nullptr;
		}
	}

	inline void draw(IRenderContext *context, Point2UI position, Color c0, Color c1, Color c2, Color c3) {
		context->draw_bitmap_2bpp(position, c0, c1, c2, c3, data, width, height);
	}

private:
	const unsigned int width;
	const unsigned int height;
	unsigned short *data;
};
