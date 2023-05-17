#pragma once

#include "gl_shader.h"

class GLProgram {
public:
	GLProgram(GLShader* vertex, GLShader* fragment);
	~GLProgram();
	GLuint get_id();
	GLuint get_location(const char* name);

	void bind();
	void unbind();
	void set_uniform_1i(const char* name, int value);
	void set_uniform_2i(const char* name, int v0, int v1);
	void set_uniform_1f(const char* name, float value);
	void set_uniform_2f(const char* name, float v0, float v1);

	GLuint get_uniform_location(const char* name);
	GLuint get_attribute_location(const char* name);

private:
	GLuint id;
	bool is_in_use;

	static GLuint compile(GLuint vertexShader, GLuint fragmentShader);
};
