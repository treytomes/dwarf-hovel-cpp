#pragma once

#include <fstream>
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

enum class LogLevel : int {
	LOG_DEBUG = 0,
	LOG_INFO = 1,
	LOG_WARNING = 2,
	LOG_ERROR = 3,
	LOG_FATAL = 4,
};

class Logger {
public:
	static void initialize();
	static void shutdown();
	static Logger* get_instance();

	void write(LogLevel level, const char* format, ...);
	void write(LogLevel level, SDL_Event* evt);
	void write(LogLevel level, SDL_QuitEvent* evt);
	void write(LogLevel level, SDL_WindowEvent* evt);
	void write(LogLevel level, GLuint gl_id);

private:
	Logger();
	~Logger();
	void write_program(LogLevel level, GLuint program);
	void write_shader(LogLevel level, GLuint shader);

	static Logger* instance;
	std::ofstream log_file;
};
