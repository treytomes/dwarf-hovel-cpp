#include "gl_shader.h"
#include "logger.h"

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include <fstream>
#include <sstream>

GLShader::GLShader(GLuint _type, const char* source)
	: type(_type), id(0) {
	id = compile(type, source);
}

GLShader::~GLShader() {
	if (id != 0) {
		glDeleteShader(id);
		id = 0;
	}
}

GLuint GLShader::get_id() {
	return id;
}

GLuint GLShader::compile(GLenum type, const char* source) {
	// Create the shader.
	GLuint shader = glCreateShader(type);

	// Get vertex source.
	const GLchar* shaderSource[] = { source };

	// Set vertex source.
	glShaderSource(shader, 1, shaderSource, NULL);

	// Compile vertex source.
	glCompileShader(shader);

	// Check vertex shader for errors.
	GLint status = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		Logger::get_instance()->write(LogLevel::LOG_ERROR, "Unable to compile vertex shader %d.", shader);
		Logger::get_instance()->write(LogLevel::LOG_ERROR, shader);
		return 0;
	}

	return shader;
}

GLShader GLShader::from_file(GLuint type, const char* path) {
	std::string source;
	std::ifstream f(path);
	if (!f.is_open()) {
		Logger::get_instance()->write(LogLevel::LOG_ERROR, "Unable to open file path: %s", path);
	} else {
		std::stringstream buffer;
		buffer << f.rdbuf();
		source = buffer.str();
	}
	return GLShader(type, source.c_str());
}