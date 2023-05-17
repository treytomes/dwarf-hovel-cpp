#include "Texture.h"
#include "gl_error.h"
#include "moremath.h"

Texture::Texture(GLuint _width, GLuint _height)
    : width(_width), height(_height), is_dirty(true), is_bound(false) {
    pixels = new GLfloat[width * height * NUM_CHANNELS];
    stride = width * NUM_CHANNELS;
    reload();
}

Texture::~Texture() {
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
    if (pixels != nullptr) {
        delete[] pixels;
    }
}

void Texture::reload() {
    if (id != 0) {
        glDeleteTextures(1, &id);
    }

    glGenTextures(1, &id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::bind() {
    if (!is_bound) {
        glBindTexture(GL_TEXTURE_2D, id);
        refresh();
        is_bound = true;
    }
}

void Texture::refresh() {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, pixels);
}

void Texture::unbind() {
    if (is_bound) {
        glBindTexture(GL_TEXTURE_2D, NULL);
        is_bound = false;
    }
}

void Texture::draw_filled_rect(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2, const Color color) {
	if (x1 > x2)
	{
		math::swap(x1, x2);
	}
	if (y1 > y2)
	{
		math::swap(y1, y2);
	}

	unsigned int offset = get_offset(x1, y1);
	const unsigned int width = (x2 - x1 + 1);
	const unsigned int stride = get_offset(x1, y1 + 1) - offset - width * NUM_CHANNELS;
	for (unsigned int y = y1; y <= y2; y++, offset += stride) {
		for (unsigned int x = x1; x <= x2; x++, offset += NUM_CHANNELS) {
			set_pixel(offset, color);
		}
	}
}

void Texture::draw_h_line(unsigned int x1, unsigned int x2, unsigned int y, Color color) {
	if (!math::is_in_range(y, 0u, height)) {
		return;
	}

	if (x1 > x2) {
		math::swap(x1, x2);
	}

	if (x2 < 0 || x1 >= width) {
		return;
	}

	if (x1 < 0) {
		x1 = 0;
	}
	if (x2 >= width) {
		x2 = width - 1;
	}

	unsigned int offset = get_offset(x1, y);
	for (unsigned int x = x1; x <= x2; x++, offset += NUM_CHANNELS) {
		set_pixel(offset, color);
	}
}

void Texture::draw_v_line(unsigned int x, unsigned int y1, unsigned int y2, const Color color) {
	if (!math::is_in_range(x, 0u, width)) {
		return;
	}

	if (y1 > y2) {
		math::swap(y1, y2);
	}

	if (y2 < 0 || y1 >= height) {
		return;
	}

	if (y1 < 0) {
		y1 = 0;
	}
	if (y2 >= height)
	{
		y2 = height - 1;
	}

	unsigned int offset = get_offset(x, y1);
	unsigned int stride = width * NUM_CHANNELS;
	for (unsigned int y = y1; y <= y2; y++, offset += stride)
	{
		set_pixel(x, y, color);
	}
}

void Texture::draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Color color) {
	int dx = x2 - x1;
	if (dx < 0)
	{
		dx = -dx;
	}
	int sx = (x1 < x2) ? 1 : -1;
	int dy = y2 - y1;
	if (dy < 0)
	{
		dy = -dy;
	}
	dy = -dy;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx + dy;
	while (true)
	{
		set_pixel(x1, y1, color);
		if ((x1 == x2) && (y1 == y2))
		{
			break;
		}
		int e2 = err << 1;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void Texture::draw_circle(unsigned int xc, unsigned int yc, unsigned int radius, Color color) {
	int x = 0;
	int y = radius;
	int d = 3 - (radius << 1);
	while (y >= x) {
		draw_circle_points(xc, yc, x, y, color); // For each pixel we will draw all 8 points.
		x++;

		// Check for decision parameter and correspondingly update d, x, y.
		if (d > 0) {
			y--;
			d += ((x - y) << 2) + 10;
		} else {
			d += (x << 2) + 6;
		}
	}
}

void Texture::clear(float r, float g, float b, float a) {
	for (unsigned int offset = 0; offset < width * height * NUM_CHANNELS; offset += NUM_CHANNELS) {
		set_pixel(offset, r, g, b, a);
	}
}

void Texture::draw_bitmap(unsigned int x, unsigned int y, Color fg_color, Color bg_color, unsigned char* bitmap, unsigned int width, unsigned int height) {
	for (unsigned int yc = 0; yc < OEM437::CHAR_HEIGHT; yc++, bitmap++) {
		unsigned int char_byte = *bitmap;
		for (unsigned int xc = 0; xc < OEM437::CHAR_WIDTH; xc++, char_byte = char_byte >> 1) {
			if ((char_byte & 1) != 0) {
				set_pixel(x + xc, y + yc, fg_color);
			} else if (bg_color.alpha != 0) {
				set_pixel(x + xc, y + yc, bg_color);
			}
		}
	}
}
