#pragma once

#include <gl/glew.h>
#include <SDL_opengl.h>
#include "Color.h"
#include "Vector2UI.h"

#define NUM_CHANNELS 4

class Texture {
public:
	Texture(GLuint _width, GLuint _height);
	~Texture();

	inline void Texture::set_pixel(unsigned int x, unsigned int y, float r, float g, float b, float a = 1.0f) {
		unsigned int offset = get_offset(x, y);
		pixels[offset + 0] = r;
		pixels[offset + 1] = g;
		pixels[offset + 2] = b;
		pixels[offset + 3] = a;
	}

	inline void Texture::set_pixel(unsigned int x, unsigned int y, Color color) {
		set_pixel(x, y, color.red, color.green, color.blue, color.alpha);
	}

	inline void Texture::set_pixel(Vector2UI point, Color color) {
		set_pixel(point.x, point.y, color.red, color.green, color.blue, color.alpha);
	}

	inline void Texture::get_pixel(unsigned int x, unsigned int y, float *r, float *g, float *b, float *a) {
		unsigned int offset = get_offset(x, y);
		*r = pixels[offset + 0];
		*g = pixels[offset + 1];
		*b = pixels[offset + 2];
		*a = pixels[offset + 3];
	}

	inline Color Texture::get_pixel(unsigned int x, unsigned int y) {
		float r, g, b, a;
		get_pixel(x, y, &r, &g, &b, &a);
		return Color(r, g, b, a);
	}

	inline Color Texture::get_pixel(Vector2UI point) {
		return get_pixel(point.x, point.y);
	}

	void bind();
	void unbind();
	void refresh();

	// Rebuild the texture resource after the context is lost.
	void reload();

	GLuint get_id();

	GLuint get_width();
	GLuint get_height();

private:
	GLuint id;
	GLfloat* pixels;

	GLuint width;
	GLuint height;
	GLuint stride;
	bool is_dirty;
	bool is_bound;

	inline unsigned int get_offset(unsigned int x, unsigned int y) {
		return y * stride + x * NUM_CHANNELS;
	}

	inline unsigned int get_offset(Vector2UI point) {
		return get_offset(point.x, point.y);
	}
};