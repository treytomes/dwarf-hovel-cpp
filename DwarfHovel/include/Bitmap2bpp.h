#pragma once

#include <fstream>
#include <sstream>
#include "io/io.h"

#include "Color.h"
#include "IRenderContext.h"
#include "math/math.h"

#define BITMAP_BIT_WIDTH 16
#define BITMAP_BPP 2
#define BITMAP_WIDTH (BITMAP_BIT_WIDTH / BITMAP_BPP)
#define BITMAP_HEIGHT_DEFAULT 8

class Bitmap2bpp {
public:
	const unsigned int width;
	const unsigned int height;

	inline Bitmap2bpp(const char* _data, unsigned int _height = BITMAP_HEIGHT_DEFAULT)
		: width(BITMAP_WIDTH), height(_height) {
		data = new unsigned short[height];
		for (auto r = 0u, n = 0u; r < height; r++) {
			unsigned short value = 0;
			for (auto c = 0u; c < width; c++, n++) {
				char ch = _data[n];
				if (!isspace(ch)) { // Skip whitespace.
					value >>= BITMAP_BPP;
					value |= ((ch - '0') << (BITMAP_BIT_WIDTH - 2));
				} else {
					c--;
				}
			}
			data[r] = value;
		}
	}

	inline Bitmap2bpp(const Bitmap2bpp& clone) : width(clone.width), height(clone.height), data(clone.data) {}

	inline ~Bitmap2bpp() {
		if (data != nullptr) {
			delete data;
			data = nullptr;
		}
	}

	inline void draw(IRenderContext *context, PointUI position, Color c0, Color c1, Color c2, Color c3, bool flip_x = false, bool flip_y = false, float angle = 0.0f) {
		context->draw_bitmap_2bpp(position, c0, c1, c2, c3, data, width, height, flip_x, flip_y, angle);
	}

	inline unsigned short get_pixel(unsigned int x, unsigned int y) { return (data[y] >> (2 * x)) & 0b11; }

	static Bitmap2bpp from_file(const char* filename) {
		std::fstream f(filename);	
		int lines = 0;
		std::stringstream buffer;
		if (!f.is_open()) {
			LOG_FATAL("File does not exist: %s", filename);
		}
		f >> lines;
		buffer << f.rdbuf();
		return Bitmap2bpp(buffer.str().c_str(), lines);
	}

private:
	unsigned short *data;
};
