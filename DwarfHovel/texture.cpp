#include "texture.h"
#include "gl_error.h"

#define NUM_CHANNELS 4

Texture::Texture(GLuint _width, GLuint _height)
    : width(_width), height(_height), is_dirty(true), is_bound(false) {
    pixels = new GLfloat[width * height * NUM_CHANNELS];
    stride = width * NUM_CHANNELS;
    reload();
}

Texture::~Texture() {
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
    if (pixels != nullptr) {
        delete[] pixels;
    }
}

void Texture::reload() {
    if (id != 0) {
        glDeleteTextures(1, &id);
    }

    glGenTextures(1, &id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::set_pixel(GLuint x, GLuint y, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    GLuint offset = y * stride + x * NUM_CHANNELS;

    if (pixels[offset + 0] != r || pixels[offset + 1] != g || pixels[offset + 2] != b || pixels[offset + 3] != a) {
        is_dirty = true;
    }

    pixels[offset + 0] = r;
    pixels[offset + 1] = g;
    pixels[offset + 2] = b;
    pixels[offset + 3] = a;
}

void Texture::bind() {
    if (!is_bound) {
        glBindTexture(GL_TEXTURE_2D, id);
        refresh();
        is_bound = true;
    }
}

void Texture::refresh(bool always) {
    if (is_dirty || always) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, pixels);
        is_dirty = false;
    }
}

void Texture::unbind() {
    if (is_bound) {
        glBindTexture(GL_TEXTURE_2D, NULL);
        is_bound = false;
    }
}

GLuint Texture::get_id() {
    return id;
}

GLuint Texture::get_width() {
    return width;
}

GLuint Texture::get_height() {
    return height;
}
