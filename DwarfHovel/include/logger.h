#pragma once

#include <fstream>
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

enum class LogLevel : int {
	LOG_LEVEL_DEBUG = 0,
	LOG_LEVEL_INFO = 1,
	LOG_LEVEL_WARNING = 2,
	LOG_LEVEL_ERROR = 3,
	LOG_LEVEL_FATAL = 4,
};

#define LOG_DEBUG(format, ...) Logger::get_instance()->write(LogLevel::LOG_LEVEL_DEBUG, format, __VA_ARGS__)
#define LOG_INFO(format, ...) Logger::get_instance()->write(LogLevel::LOG_LEVEL_INFO, format, __VA_ARGS__)
#define LOG_WARNING(format, ...) Logger::get_instance()->write(LogLevel::LOG_LEVEL_WARNING, format, __VA_ARGS__)
#define LOG_ERROR(format, ...) Logger::get_instance()->write(LogLevel::LOG_LEVEL_ERROR, format, __VA_ARGS__)
#define LOG_FATAL(format, ...) Logger::get_instance()->write(LogLevel::LOG_LEVEL_FATAL, format, __VA_ARGS__)

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
