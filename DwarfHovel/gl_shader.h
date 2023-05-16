#pragma once

#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/glu.h>

class GLShader {
public:
	GLShader(GLuint type, const char* source);
	~GLShader();

	GLuint get_id();

	static GLShader from_file(GLuint type, const char* path);

private:
	GLuint type;
	GLuint id;

	static GLuint compile(GLuint type, const char* source);
};
