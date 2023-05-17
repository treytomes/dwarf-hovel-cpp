#pragma once

#include <gl/glew.h>
#include <SDL_opengl.h>

#include "Color.h"
#include "IRenderContext.h"
#include "OEM437.h"
#include "Vector2UI.h"

#define NUM_CHANNELS 4

class Texture : public IRenderContext {
public:
	Texture(unsigned int _width, unsigned int _height);
	~Texture();

	inline void set_pixel(unsigned int offset, float r, float g, float b, float a = 1.0f) {
		pixels[offset + 0] = r;
		pixels[offset + 1] = g;
		pixels[offset + 2] = b;
		pixels[offset + 3] = a;
	}

	inline void set_pixel(unsigned int x, unsigned int y, float r, float g, float b, float a = 1.0f) {
		unsigned int offset = get_offset(x, y);
		set_pixel(offset, r, g, b, a);
	}

	inline void set_pixel(unsigned int offset, const Color color) {
		set_pixel(offset, color.red, color.green, color.blue, color.alpha);
	}

	inline void set_pixel(unsigned int x, unsigned int y, const Color color) {
		set_pixel(x, y, color.red, color.green, color.blue, color.alpha);
	}

	inline void set_pixel(Vector2UI point, const Color color) {
		set_pixel(point.x, point.y, color.red, color.green, color.blue, color.alpha);
	}

	inline void get_pixel(unsigned int x, unsigned int y, float *r, float *g, float *b, float *a) {
		unsigned int offset = get_offset(x, y);
		*r = pixels[offset + 0];
		*g = pixels[offset + 1];
		*b = pixels[offset + 2];
		*a = pixels[offset + 3];
	}

	inline const Color get_pixel(unsigned int x, unsigned int y) {
		float r, g, b, a;
		get_pixel(x, y, &r, &g, &b, &a);
		return Color(r, g, b, a);
	}

	inline const Color get_pixel(Vector2UI point) {
		return get_pixel(point.x, point.y);
	}

	void draw_filled_rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, const Color color);

	inline void draw_filled_rect(Vector2UI point1, Vector2UI point2, const Color color) {
		draw_filled_rect(point1.x, point2.x, point1.y, point2.y, color);
	}

	void draw_h_line(unsigned int x1, unsigned int x2, unsigned int y, const Color color);
	void draw_v_line(unsigned int x, unsigned int y1, unsigned int y2, const Color color);
	void draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Color color);

	inline void draw_line(Vector2UI point1, Vector2UI point2, Color color) {
		draw_line(point1.x, point1.y, point2.x, point2.y, color);
	}

	void draw_circle(unsigned int xc, unsigned int yc, unsigned int radius, Color color);

	inline void draw_circle(Vector2UI center, unsigned int radius, Color color) {
		draw_circle(center.x, center.y, radius, color);
	}
	
	void clear(float r, float g, float b, float a = 1.0f);

	inline void clear(Color color) {
		clear(color.red, color.green, color.blue, color.alpha);
	}

	void draw_bitmap(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height);

	inline void draw_bitmap(Vector2UI point, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height) {
		draw_bitmap(point.x, point.y, fg_color, bg_color, bitmap, width, height);
	}

	inline void draw_char(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char ch) {
		draw_bitmap(x, y, fg_color, bg_color, (unsigned char*)(OEM437::DATA + ch * OEM437::BYTES_PER_CHAR), OEM437::CHAR_WIDTH, OEM437::CHAR_HEIGHT);
	}

	inline void draw_char(Vector2UI point, Color fg_color, Color bg_color, unsigned char ch) {
		draw_char(point.x, point.y, fg_color, bg_color, ch);
	}

	inline void draw_string(unsigned int x, unsigned int y, Color fg_color, Color bg_color, const char* text) {
		for (; *text != 0; text++, x += OEM437::CHAR_WIDTH) {
			draw_char(x, y, fg_color, bg_color, *text);
		}
	}

	inline void draw_string(Vector2UI point, Color fg_color, Color bg_color, const char* text) {
		draw_string(point.x, point.y, fg_color, bg_color, text);
	}

	void bind();
	void unbind();
	void refresh();

	// Rebuild the texture resource after the context is lost.
	void reload();

	inline unsigned int get_id() {
		return id;
	}

	inline unsigned int get_width() {
		return width;
	}

	inline unsigned int get_height() {
		return height;
	}

private:
	unsigned int id;
	float* pixels;

	unsigned int width;
	unsigned int height;
	unsigned int stride;
	bool is_dirty;
	bool is_bound;

	inline unsigned int get_offset(unsigned int x, unsigned int y) {
		return y * stride + x * NUM_CHANNELS;
	}

	inline unsigned int get_offset(Vector2UI point) {
		return get_offset(point.x, point.y);
	}

	/*
	* Draw all 8 quadrants simultaneously.
	*/
	inline void draw_circle_points(int xc, int yc, int x, int y, const Color color) {
		set_pixel(xc + x, yc + y, color);
		set_pixel(xc + x, yc - y, color);
		set_pixel(xc - x, yc + y, color);
		set_pixel(xc - x, yc - y, color);
		set_pixel(xc + y, yc + x, color);
		set_pixel(xc + y, yc - x, color);
		set_pixel(xc - y, yc + x, color);
		set_pixel(xc - y, yc - x, color);
	}
};