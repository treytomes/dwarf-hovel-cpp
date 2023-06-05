#include "io/Logger.h"

#include <algorithm>
#include <chrono>
#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <SDL.h>

#include "io/Settings.h"

LogLevel from_string(std::string value) {
	std::transform(value.begin(), value.end(), value.begin(), ::toupper);
	
	if (value == "DEBUG") {
		return LogLevel::LOG_LEVEL_DEBUG;
	} else if (value == "INFO") {
		return LogLevel::LOG_LEVEL_INFO;
	} else if (value == "WARNING") {
		return LogLevel::LOG_LEVEL_WARNING;
	} else if (value == "ERROR") {
		return LogLevel::LOG_LEVEL_ERROR;
	} else if (value == "FATAL") {
		return LogLevel::LOG_LEVEL_FATAL;
	} else {
		return LogLevel::LOG_LEVEL_DEBUG;
	}
}

std::string to_string(LogLevel value) {
	switch (value) {
	default:
	case LogLevel::LOG_LEVEL_DEBUG:
		return "DEBUG";
	case LogLevel::LOG_LEVEL_INFO:
		return "INFO";
	case LogLevel::LOG_LEVEL_WARNING:
		return "WARNING";
	case LogLevel::LOG_LEVEL_ERROR:
		return "ERROR";
	case LogLevel::LOG_LEVEL_FATAL:
		return "FATAL";
	}
}

template<typename TStream>
TStream& operator<<(TStream& stream, const LogLevel& level)
{
	const char* levels[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"FATAL",
	};
	return stream << levels[(int)level];
}

std::string timestamp(const std::string& format) {
	auto now = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(now);

	std::tm local_time;
#ifdef _WIN32
	localtime_s(&local_time, &time);
#else
	localtime_r(&time, &local_time);
#endif

	std::stringstream ss;
	ss << std::put_time(&local_time, format.c_str());
	return ss.str();
}

std::string generate_log_path() {
	std::stringstream filename;
	filename << "log_" << timestamp("%Y%m%d_%H%M%S") << ".txt";
	return filename.str();
}

Logger::Logger() {
	log_file.open(generate_log_path());
	if (!log_file.is_open()) {
		throw std::runtime_error("Unable to open the log file.");
	}
}

Logger::~Logger() {
	if (log_file.is_open()) {
		log_file.close();
	}
}

void Logger::write(LogLevel level, const char* format, ...) {
	if (level < Settings::get_instance()->log_level) {
		return;
	}

	std::stringstream message;
	message << timestamp("%Y-%m-%d %H:%M:%S") << " [" << level << "] ";

	va_list args;
	va_start(args, format);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	message << buffer;

	std::cerr << message.str() << std::endl;
	log_file << message.str() << std::endl;
}

void Logger::write(LogLevel level, SDL_Event* evt) {
    switch (evt->type) {
    case SDL_QUIT:
        write(level, &evt->quit);
        break;
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		write(level, &evt->key);
		break;
    case SDL_WINDOWEVENT:
        write(level, &evt->window);
        break;
    default:
        write(level, "Unknown event: %d", evt->type);
        break;
    }
}

void Logger::write(LogLevel level, SDL_WindowEvent* evt) {
    switch (evt->event) {
    case SDL_WINDOWEVENT_SHOWN:
        write(level, "Window %d shown.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        write(level, "Window %d hidden.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_EXPOSED:
        write(level, "Window %d exposed.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_MOVED:
        write(level, "Window %d moved to %d,%d.", evt->windowID, evt->data1, evt->data2);
        break;
    case SDL_WINDOWEVENT_RESIZED:
        write(level, "Window %d resized to %dx%d.", evt->windowID, evt->data1, evt->data2);
        break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        write(level, "Window %d size changed to %dx%d.", evt->windowID, evt->data1, evt->data2);
        break;
    case SDL_WINDOWEVENT_MINIMIZED:
        write(level, "Window %d minimized.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
        write(level, "Window %d maximized.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_RESTORED:
        write(level, "Window %d restored.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_ENTER:
        write(level, "Mouse entered window %d.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_LEAVE:
        write(level, "Mouse left window %d.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        write(level, "Window %d gained keyboard focus.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
        write(level, "Window %d lost keyboard focus.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_CLOSE:
        write(level, "Window % d closed.", evt->windowID);
        break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
    case SDL_WINDOWEVENT_TAKE_FOCUS:
        write(level, "Window %d is offered a focus.", evt->windowID);
        break;
    case SDL_WINDOWEVENT_HIT_TEST:
        write(level, "Window %d has a special hit test.", evt->windowID);
        break;
#endif
    default:
        write(level, "Window %d got unknown event %d.", evt->windowID, evt->event);
        break;
    }
}

void Logger::write(LogLevel level, SDL_QuitEvent* evt) {
    write(LogLevel::LOG_LEVEL_INFO, "Program quit after %i ticks.", evt->timestamp);
}

void Logger::write(LogLevel level, SDL_KeyboardEvent* evt) {
	bool is_key_down = evt->type == SDL_KEYDOWN;
	bool is_pressed = evt->state == SDL_PRESSED;
	bool is_repeat = evt->repeat != 0;

	if (is_key_down) {
		write(level, "Key down: (keysym.mod=%u;scancode=%d;sym=%d), (pressed=%d), (repeat=%d), (timestamp=%d)", evt->keysym.mod, evt->keysym.scancode, evt->keysym.sym, is_pressed, is_repeat, evt->timestamp);
	} else {
		write(level, "Key up: (keysym.mod=%u;scancode=%d;sym=%d), (pressed=%d), (repeat=%d), (timestamp=%d)", evt->keysym.mod, evt->keysym.scancode, evt->keysym.sym, is_pressed, is_repeat, evt->timestamp);
	}
}

void Logger::write(LogLevel level, GLuint gl_id) {
	if (glIsProgram(gl_id)) {
		write_program(level, gl_id);
	} else if (glIsShader(gl_id)) {
		write_shader(level, gl_id);
	} else {
		write(level, "Unknown GL id type: %d", gl_id);
	}
}

void Logger::write_program(LogLevel level, GLuint program) {
	//Program log length
	int infoLogLength = 0;
	int maxLength = infoLogLength;

	//Get info string length
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

	//Allocate string
	char* infoLog = new char[maxLength];

	//Get info log
	glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
	if (infoLogLength > 0) {
		write(level, infoLog);
	}

	//Deallocate string
	delete[] infoLog;
}

void Logger::write_shader(LogLevel level, GLuint shader) {
	//Shader log length
	int infoLogLength = 0;
	int maxLength = infoLogLength;

	//Get info string length
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

	//Allocate string
	char* infoLog = new char[maxLength];

	//Get info log
	glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
	if (infoLogLength > 0)
	{
		//Print Log
		write(level, infoLog);
	}

	//Deallocate string
	delete[] infoLog;
}

Logger* Logger::instance = nullptr;

void Logger::initialize() {
	if (instance != nullptr) {
		shutdown();
	}
	instance = new Logger();
}

void Logger::shutdown() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

Logger* Logger::get_instance() {
	return instance;
}