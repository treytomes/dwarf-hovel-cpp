#pragma once

#include <string>
#include <SDL.h>

#include "GameStateManager.h"
#include "gl_program.h"
#include "Texture.h"

class Window : public GameStateManager {
public:
    Window(std::string title, int width, int height);
    inline Window(std::string title, Vector2UI size) : Window(title, size.x, size.y) {}

    ~Window();

    SDL_Renderer* create_renderer();
    void init_gl();
    bool can_handle_event(SDL_WindowEvent* evt);
    void handle_event(SDL_WindowEvent* evt);
    bool can_handle_event(SDL_KeyboardEvent* evt);
    void handle_event(SDL_KeyboardEvent* evt);
    bool can_handle_event(SDL_MouseMotionEvent* evt);
    void handle_event(SDL_MouseMotionEvent* evt);
    bool can_handle_event(SDL_MouseButtonEvent* evt);
    void handle_event(SDL_MouseButtonEvent* evt);
    bool can_handle_event(SDL_MouseWheelEvent* evt);
    void handle_event(SDL_MouseWheelEvent* evt);

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
	Vector2UI mouse_position;
    unsigned char mouse_bitmap[12];
    unsigned char mouse_outline_bitmap[12];

    SDL_GLContext gl_context;

    void rebuild_gl_context();
    Vector2UI translate_position(unsigned int x, unsigned int y);
};
