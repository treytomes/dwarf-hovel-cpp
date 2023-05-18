#include "window.h"

#include <gl\glew.h>
#include "gl_shader.h"
#include "glew_error.h"
#include "Logger.h"
#include "sdl_error.h"
#include "Settings.h"

Window::Window(std::string _title, int width, int height) {
	gl_program = nullptr;
	gl_context = nullptr;
	window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		throw SDLError();
	}
	texture = nullptr;

	a_position = -1;
	v_texcoord = -1;
	vbo = 0;
	ibo = 0;
}

Window::~Window() {
	if (texture != nullptr) {
		delete texture;
		texture = nullptr;
	}

	if (gl_program != nullptr) {
		delete gl_program;
		gl_program = nullptr;
	}

	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}
}

bool Window::can_handle_event(SDL_WindowEvent* evt) {
	return evt->windowID == SDL_GetWindowID(window);
}

void Window::handle_event(SDL_WindowEvent* evt) {
	if (!can_handle_event(evt)) {
		return;
	}

	LOG_INFO(evt);

	switch (evt->event) {
	case SDL_WINDOWEVENT_RESIZED:
	case SDL_WINDOWEVENT_SIZE_CHANGED:
	case SDL_WINDOWEVENT_MAXIMIZED:
		init_gl();
		break;
	}
}

SDL_Renderer* Window::create_renderer() {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == nullptr) {
		throw SDLError();
	}
	return renderer;
}

void Window::init_gl() {
	rebuild_gl_context();

	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		throw GLEWError(result);
	}

	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0) {
		throw SDLError();
	}

	load_contents();
}

void Window::rebuild_gl_context() {
	if (gl_context != nullptr) {
		SDL_GL_DeleteContext(gl_context);
		gl_context = nullptr;
	}
	if (gl_context == nullptr) {
		gl_context = SDL_GL_CreateContext(window);
	}
	if (gl_context == nullptr) {
		throw SDLError();
	}
}

void Window::load_contents() {
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);

	GLShader vertex_shader = GLShader::from_file(GL_VERTEX_SHADER, "render.vert");
	GLShader fragment_shader = GLShader::from_file(GL_FRAGMENT_SHADER, "render.frag");

	if (gl_program != nullptr) {
		delete gl_program;
		gl_program = nullptr;
	}
	gl_program = new GLProgram(&vertex_shader, &fragment_shader);

	if (texture != nullptr) {
		texture->reload();
	} else {
		texture = new Texture(Settings::get_instance()->virtual_window_size);
	}

	// Get vertex attribute location.
	a_position = gl_program->get_attribute_location("a_position");
	if (a_position == -1) {
		throw std::runtime_error("Could not retrieve program location.");
	}

	gl_program->bind();
	gl_program->set_uniform_2i("actual_screen_size", width, height);
	gl_program->set_uniform_1i("render_texture", texture->get_id());

	gl_program->unbind();

	float aspectRatio = 8.0f / 7.0f;
	float heightFromWidth = width / aspectRatio;
	float widthFromHeight = height * aspectRatio;

	// VBO data.
	static const GLfloat vertexData[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
		-1.0f,  1.0f,
	};

	// Create VBO.
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	//Enable vertex position
	glEnableVertexAttribArray(a_position);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//Disable vertex position
	glDisableVertexAttribArray(a_position);

	// IBO data.
	static const GLuint indexData[] = { 0, 1, 2, 3 };
	#define IBO_LENGTH 4

	// Create IBO.
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBO_LENGTH * sizeof(GLuint), indexData, GL_STATIC_DRAW);
}

void Window::present() {
	texture->refresh();

	gl_program->bind();
	gl_program->set_uniform_1i("time", SDL_GetTicks());

	// Enable vertex position.
	glEnableVertexAttribArray(a_position);

	// TODO: Not sure the vertex data needs to be set every time.
	// Set vertex data.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	// Set index data and render.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	// Disable vertex position.
	glDisableVertexAttribArray(a_position);

	gl_program->unbind();
	SDL_GL_SwapWindow(window);
}