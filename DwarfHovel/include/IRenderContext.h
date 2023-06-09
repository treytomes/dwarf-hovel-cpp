#pragma once

#include "Color.h"
#include "math/math.h"

class IRenderContext {
public:
	virtual void set_pixel(unsigned int offset, float r, float g, float b, float a = 1.0f) = 0;
	virtual void set_pixel(unsigned int offset, const Color color) = 0;
	virtual void set_pixel(unsigned int x, unsigned int y, float r, float g, float b, float a = 1.0f) = 0;
	virtual void set_pixel(unsigned int x, unsigned int y, const Color color) = 0;
	virtual void set_pixel(PointUI point, const Color color) = 0;
	virtual void get_pixel(unsigned int x, unsigned int y, float* r, float* g, float* b, float* a) = 0;
	virtual const Color get_pixel(unsigned int x, unsigned int y) = 0;
	virtual const Color get_pixel(PointUI point) = 0;
	virtual void draw_filled_rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, const Color color) = 0;
	virtual void draw_filled_rect(PointUI point1, PointUI Point, const Color color) = 0;
	virtual inline void draw_filled_rect(Rectangle rect, const Color color) = 0;
	virtual inline void draw_rect(Rectangle rect, const Color color) = 0;
	virtual void draw_h_line(unsigned int x1, unsigned int x2, unsigned int y, const Color color) = 0;
	virtual void draw_v_line(unsigned int x, unsigned int y1, unsigned int y2, const Color color) = 0;
	virtual void draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Color color) = 0;
	virtual void draw_line(PointUI point1, PointUI Point, Color color) = 0;
	virtual void draw_circle(unsigned int xc, unsigned int yc, unsigned int radius, Color color) = 0;
	virtual void draw_circle(PointUI center, unsigned int radius, Color color) = 0;
	virtual void clear(float r, float g, float b, float a = 1.0f) = 0;
	virtual void clear(Color color) = 0;
	virtual void draw_bitmap_1bpp(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height) = 0;
	virtual void draw_bitmap_1bpp(PointUI point, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height) = 0;
	virtual void draw_bitmap_2bpp(unsigned int x, unsigned int y, Color c0, Color c1, Color c2, Color c3, unsigned short* bitmap, unsigned int width, unsigned int height, bool flip_x = false, bool flip_y = false, float angle = 0.0f) = 0;
	virtual void draw_bitmap_2bpp(PointUI point, Color c0, Color c1, Color c2, Color c3, unsigned short* bitmap, unsigned int width, unsigned int height, bool flip_x = false, bool flip_y = false, float angle = 0.0f) = 0;
	virtual void draw_char(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char ch) = 0;
	virtual void draw_char(PointUI point, Color fg_color, Color bg_color, unsigned char ch) = 0;
	virtual void draw_string(unsigned int x, unsigned int y, Color fg_color, Color bg_color, const char* text) = 0;
	virtual void draw_string(PointUI point, Color fg_color, Color bg_color, const char* text) = 0;
	virtual void flood_fill(PointUI origin, Color fill_color, Color border_color) = 0;
	virtual unsigned int get_width() = 0;
	virtual unsigned int get_height() = 0;
};
