#pragma once

#include <gl/glew.h>
#include <SDL_opengl.h>

#include "Color.h"
#include "IRenderContext.h"
#include "OEM437.h"
#include "math/math.h"

#define NUM_CHANNELS 4

class Texture : public IRenderContext {
public:
	Texture(unsigned int _width, unsigned int _height);
	inline Texture(VectorUI size) : Texture(size.x, size.y) {}
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
		set_pixel(offset, color.r, color.g, color.b, color.a);
	}

	inline void set_pixel(unsigned int x, unsigned int y, const Color color) {
		if (!math::is_in_range(x, 0u, width - 1) || !math::is_in_range(y, 0u, height)) {
			return;
		}
		set_pixel(x, y, color.r, color.g, color.b, color.a);
	}

	inline void set_pixel(PointUI point, const Color color) {
		set_pixel(point.x, point.y, color.r, color.g, color.b, color.a);
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

	inline const Color get_pixel(PointUI point) {
		return get_pixel(point.x, point.y);
	}

	void draw_filled_rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, const Color color);

	inline void draw_filled_rect(PointUI point1, PointUI Point, const Color color) {
		draw_filled_rect(point1.x, Point.x, point1.y, Point.y, color);
	}

	inline void draw_filled_rect(Rectangle rect, const Color color) {
		draw_filled_rect(rect.get_left(), rect.get_right(), rect.get_top(), rect.get_bottom(), color);
	}

	inline void draw_rect(Rectangle rect, const Color color) {
		draw_h_line(rect.get_left(), rect.get_right(), rect.get_top(), color);
		draw_h_line(rect.get_left(), rect.get_right(), rect.get_bottom(), color);
		draw_v_line(rect.get_left(), rect.get_top(), rect.get_bottom(), color);
		draw_v_line(rect.get_right(), rect.get_top(), rect.get_bottom(), color);
	}

	void draw_h_line(unsigned int x1, unsigned int x2, unsigned int y, const Color color);
	void draw_v_line(unsigned int x, unsigned int y1, unsigned int y2, const Color color);
	void draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Color color);

	inline void draw_line(PointUI point1, PointUI Point, Color color) {
		draw_line(point1.x, point1.y, Point.x, Point.y, color);
	}

	void draw_circle(unsigned int xc, unsigned int yc, unsigned int radius, Color color);

	inline void draw_circle(PointUI center, unsigned int radius, Color color) {
		draw_circle(center.x, center.y, radius, color);
	}
	
	void clear(float r, float g, float b, float a = 1.0f);

	inline void clear(Color color) {
		clear(color.r, color.g, color.b, color.a);
	}

	void draw_bitmap_1bpp(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height);

	inline void draw_bitmap_1bpp(PointUI point, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height) {
		draw_bitmap_1bpp(point.x, point.y, fg_color, bg_color, bitmap, width, height);
	}

	void draw_bitmap_2bpp(unsigned int x, unsigned int y, Color c0, Color c1, Color c2, Color c3, unsigned short* bitmap, unsigned int width, unsigned int height, bool flip_x = false, bool flip_y = false, float angle = 0.0f);
	
	inline void draw_bitmap_2bpp(PointUI point, Color c0, Color c1, Color c2, Color c3, unsigned short* bitmap, unsigned int width, unsigned int height, bool flip_x = false, bool flip_y = false, float angle = 0.0f) {
		draw_bitmap_2bpp(point.x, point.y, c0, c1, c2, c3, bitmap, width, height, flip_x, flip_y, angle);
	}

	inline void draw_char(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char ch) {
		draw_bitmap_1bpp(x, y, fg_color, bg_color, (unsigned char*)(OEM437::DATA + ch * OEM437::BYTES_PER_CHAR), OEM437::CHAR_WIDTH, OEM437::CHAR_HEIGHT);
	}

	inline void draw_char(PointUI point, Color fg_color, Color bg_color, unsigned char ch) {
		draw_char(point.x, point.y, fg_color, bg_color, ch);
	}

	inline void draw_string(unsigned int x, unsigned int y, Color fg_color, Color bg_color, const char* text) {
		for (; *text != 0; text++, x += OEM437::CHAR_WIDTH) {
			draw_char(x, y, fg_color, bg_color, *text);
		}
	}

	inline void draw_string(PointUI point, Color fg_color, Color bg_color, const char* text) {
		draw_string(point.x, point.y, fg_color, bg_color, text);
	}

	void flood_fill(PointUI origin, Color fill_color, Color border_color);

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
		x = math::clamp(x, 0u, width - 1u);
		y = math::clamp(y, 0u, height - 1u);
		return y * stride + x * NUM_CHANNELS;
	}

	inline unsigned int get_offset(PointUI point) {
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