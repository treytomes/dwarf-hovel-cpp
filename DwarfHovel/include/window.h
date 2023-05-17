#pragma once

#include <string>
#include <SDL.h>

#include "gl_program.h"
#include "Texture.h"

class Window {
public:
    Window(std::string title, int width, int height);
    ~Window();

    SDL_Renderer* create_renderer();
    void init_gl();
    bool can_handle_event(SDL_WindowEvent* evt);
    void handle_event(SDL_WindowEvent* evt);

    Texture* texture;
    void load_contents();
    void present();

protected:

private:
    SDL_Window* window;
    GLProgram* gl_program;
    GLint a_position;
    GLint v_texcoord;
    GLuint vbo;
    GLuint ibo;

    SDL_GLContext gl_context;

    void rebuild_gl_context();
};
