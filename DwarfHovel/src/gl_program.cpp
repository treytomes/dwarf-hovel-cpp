#include "gl_program.h"
#include "logger.h"

GLProgram::GLProgram(GLShader* vertex, GLShader* fragment) {
	id = compile(vertex->get_id(), fragment->get_id());
	is_in_use = false;
}

GLProgram::~GLProgram() {
	unbind();
	if (id != 0) {
		glDeleteProgram(id);
		id = 0;
	}
}

GLuint GLProgram::get_id() {
	return id;
}

void GLProgram::bind() {
	if (!is_in_use) {
		glUseProgram(id);
		is_in_use = true;
	}
}

void GLProgram::unbind() {
	if (is_in_use) {
		glUseProgram(0);
		is_in_use = false;
	}
}

void GLProgram::set_uniform_1i(const char* name, int value) {
	const GLuint location = get_uniform_location(name);
	glUniform1i(location, value);
}

void GLProgram::set_uniform_2i(const char* name, int v0, int v1) {
	const GLuint location = get_uniform_location(name);
	glUniform2i(location, v0, v1);
}

void GLProgram::set_uniform_1f(const char* name, float value) {
	const GLuint location = get_uniform_location(name);
	glUniform1f(location, value);
}

void GLProgram::set_uniform_2f(const char* name, float v0, float v1) {
	const GLuint location = get_uniform_location(name);
	glUniform2f(location, v0, v1);
}

GLuint GLProgram::get_uniform_location(const char* name) {
	const GLuint location = glGetUniformLocation(id, name);
	if (location == -1) {
		LOG_ERROR("%s is not a valid GLSL program variable.", name);
	}
	return location;
}

GLuint GLProgram::get_attribute_location(const char* name) {
	const GLuint location = glGetAttribLocation(id, name);
	if (location == -1) {
		LOG_ERROR("%s is not a valid GLSL program variable.", name);
	}
	return location;
}

GLuint GLProgram::compile(GLuint vertexShader, GLuint fragmentShader) {
	// Generate the program.
	const GLuint program = glCreateProgram();

	// Attach vertex shader to program.
	glAttachShader(program, vertexShader);

	// Attach fragment shader to program.
	glAttachShader(program, fragmentShader);

	// Link program.
	glLinkProgram(program);

	// Check for errors.
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		LOG_ERROR("Error linking program %d.", program);
		LOG_ERROR(program);
		return 0;
	}

	return program;
}
