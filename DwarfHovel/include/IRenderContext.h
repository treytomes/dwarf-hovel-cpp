#pragma once

#include "Color.h"
#include "Vector2UI.h"

class IRenderContext {
public:
	virtual void set_pixel(unsigned int offset, float r, float g, float b, float a = 1.0f) = 0;
	virtual void set_pixel(unsigned int offset, const Color color) = 0;
	virtual void set_pixel(unsigned int x, unsigned int y, float r, float g, float b, float a = 1.0f) = 0;
	virtual void set_pixel(unsigned int x, unsigned int y, const Color color) = 0;
	virtual void set_pixel(Vector2UI point, const Color color) = 0;
	virtual void get_pixel(unsigned int x, unsigned int y, float* r, float* g, float* b, float* a) = 0;
	virtual const Color get_pixel(unsigned int x, unsigned int y) = 0;
	virtual const Color get_pixel(Vector2UI point) = 0;
	virtual void draw_filled_rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, const Color color) = 0;
	virtual void draw_filled_rect(Vector2UI point1, Vector2UI point2, const Color color) = 0;
	virtual void draw_h_line(unsigned int x1, unsigned int x2, unsigned int y, const Color color) = 0;
	virtual void draw_v_line(unsigned int x, unsigned int y1, unsigned int y2, const Color color) = 0;
	virtual void draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Color color) = 0;
	virtual void draw_line(Vector2UI point1, Vector2UI point2, Color color) = 0;
	virtual void draw_circle(unsigned int xc, unsigned int yc, unsigned int radius, Color color) = 0;
	virtual void draw_circle(Vector2UI center, unsigned int radius, Color color) = 0;
	virtual void clear(float r, float g, float b, float a = 1.0f) = 0;
	virtual void clear(Color color) = 0;
	virtual void draw_bitmap(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height) = 0;
	virtual void draw_bitmap(Vector2UI point, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height) = 0;
	virtual void draw_char(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char ch) = 0;
	virtual void draw_char(Vector2UI point, Color fg_color, Color bg_color, unsigned char ch) = 0;
	virtual void draw_string(unsigned int x, unsigned int y, Color fg_color, Color bg_color, const char* text) = 0;
	virtual void draw_string(Vector2UI point, Color fg_color, Color bg_color, const char* text) = 0;
	virtual void flood_fill(Vector2UI origin, Color fill_color, Color border_color) = 0;
	virtual GLuint get_width() = 0;
	virtual GLuint get_height() = 0;
};