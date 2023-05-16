#pragma once

#include <gl/glew.h>
#include <SDL_opengl.h>

class Texture {
public:
	Texture(GLuint _width, GLuint _height);
	~Texture();

	void set_pixel(GLuint x, GLuint y, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	void bind();
	void unbind();
	void refresh(bool always = false);

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
};